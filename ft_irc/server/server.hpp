/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:22:31 by cdudzik           #+#    #+#             */
/*   Updated: 2023/07/14 18:24:36 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include <string>
#include <map>
#include "../utils/logger.hpp"
#include "client.hpp"
#include "channel.hpp"
#include "operator.h"
#include "../commands/command_handler.hpp"

class irc_server
{
	public:
		irc_server(int port, std::string const &password);
		~irc_server();

		int run();
		int getPort() const;
		std::string const &getPassword() const;
		irc_client *get_client(int fd);
		irc_client *get_client_by_name(std::string const &nickname);
		irc_channel *get_channel(std::string const &name);
		irc_channel& create_channel(std::string const &name, std::string const &owner);
		std::map<int, irc_client> &get_clients();
		void send_message(irc_client& client, std::string const &message);
		void broadcast(irc_channel& channel, irc_client& origin, std::string const &message);
		void broadcast(irc_channel& channel, std::string const &message);
		void send_all(std::string const &message);
		void disconnect(irc_client& client, std::string const& reason, bool send_error = false);
		void disconnect_all(std::string const& reason);
		void shutdown(std::string const &reason);
		std::map<std::string, irc_operator>  &get_serverOps();

	private:
		static const int					MAX_EVENTS;

		int									_port;
		std::string const					_password;
		int									_socket;
		int									_epoll_fd;
		logger								_logger;
		std::map<int, irc_client>			_clients;
		std::map<std::string, irc_channel>	_channels;
		command_handler						_command_handler;
		std::map<std::string, irc_operator>	_servOps;

		// private methods
		void _conf_epoll();
		int _listen();
		void _accept();
		void _read(int fd);
		const irc_command _parse_message(irc_client& client, std::string line);

		// handlers
		void _on_message(irc_client& client, std::string const &message);
		void _on_disconnect(irc_client& client, std::string const &reason, bool send_error = false);
};

#endif
