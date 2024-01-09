#include "implementation_base.hpp"
#include <algorithm>
#include <ctime>
#include <sstream>

static std::string get_unix_timestamp()
{
	std::time_t current = std::time(0);
	long unix_timestamp = static_cast<long> (current);
	std::ostringstream ss;
	ss << unix_timestamp;
	return ss.str();
}

void	command_handler::_topic(irc_command const& command){
	if (command.params.size() < 1 || command.params.size() > 2){
		_server.send_message(command.client, err_msg::need_more_params("TOPIC"));
		return;
	}
	irc_channel *channel = _server.get_channel(command.params[0]);
	if (!channel){
		_server.send_message(command.client, err_msg::no_such_channel(command.params[0]));
		return;
	}
	if (channel->has_client(command.client.fd) == false){
		_server.send_message(command.client, err_msg::not_on_channel(command.params[0]));
		return;
	}
	if (command.params.size() == 1) {
		irc_channel::irc_topic topic = channel->get_topic();
		if (topic.topic.empty())
			_server.send_message(command.client, rpl_msg::notopic(channel->get_name(), command.client.nickname));
		else
			_server.send_message(command.client, rpl_msg::topic_set_by(channel->get_name(), topic.set_by, topic.date));
	} else {
		if (channel->get_channel_mode().find("t") != std::string::npos)
		{
			if (channel->isOpeChanel(command.client) == false && command.client.isOp == false)
			{
				_server.send_message(command.client, err_msg::chan_op_privileges_needed(command.client.nickname, channel->get_name()));
				return ;
			}
		}
		channel->set_topic(command.params[1], command.client.nickname, get_unix_timestamp());
		_server.broadcast(*channel, cmd_msg::topic(command.client.id, channel->get_name(), command.params[1]));
	}
}
