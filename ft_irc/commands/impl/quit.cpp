/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:07:32 by cdudzik           #+#    #+#             */
/*   Updated: 2023/07/13 00:15:30 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implementation_base.hpp"

void command_handler::_quit(irc_command const& command)
{
	_logger.info("Client " + ft_to_string(command.client.fd) + " (" + command.client.address + ":" + ft_to_string(command.client.port) + ") quit");
	std::string id = command.client.id;
	_server.disconnect(command.client, command.params.size() > 0 ? command.params[0] : "");
}
