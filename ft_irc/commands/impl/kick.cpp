#include "implementation_base.hpp"
#include <algorithm>

void command_handler::_kick(irc_command const &command){
	if (command.params.size() < 2 || command.params.size() > 3){
		_server.send_message(command.client, err_msg::need_more_params("KICK"));
		return ;
	}
	irc_channel *channel = _server.get_channel(command.params[0]);
	if (!channel){
		_server.send_message(command.client, err_msg::no_such_channel(command.params[0]));
		return ;
	}
	if (channel->isOpeChanel(command.client) == false && command.client.isOp == false){
		_server.send_message(command.client, err_msg::chan_op_privileges_needed(command.client.nickname, command.params[0]));
		return ;
	}
	if (channel->has_client(command.client.fd) == false){
		_server.send_message(command.client, err_msg::not_on_channel(channel->get_name()));
		return;
	}
	irc_client *dest = _server.get_client_by_name(command.params[1]);
	if (!dest){
		_server.send_message(command.client, err_msg::no_such_nick(command.params[1]));
		return;
	}
	std::vector<std::string>::iterator it = std::find(dest->channels.begin(), dest->channels.end(), channel->get_name());
	if (!channel->has_client(dest->fd)){
		_server.send_message(command.client, err_msg::user_not_in_channel(command.params[1], command.params[0]));
		return;
	}
	if (command.client.isOp == false && channel->get_channel_owner() != command.client.nickname && (channel->isOpeChanel(*dest) || dest->isOp == true)){
		_server.send_message(command.client, err_msg::chan_op_privileges_needed(command.client.nickname, channel->get_name()));
		return ;
	}
	if (command.params.size() == 2)
		_server.broadcast(*channel, broadcast_msg::kick(channel->get_name() , command.client.id, command.params[1], ""));
	else
		_server.broadcast(*channel, broadcast_msg::kick(channel->get_name() , command.client.id, command.params[1], command.params[2]));
	channel->remove_client(dest->fd);
	dest->channels.erase(it);
}
