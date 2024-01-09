/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:17:57 by cdudzik           #+#    #+#             */
/*   Updated: 2023/06/19 17:38:35 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implementation_base.hpp"

void command_handler::_user(irc_command const& command)
{
	if (command.client.handshake_done) {
		_logger.error("Client " + ft_to_string(command.client.fd) + " (" + command.client.address + ":" + ft_to_string(command.client.port) + ") sent command 'USER' but already has a realname");
		_server.send_message(command.client, err_msg::already_registered());
	} else if (command.params.size() != 4) {
		_logger.error("Client " + ft_to_string(command.client.fd) + " (" + command.client.address + ":" + ft_to_string(command.client.port) + ") sent command 'USER' with wrong number of parameters");
		_server.send_message(command.client, err_msg::need_more_params("USER"));
	} else {
		command.client.username = command.params[0];
		command.client.hostname = command.params[2];
		command.client.realname = command.params[3];
		_check_handcheck_status(command.client);
	}
}
