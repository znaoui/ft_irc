/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:08:00 by cdudzik           #+#    #+#             */
/*   Updated: 2023/07/14 18:33:40 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implementation_base.hpp"
#include <algorithm>

static bool _is_valid_channel_name(std::string const& name)
{
	for (std::string::size_type i = 1; i < name.length(); ++i)
	{
		if (command_handler::ALLOWED_NICKNAME_CHARACTERS.find(name[i]) == std::string::npos)
			return false;
	}
	return true;
}

static std::string _get_names(irc_channel& channel)
{
	std::string names = "";
	for (std::map<int, irc_client&>::const_iterator it = channel.get_clients().begin(); it != channel.get_clients().end(); ++it)
		names += (channel.isOpeChanel(it->second) == true ? "@" : "") + it->second.nickname + " ";
	return (names);
}

void command_handler::_join(irc_command const& command)
{
	if (command.params.size() < 1) {
		_logger.error("Client " + ft_to_string(command.client.fd) + " (" + command.client.address + ":" + ft_to_string(command.client.port) + ") sent command 'JOIN' with wrong number of parameters");
		_server.send_message(command.client, err_msg::need_more_params("JOIN"));
		return ;
	}
	std::string channel_name = command.params[0];
	if (channel_name[0] != '#' || !_is_valid_channel_name(channel_name)) {
		_logger.error("Client " + ft_to_string(command.client.fd) + " (" + command.client.address + ":" + ft_to_string(command.client.port) + ") sent command 'JOIN' with invalid channel name");
		_server.send_message(command.client, err_msg::erronous_nickname(channel_name));
		return ;
	}
	irc_channel& channel = _server.create_channel(channel_name, command.client.nickname);
	if (channel.has_client(command.client.fd)) {
		_logger.error("Client " + ft_to_string(command.client.fd) + " (" + command.client.address + ":" + ft_to_string(command.client.port) + ") tried to join channel " + channel_name + " but is already in it");
		_server.send_message(command.client, err_msg::user_on_channel(command.client.id, channel_name));
	} else {
		if (command.client.isOp == false){
			if (channel.get_channel_mode().find("i") != std::string::npos){
				std::vector<std::string>::iterator it = std::find(command.client.invite.begin(), command.client.invite.end(), channel_name);
				if (it == command.client.invite.end())
				{
					_server.send_message(command.client, err_msg::invite_only_chan(channel.get_name(), command.client.nickname));
					return;
				}
				command.client.invite.erase(it);
			}
			if (channel.get_channel_mode().find("l") != std::string::npos){
				int limit = channel.getClientsLimit();
				if (channel.clients_count() >= limit){
					_server.send_message(command.client, err_msg::to_many_people_chan(command.client.nickname, channel.get_name()));
					return;
				}
			}
			if (channel.get_channel_mode().find("k") != std::string::npos){
				if (command.params.size() < 2 || command.params[1] != channel.get_pass()){
					_server.send_message(command.client, err_msg::wrong_channel_key(channel_name, command.client.nickname));
					return;
				}
			}
		}
		if (channel.isBan(command.client.nickname) == true){
			_server.send_message(command.client, err_msg::youre_ban(channel.get_name()));
			return;
		}
		_logger.info("Client " + ft_to_string(command.client.fd) + " (" + command.client.address + ":" + ft_to_string(command.client.port) + ") joined channel " + channel_name);
		channel.add_client(command.client);
		command.client.channels.push_back(channel_name);
		_server.broadcast(channel, broadcast_msg::join(command.client.id, channel_name));
		irc_channel::irc_topic topic = channel.get_topic();
		if (!topic.topic.empty()) {
			_server.send_message(command.client, rpl_msg::topic(channel.get_name(), topic.topic, command.client.nickname) + "\n" + rpl_msg::topic_set_by(channel.get_name(), topic.set_by, topic.date));
		}
		_server.send_message(command.client, rpl_msg::names(channel_name, command.client.nickname, _get_names(channel) + "\n" + rpl_msg::names_end(channel_name, command.client.nickname)));
	}
}
