/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:17:04 by cdudzik           #+#    #+#             */
/*   Updated: 2023/06/27 01:51:18 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implementation_base.hpp"

static bool _is_valid_nickname(std::string const& nickname)
{
	for (std::string::size_type i = 0; i < nickname.length(); ++i)
	{
		if (command_handler::ALLOWED_NICKNAME_CHARACTERS.find(nickname[i]) == std::string::npos)
			return false;
	}
	return true;
}

static std::string _get_new_nickname(irc_server& server, std::string const& nickname)
{
	int i = 2;
	std::string new_nickname = nickname + ft_to_string(i);
	while (server.get_client_by_name(new_nickname) != NULL) {
		new_nickname = nickname + ft_to_string(++i);
	}
	return new_nickname;
}

void command_handler::_nick(irc_command const& command)
{
	if (command.params.size() != 1) {
		_logger.error("Client " + ft_to_string(command.client.fd) + " (" + command.client.address + ":" + ft_to_string(command.client.port) + ") sent command 'NICK' with wrong number of parameters");
		_server.send_message(command.client, err_msg::need_more_params("NICK"));
	} else if (command.params[0].size() > 9) {
		_logger.error("Client " + ft_to_string(command.client.fd) + " (" + command.client.address + ":" + ft_to_string(command.client.port) + ") sent command 'NICK' with nickname too long");
		_server.send_message(command.client, err_msg::erronous_nickname(command.params[0]));
	} else if (!_is_valid_nickname(command.params[0])) {
		_logger.error("Client " + ft_to_string(command.client.fd) + " (" + command.client.address + ":" + ft_to_string(command.client.port) + ") sent command 'NICK' with invalid nickname");
		_server.send_message(command.client, err_msg::erronous_nickname(command.params[0]));
	} else {
		std::string nick = command.params[0];
		if (_server.get_client_by_name(nick) != NULL) {
			nick = _get_new_nickname(_server, nick);
			_server.send_message(command.client, broadcast_msg::nick(command.params[0], nick));
		}
		if (command.client.nickname != "") {
			_server.send_all(broadcast_msg::nick(command.client.id, nick));
			command.client.id = nick + "!" + command.client.username + "@" + command.client.hostname;
		}
		command.client.nickname = nick;
		_logger.info("Client " + ft_to_string(command.client.fd) + " (" + command.client.address + ":" + ft_to_string(command.client.port) + ") set nickname to " + nick);
		_check_handcheck_status(command.client);
	}
}
