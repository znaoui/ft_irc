/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 18:27:38 by cdudzik           #+#    #+#             */
/*   Updated: 2023/06/19 17:11:57 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implementation_base.hpp"

void command_handler::_notice(irc_command const &command)
{
	if (command.params.size() < 1) {
		_logger.error("Client " + ft_to_string(command.client.fd) + " (" + command.client.address + ":" + ft_to_string(command.client.port) + ") sent command 'NOTICE' with wrong number of parameters");
		_server.send_message(command.client, err_msg::need_more_params("NOTICE"));
		return ;
	}
	std::string const& target = command.params[0];
	std::string const& msg = command.params[1];
	if (target[0] == '#') {
		irc_channel* channel = _server.get_channel(target);
		if (channel == NULL) {
			_logger.error("Client " + command.client.username + " sent NOTICE command to non-existing channel " + target);
			_server.send_message(command.client, err_msg::no_such_channel(target));
		} else {
			_logger.info("Client " + command.client.username + " sent NOTICE command to channel " + target);
			_server.broadcast(*channel, command.client, broadcast_msg::notice(command.client.id, target, msg));
		}
	} else {
		irc_client *client = _server.get_client_by_name(target);
		if (client == NULL) {
			_logger.error("Client " + command.client.username + " sent NOTICE command to non-existing client " + target);
			_server.send_message(command.client, err_msg::no_such_nick(target));
		} else {
			_logger.info("Client " + command.client.username + " sent NOTICE command to client " + target);
			_server.send_message(*client, broadcast_msg::notice(command.client.id, target, msg));
		}
	}
}
