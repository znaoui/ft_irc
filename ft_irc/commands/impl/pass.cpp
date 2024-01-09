/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:08:14 by cdudzik           #+#    #+#             */
/*   Updated: 2023/06/19 17:45:42 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implementation_base.hpp"

void command_handler::_pass(irc_command const &command)
{
	irc_client &client = command.client;
	if (client.passwd_sent) {
		_logger.error("PASS command received from client " + ft_to_string(client.fd) + " (" + client.address + ":" + ft_to_string(client.port) + ") but already sent");
		_server.send_message(client, err_msg::already_registered());
	} else if (command.params.size() != 1) {
		_logger.error("PASS command received from client " + ft_to_string(client.fd) + " (" + client.address + ":" + ft_to_string(client.port) + ") with wrong number of parameters");
		_server.send_message(client, err_msg::need_more_params("PASS"));
	} else if (command.params[0] == _server.getPassword()) {
		client.passwd_sent = true;
		_logger.debug("PASS command received from client " + ft_to_string(client.fd) + " (" + client.address + ":" + ft_to_string(client.port) + ") with correct password");
		_check_handcheck_status(client);
	} else {
		_logger.error("PASS command received from client " + ft_to_string(client.fd) + " (" + client.address + ":" + ft_to_string(client.port) + ") with wrong password " + command.params[0]);
		_server.send_message(client, err_msg::password_mismatch());
	}
}
