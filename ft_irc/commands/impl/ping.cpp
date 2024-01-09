/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 22:06:21 by cdudzik           #+#    #+#             */
/*   Updated: 2023/05/27 14:08:37 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implementation_base.hpp"

void command_handler::_ping(irc_command const &command)
{
	if (command.params.size() < 1) {
		_server.send_message(command.client, err_msg::need_more_params("PING"));
	} else {
		_server.send_message(command.client, "PONG " + command.params[0]);
	}
}
