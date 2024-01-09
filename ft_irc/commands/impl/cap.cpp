/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:59:33 by cdudzik           #+#    #+#             */
/*   Updated: 2023/05/27 14:08:29 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implementation_base.hpp"

void command_handler::_cap(irc_command const &command)
{
	if (command.params.size() < 1) {
		_server.send_message(command.client, err_msg::need_more_params("CAP"));
	} else if (command.params[0] == "LS") {
		_server.send_message(command.client, "CAP * LS :");
	}
}
