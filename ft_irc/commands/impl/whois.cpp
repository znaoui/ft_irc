/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whois.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:58:21 by cdudzik           #+#    #+#             */
/*   Updated: 2023/06/19 18:15:47 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implementation_base.hpp"

void command_handler::_whois(irc_command const& command)
{
	irc_client &client = command.client;
	if (command.params.size() != 1) {
		_logger.error("WHOIS command received from client " + ft_to_string(client.fd) + " (" + client.address + ":" + ft_to_string(client.port) + ") with wrong number of parameters");
		_server.send_message(client, err_msg::need_more_params("WHOIS"));
	} else {
		irc_client *target = _server.get_client_by_name(command.params[0]);
		if (target == NULL) {
			_logger.error("WHOIS command received from client " + ft_to_string(client.fd) + " (" + client.address + ":" + ft_to_string(client.port) + ") with wrong nickname " + command.params[0]);
			_server.send_message(client, err_msg::no_such_nick(command.params[0]));
		} else {
			std::string whois = rpl_msg::whois_user(client.nickname, target->nickname, target->username, target->hostname, target->realname) + "\n";
			whois += rpl_msg::whois_server(client.nickname, target->nickname, "localhost", "42 - ft_irc") + "\n";
			std::string channels = "";
			for (std::vector<std::string>::iterator it = target->channels.begin(); it != target->channels.end(); ++it)
				channels += *it + " ";
			if (channels != "")
				whois += rpl_msg::whois_channels(client.nickname, target->nickname, channels) + "\n";
			if (target->isOp)
				whois += rpl_msg::whois_operator(client.nickname, target->nickname) + "\n";
			if (target->away_msg != "")
				whois += rpl_msg::whois_away(client.nickname, target->nickname, target->away_msg) + "\n";
			whois += rpl_msg::whois_end(client.nickname, target->nickname);
			_server.send_message(client, whois);
		}
	}
}
