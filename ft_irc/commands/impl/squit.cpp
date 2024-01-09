#include "implementation_base.hpp"
#include <algorithm>

void command_handler::_squit(irc_command const &command){
	if (command.params.size() < 1){
		_server.send_message(command.client, err_msg::need_more_params(command.command));
		throw std::runtime_error("SQUIT error");
	}
	if (!command.client.isOp){
		_server.send_message(command.client, err_msg::no_privileges());
		throw std::runtime_error("SQUIT error");
	}
	std::string server_name = command.params[0];
	if (server_name != "localhost") {
		throw std::runtime_error("SQUIT error");
	}
	std::string comment = command.params.size() > 1 ? command.params[1] : "";
	_server.shutdown("Got SQUIT from " + command.client.nickname);
}