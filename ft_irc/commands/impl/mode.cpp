#include "implementation_base.hpp"
#include <ctype.h>
#include <cstdlib>

static size_t getNumberParamsNeeded(std::string params){
	size_t i = 0;
	if (params[0] != '-') {
	if (params.find("l") != std::string::npos)
		i++;
	if (params.find("k") != std::string::npos)
		i++;
	}
	if (params.find("o") != std::string::npos)
		i++;
	return (i + 2);
}

static bool checkparams(const std::string &string){
	if (string.length() < 2 || (string[0] != '-' && string[0] != '+')) {
		return(false);
	}
	for (size_t i = 1; i < string.length(); i++) {
		if (string[i] != 'l' && string[i] != 'k' && string[i] != 'i'
			&& string[i] != 't' && string[i] != 'o') {
			return (false);
		}
	}
	return (true);
}

static bool checkArg(std::string &string){
	for (int i = 0; string[i]; i++){
		if (!std::isdigit(string[i]))
			return (false);
	}
	return (true);
}

void command_handler::_mode(irc_command const &command){
	if (command.params.size() < 1){
		_server.send_message(command.client, err_msg::need_more_params("MODE"));
		return;
	}
	if (command.params.size() == 2 && command.params[1] == "b")
		return;
	irc_channel *channel = _server.get_channel(command.params[0]);
	if (!channel){
		return ;
	}
	if (command.params.size() == 1){
		_server.send_message(command.client, rpl_msg::mode(command.client.nickname, channel->get_name(), channel->get_channel_mode()));
		return;
	}
	if (channel->isOpeChanel(command.client) == false && command.client.isOp == false){
		_server.send_message(command.client, err_msg::chan_op_privileges_needed(command.client.nickname, command.params[0]));
		return ;
	}
	if (checkparams(command.params[1]) == false){
		_server.send_message(command.client, err_msg::unknown_mode(command.params[1]));
		return;
	}
	if (command.params.size() < getNumberParamsNeeded(command.params[1])){
		_server.send_message(command.client, err_msg::need_more_params("MODE"));
		return;
	}
	std::vector<std::string> tmpParams(command.params);
	std::string tmpMode;
	char sign = tmpParams[1][0];
	for (size_t i = 1; i < tmpParams[1].length(); i++) {
		if (tmpParams[1][i] == 'o') {
			std::string target = sign == '-' ? tmpParams[2] : tmpParams[1 + i];
			irc_client *tmpClient = _server.get_client_by_name(target);
			if (tmpClient == NULL || !channel->has_client(tmpClient->fd)) {
				_server.send_message(command.client, err_msg::user_not_in_channel(command.client.nickname, channel->get_name()));
				return;
			} else if (channel->get_channel_owner() == tmpClient->nickname) {
				_server.send_message(command.client, err_msg::not_chan_owner(command.client.nickname, channel->get_name()));
				return;
			} else if (channel->setOperator(sign, *tmpClient) == true) {
				if (tmpMode.find("o") == std::string::npos)
					tmpMode += "o";
			}
		}
		else if (tmpParams[1][i] == 'i'){
			if (channel->invitMod(sign) == true && tmpMode.find("i") == std::string::npos)
				tmpMode += "i";
		}
		else if (tmpParams[1][i] == 't'){
			if (channel->topicCmd(sign) == true && tmpMode.find("t") == std::string::npos)
				tmpMode += "t";
		}
		else if (tmpParams[1][i] == 'k'){
			if (channel->setPass(sign, (sign == '+' ? tmpParams[1 + i] : "")) == true && tmpMode.find("k") == std::string::npos)
				tmpMode += "k";
		}
		else if (tmpParams[1][i] == 'l'){
			bool isvalid = true;
			if (sign != '-')
				isvalid = tmpParams.size() >= (1 + i) && checkArg(tmpParams[1 + i]);
			if(isvalid == true && channel->setUserLimit(sign, (sign != '-') ? std::atoi(tmpParams[1 + i].c_str()) : 0)
				&& tmpMode.find("l") == std::string::npos)
				tmpMode += "l";
		}
	}
	std::string msgSend = ":" + command.client.id + " MODE " + channel->get_name() + " " + sign + tmpMode;
	int i = 0;
	for (std::vector<std::string>::const_iterator it = command.params.begin(); it != command.params.end(); it++){
		if (i >= 2){
			msgSend += " ";
			msgSend += *it;
		}
		i++;
	}
	_server.broadcast(*channel, msgSend);
}
