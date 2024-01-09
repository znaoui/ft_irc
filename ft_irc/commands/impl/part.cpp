/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:23:38 by cdudzik           #+#    #+#             */
/*   Updated: 2023/06/19 15:06:19 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include "implementation_base.hpp"

void command_handler::_part(irc_command const &command)
{
	if (command.params.size() < 1)
	{
		_logger.error("Client " + ft_to_string(command.client.fd) + " (" + command.client.address + ":" + ft_to_string(command.client.port) + ") sent command 'PART' with wrong number of parameters");
		_server.send_message(command.client, err_msg::need_more_params("PART"));
		return ;
	}

	std::string channel_name = command.params[0];
	if (channel_name[0] != '#')
	{
		_logger.error("Client " + ft_to_string(command.client.fd) + " (" + command.client.address + ":" + ft_to_string(command.client.port) + ") sent command 'PART' with invalid channel name");
		_server.send_message(command.client, err_msg::erronous_nickname(channel_name));
	} else if (std::find(command.client.channels.begin(), command.client.channels.end(), channel_name) == command.client.channels.end()) {
		_logger.error("Client " + ft_to_string(command.client.fd) + " (" + command.client.address + ":" + ft_to_string(command.client.port) + ") tried to part channel " + channel_name + " but is not in it");
		_server.send_message(command.client, err_msg::not_on_channel(channel_name));
	} else {
		irc_channel *channel = _server.get_channel(channel_name);
		if (channel != NULL) {
			_logger.info("Client " + ft_to_string(command.client.fd) + " (" + command.client.address + ":" + ft_to_string(command.client.port) + ") parted channel " + channel_name);
			_server.broadcast(*channel, broadcast_msg::part(command.client.id, channel_name));
			channel->remove_client(command.client.fd);
			if (channel->clients_count() == 0) {
				command.client.channels.erase(std::remove(command.client.channels.begin(), command.client.channels.end(), channel_name), command.client.channels.end());
			}
		} else {
			_logger.error("Client " + ft_to_string(command.client.fd) + " (" + command.client.address + ":" + ft_to_string(command.client.port) + ") tried to part channel " + channel_name + " but it does not exist");
			_server.send_message(command.client, err_msg::no_such_channel(channel_name));
		}
	}
}
