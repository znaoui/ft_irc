/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:14:25 by cdudzik           #+#    #+#             */
/*   Updated: 2023/06/19 15:20:06 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implementation_base.hpp"

void command_handler::_privmsg(irc_command const& command)
{
	if (command.params.size() < 2) {
		_logger.error("Client " + command.client.nickname + " sent PRIVMSG command with not enough params");
		_server.send_message(command.client, err_msg::need_more_params("PRIVMSG"));
		return;
	}
	std::string msg = command.params[1];
	std::string target = command.params[0];
	if (target[0] == '#') {
		irc_channel* channel = _server.get_channel(target);
		if (channel == NULL) {
			_logger.error("Client " + command.client.nickname + " sent PRIVMSG command to non-existing channel " + target);
			_server.send_message(command.client, err_msg::no_such_channel(target));
		} else if (!channel->has_client(command.client.fd)) {
			_logger.error("Client " + command.client.nickname + " sent PRIVMSG command to channel " + target + " without being in it");
			_server.send_message(command.client, err_msg::not_on_channel(target));
		} else {
			_logger.info("Client " + command.client.nickname + " sent PRIVMSG command to channel " + target);
			_server.broadcast(*channel, command.client, broadcast_msg::priv_msg(command.client.id, msg, target));
		}
	} else {
		irc_client *client = _server.get_client_by_name(target);
		if (client == NULL) {
			_logger.error("Client " + command.client.nickname + " sent PRIVMSG command to non-existing client " + target);
			_server.send_message(command.client, err_msg::no_such_nick(target));
		} else {
			_logger.info("Client " + command.client.nickname + " sent PRIVMSG command to client " + target);
			_server.send_message(*client, broadcast_msg::priv_msg(command.client.id, msg, target));
		}
	}
}
