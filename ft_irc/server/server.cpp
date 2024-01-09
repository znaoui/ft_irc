/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:11:31 by cdudzik           #+#    #+#             */
/*   Updated: 2023/07/14 18:27:59 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if defined(__APPLE__)
	#include <sys/types.h>
	#include <sys/event.h>
	#include <sys/time.h>
#elif defined(__linux__)
	#include <sys/epoll.h>
#endif

#include <algorithm>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>
#include "server.hpp"
#include "../utils/utils.hpp"
#include "messages/broadcast_msg.hpp"

const int irc_server::MAX_EVENTS = 10;

irc_server::irc_server(int port, std::string const &password) : _port(port), _password(password), _socket(-1), _epoll_fd(-1), _logger(), _command_handler(command_handler(*this, _logger))
{
	_servOps.insert(std::make_pair("zak", irc_operator("2222")));
	_servOps.insert(std::make_pair("mehdi", irc_operator("1111")));
	_servOps.insert(std::make_pair("ctp", irc_operator("ctp")));
}

irc_server::~irc_server()
{
	if (_socket != -1) {
		close(_socket);
	}
	if (_epoll_fd != -1) {
		close(_epoll_fd);
	}
	_clients.clear();
}

std::map<int, irc_client> &irc_server::get_clients()
{
	return _clients;
}

irc_client *irc_server::get_client(int fd)
{
	if (_clients.find(fd) == _clients.end()) {
		return NULL;
	}
	return &_clients[fd];
}

irc_client *irc_server::get_client_by_name(std::string const &nickname)
{
	for (std::map<int, irc_client>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
		if (it->second.nickname == nickname) {
			return &it->second;
		}
	}
	return NULL;
}

irc_channel *irc_server::get_channel(std::string const &name)
{
	std::map<std::string, irc_channel>::iterator it = _channels.find(name);
	if (it == _channels.end()) {
		return NULL;
	}
	return &it->second;
}

irc_channel& irc_server::create_channel(std::string const &name, std::string const& owner)
{
	std::map<std::string, irc_channel>::iterator it = _channels.find(name);
	if (it != _channels.end()) {
		return it->second;
	}
	irc_channel channel(name, owner);
	_channels[name] = channel;
	return _channels[name];
}

void irc_server::send_message(irc_client& client, std::string const &message)
{
	_logger.debug("Sending message to client " + ft_to_string(client.fd) + " (" + client.address + ":" + ft_to_string(client.port) + "): " + message);
	std::string msg = message + "\n";
	if (send(client.fd, msg.c_str(), msg.length(), 0) == -1) {
		_logger.error("Failed to send message to client " + ft_to_string(client.fd) + " (" + client.address + ":" + ft_to_string(client.port) + ")");
		//disconnect client?
		//_on_disconnect(client);
	}
}

void irc_server::broadcast(irc_channel& channel, std::string const &message)
{
	_logger.debug("Broadcasting message to channel " + channel.get_name() + ": " + message);
	std::string msg = message + "\n";
	std::map<int, irc_client&>::const_iterator it = channel.get_clients().begin();
	std::map<int, irc_client&>::const_iterator end = channel.get_clients().end();
	for (; it != end; it++) {
		int fd = it->first;
		if (send(fd, msg.c_str(), msg.length(), 0) == -1) {
			_logger.error("Failed to send message to client " + ft_to_string(fd));
			//disconnect client?
			//_on_disconnect(client);
		}
	}
}

void irc_server::broadcast(irc_channel& channel, irc_client& origin, std::string const &message)
{
	_logger.debug("Broadcasting message to channel " + channel.get_name() + ": " + message);
	std::string msg = message + "\n";
	std::map<int, irc_client&>::const_iterator it = channel.get_clients().begin();
	std::map<int, irc_client&>::const_iterator end = channel.get_clients().end();
	for (; it != end; it++) {
		int fd = it->first;
		if (fd != origin.fd && send(fd, msg.c_str(), msg.length(), 0) == -1) {
			_logger.error("Failed to send message to client " + ft_to_string(fd));
			//disconnect client?
			//_on_disconnect(client);
		}
	}
}

void irc_server::send_all(std::string const &message)
{
	_logger.debug("Sending message to all clients: " + message);
	std::string msg = message + "\n";
	std::map<int, irc_client>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); it++) {
		irc_client& client = it->second;
		if (client.handshake_done && send(client.fd, msg.c_str(), msg.length(), 0) == -1) {
			_logger.error("Failed to send message to client " + ft_to_string(client.fd) + " (" + client.address + ":" + ft_to_string(client.port) + ")");
			//disconnect client?
			//_on_disconnect(client);
		}
	}
}

void irc_server::disconnect(irc_client& client, std::string const& reason, bool send_error)
{
	_logger.info("Disconnecting client " + ft_to_string(client.fd) + " (" + client.address + ":" + ft_to_string(client.port) + "): " + reason);
	_on_disconnect(client, reason, send_error);
}

void irc_server::disconnect_all(std::string const& reason)
{
	_logger.info("Disconnecting all clients");
	std::map<int, irc_client>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); it++) {
		irc_client& client = it->second;
		send_message(client, "ERROR :" +  reason);
		close(client.fd);
	}
	_clients.clear();
}

void irc_server::shutdown(std::string const& reason)
{
	_logger.info("Shutting down server");
	disconnect_all(reason);
	close(_socket);
	_socket = -1;
	close(_epoll_fd);
	_epoll_fd = -1;
	_channels.clear();
	_servOps.clear();
}

void irc_server::_on_message(irc_client& client, std::string const &message)
{
	client.buffer += message;
	_logger.debug("Client " + ft_to_string(client.fd) + " (" + client.address + ":" + ft_to_string(client.port) + ") buffer: " + client.buffer);
	std::string::size_type pos = client.buffer.find_first_of("\n\r");
	while (pos != std::string::npos) {
		std::string line = trim(client.buffer.substr(0, pos));
		int i = 0;
		if (line.length() > 0) {
			const irc_command& command = _parse_message(client,  line);
			i = _command_handler.handle(command);
		}
		if (i)
			return;
		client.buffer.erase(0, pos + 1);
		pos = client.buffer.find_first_of("\n\r");
	}
}

const irc_command irc_server::_parse_message(irc_client& client, std::string line)
{
	irc_command cmd(client);
	size_t last_pos = 0;
	size_t len = line.length();
	for (size_t i = 0; i < len; i++) {
		if (line[i] == ':') {
			cmd.params.push_back((i + 1) < len ? line.substr(i + 1) : "");
			break;
		} else if (line[i] == ' ' || i == len - 1) {
			if (last_pos == 0) {
				cmd.command = line.substr(last_pos, i - last_pos + (i == len - 1));
			} else {
				cmd.params.push_back(line.substr(last_pos, i - last_pos + (i == len - 1)));
			}
			last_pos = i + 1;
		}
	}
	if (cmd.command.empty()) {
		cmd.command = line;
	}
	std::transform(cmd.command.begin(), cmd.command.end(), cmd.command.begin(), ::toupper);
	return (cmd);
}

void irc_server::_on_disconnect(irc_client& client, std::string const& reason, bool send_error)
{
	if (send_error) {
		send_message(client, "ERROR :" +  reason);
	}
	close(client.fd);
	if (client.handshake_done) {
		for (std::map<std::string, irc_channel>::iterator it = _channels.begin(); it != _channels.end(); ) {
			irc_channel& channel = it->second;
			channel.remove_client(client.fd);
			if (channel.get_clients().empty()) {
				std::map<std::string, irc_channel>::iterator tmp = it;
				it++;
				_channels.erase(tmp);
			} else {
				++it;
				broadcast(channel, broadcast_msg::quit(client.id, reason));
			}
		}
	}
	std::map<int, irc_client>::iterator it = _clients.find(client.fd);
	if (it != _clients.end()){
		_clients.erase(it);
	}
}

const std::string& irc_server::getPassword() const
{
	return (_password);
}

int irc_server::getPort() const
{
	return (this->_port);
}

int irc_server::run()
{
	_logger.info("Starting server on port " + ft_to_string(_port));
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket == -1) {
		_logger.error("Failed to create socket");
		return (EXIT_FAILURE);
	}
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(_port);
	addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(_socket, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
		_logger.error("Failed to bind socket");
		return (EXIT_FAILURE);
	}
	if (fcntl(_socket, F_SETFL, O_NONBLOCK) == -1) {
		_logger.error("Failed to set socket to non-blocking");
		return (EXIT_FAILURE);
	}
	if (listen(_socket, SOMAXCONN) == -1) {
		_logger.error("Failed to listen on socket");
		return (EXIT_FAILURE);
	}
	try {
		_conf_epoll();
	} catch(const std::exception& e) {
		_logger.error(e.what());
		return (EXIT_FAILURE);
	}
	return (_listen());
}

void irc_server::_conf_epoll()
{
	_logger.debug("Configuring epoll");
#if defined(__APPLE__)
	_epoll_fd = kqueue();
	if (_epoll_fd == -1) {
		throw std::runtime_error("Failed to create kqueue");
	}
	struct kevent ev;
	EV_SET(&ev, _socket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
	if (kevent(_epoll_fd, &ev, 1, NULL, 0, NULL) == -1) {
		throw std::runtime_error("Failed to add socket to kqueue");
	}
#elif defined(__linux__)
	_epoll_fd = epoll_create1(0);
	if (_epoll_fd == -1) {
		throw std::runtime_error("Failed to create epoll");
	}
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = _socket;
	if (epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, _socket, &ev) == -1) {
		throw std::runtime_error("Failed to add socket to epoll");
	}
#endif
}

int irc_server::_listen()
{
	_logger.info("Server started, listening for connections");
	while (_socket != -1) {
#if defined(__APPLE__)
		struct kevent ev[MAX_EVENTS];
		int n = kevent(_epoll_fd, NULL, 0, ev, MAX_EVENTS, NULL);
#elif defined(__linux__)
		struct epoll_event ev[MAX_EVENTS];
		int n = epoll_wait(_epoll_fd, ev, MAX_EVENTS, -1);
#endif
		if (n == -1) {
			_logger.error("Failed to wait for events");
			return (EXIT_FAILURE);
		}
		for (int i = 0; i < n; i++) {
#if defined(__APPLE__)
			int fd = ev[i].ident;
#elif defined(__linux__)
			int fd = ev[i].data.fd;
#endif
			if (fd == _socket) {
				_accept();
			} else {
				_read(fd);
			}
		}
	}
	return (EXIT_SUCCESS);
}

void irc_server::_accept()
{
	sockaddr_in addr;
	socklen_t len = sizeof(addr);
	int fd = accept(_socket, (struct sockaddr *)&addr, &len);
	if (fd == -1) {
		_logger.error("Failed to accept connection");
		return;
	}
#if defined(__APPLE__)
	struct kevent ev;
	EV_SET(&ev, fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
	if (kevent(_epoll_fd, &ev, 1, NULL, 0, NULL) == -1) {
		_logger.error("Failed to add connection to kqueue");
		close(fd);
		return;
	}
#elif defined(__linux__)
	struct epoll_event ev;
	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = fd;
	if (epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, fd, &ev) == -1) {
		_logger.error("Failed to add connection to epoll");
		close(fd);
		return;
	}
#endif
	_logger.info("Accepted connection from " + std::string(inet_ntoa(addr.sin_addr)) + ":" + ft_to_string(ntohs(addr.sin_port)));
	irc_client client;
	client.fd = fd;
	client.address = inet_ntoa(addr.sin_addr);
	client.port = ntohs(addr.sin_port);
	_clients.insert(std::make_pair(fd, client));
}

void irc_server::_read(int fd)
{
	irc_client& client = _clients[fd];
	char buf[1024];
	int n = read(fd, buf, sizeof(buf));
	if (n == -1) {
		_logger.error("Failed to read from connection " + ft_to_string(fd) + " (" + client.address + ":" + ft_to_string(client.port) + ")");
		_on_disconnect(client, "Connection loss", true);
		return;
	}
	if (n == 0) {
		_logger.info("Connection closed by client " + ft_to_string(fd) + " (" + client.address + ":" + ft_to_string(client.port) + ")");
		_on_disconnect(client, "Connection loss", true);
		return;
	}
	const std::string message(buf, n);
	_logger.debug("Received " + ft_to_string(n) + " bytes: " + message + " from client " + ft_to_string(fd) + " (" + client.address + ":" + ft_to_string(client.port) + ")");
	_on_message(client, message);
}

std::map<std::string, irc_operator>  &irc_server::get_serverOps() {
	return (_servOps);
}
