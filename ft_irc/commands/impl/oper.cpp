#include "implementation_base.hpp"
#include <algorithm>
void command_handler::_oper(irc_command const &command){
	std::map<std::string, irc_operator> &operators = _server.get_serverOps();


	std::map<std::string, irc_operator>::iterator it = operators.find(command.params[0]);
	if (command.params.size() < 2){
		_server.send_message(command.client, err_msg::need_more_params(command.command));
		return ;
	}
	if (it == operators.end()){
		_server.send_message(command.client, err_msg::no_privileges());
		return;
	}
	if (it->second.password != command.params[1]){
		_server.send_message(command.client, err_msg::password_mismatch());
		return;
	}
	command.client.isOp = true;
	_server.send_message(command.client, rpl_msg::oper(command.client.nickname));
}
