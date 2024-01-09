#include "implementation_base.hpp"
#include <algorithm>

void command_handler::_kill(irc_command const &command){
	if (command.params.size() < 1 || command.params.size() > 2){
		_server.send_message(command.client, err_msg::need_more_params(command.command));
		return;
	}
	if (!command.client.isOp){
		_server.send_message(command.client, err_msg::no_privileges());
		return;
	}
	irc_client *dest = _server.get_client_by_name(command.params[0]);
	if (!dest){
		_server.send_message(command.client, err_msg::no_such_nick(command.params[0]));
		return;
	}
	if (dest->isOp){
		_server.send_message(command.client, err_msg::no_privileges());
		return;
	}
	_server.disconnect(*dest, "KILLed by " + command.client.nickname + ": " + (command.params.size() == 2 ? command.params[1] : ""), true);
}
