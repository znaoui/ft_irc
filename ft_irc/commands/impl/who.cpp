/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:23:31 by cdudzik           #+#    #+#             */
/*   Updated: 2023/06/19 17:42:53 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implementation_base.hpp"

void command_handler::_who(irc_command const& command)
{
	std::string who_list = "";
	if (command.params.size() == 1) {
		std::string target = command.params[0];
		_logger.info("Client " + ft_to_string(command.client.fd) + " (" + command.client.address + ":" + ft_to_string(command.client.port) + ") sent command 'WHO' with parameter '" + command.params[0] + "'");
		if (target[0] == '#') {
			irc_channel* channel = _server.get_channel(target);
			if (channel != NULL) {
				std::map<int, irc_client&> clients = channel->get_clients();
				for (std::map<int, irc_client&>::iterator it = clients.begin(); it != clients.end(); ++it) {
					irc_client& client = it->second;
					std::string op_flags = (client.isOp ? "*" : (channel->isOpeChanel(client) == true  ? "@" : ""));
					who_list += rpl_msg::who(command.client.nickname, channel->get_name(), client.username, client.hostname, client.realname, "localhost", client.away_msg != "", op_flags) + "\n";
				}
			}
		} else {
			irc_client* client = _server.get_client_by_name(target);
			if (client != NULL) {
				who_list = rpl_msg::who(command.client.nickname, "*", client->username, client->hostname, client->realname, "localhost", client->away_msg != "", client->isOp ? "*" : "") + "\n";
			}
		}
		who_list += rpl_msg::who_end(command.client.nickname, target);
		_server.send_message(command.client, who_list);
	} else {
		_logger.info("Client " + ft_to_string(command.client.fd) + " (" + command.client.address + ":" + ft_to_string(command.client.port) + ") sent command 'WHO' with no parameters");
		std::map<int, irc_client> clients = _server.get_clients();
		for (std::map<int, irc_client>::iterator it = clients.begin(); it != clients.end(); ++it) {
			irc_client& client = it->second;
			who_list += rpl_msg::who(command.client.nickname, "*", client.username, client.hostname, client.realname, "localhost", client.away_msg != "", client.isOp ? "*" : "") + "\n";
		}
		who_list += rpl_msg::who_end(command.client.nickname, "*");
		_server.send_message(command.client, who_list);
	}

}
