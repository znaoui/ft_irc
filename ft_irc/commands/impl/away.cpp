/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   away.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 18:50:11 by cdudzik           #+#    #+#             */
/*   Updated: 2023/06/09 18:57:29 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implementation_base.hpp"

void command_handler::_away(irc_command const& command)
{
	if (command.params.empty()) {
		_logger.info("Client " + command.client.username + " (" + command.client.address + ":" + ft_to_string(command.client.port) + ") unset AWAY status");
		_server.send_message(command.client, cmd_msg::away_unset(command.client.nickname));
		command.client.away_msg = "";
	} else {
		_logger.info("Client " + command.client.username + " (" + command.client.address + ":" + ft_to_string(command.client.port) + ") set AWAY status");
		_server.send_message(command.client, cmd_msg::away(command.client.nickname));
		command.client.away_msg = command.params[0];
	}
}
