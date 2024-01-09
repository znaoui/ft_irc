#include "implementation_base.hpp"

void command_handler::_invite(irc_command const &command){
	if (command.params.size() < 2){
		_server.send_message(command.client, err_msg::need_more_params("INVITE"));
		return;
	}
	irc_channel *channel = _server.get_channel(command.params[1]);
	if (!channel){
		_server.send_message(command.client, err_msg::no_such_channel(command.params[1]));
	}
	irc_client *dest = _server.get_client_by_name(command.params[0]);
	if (!dest){
		_server.send_message(command.client, err_msg::no_such_nick(command.params[0]));
		return ;
	}
	dest->invite.push_back(channel->get_name());
	_server.send_message(*dest, cmd_msg::invite(command.client.id, dest->nickname, channel->get_name()));
}
