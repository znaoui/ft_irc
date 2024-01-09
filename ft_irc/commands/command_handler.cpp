/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:45:37 by cdudzik           #+#    #+#             */
/*   Updated: 2023/07/14 18:23:01 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_handler.hpp"
#include "../utils/utils.hpp"
#include "../server/messages/err_msg.hpp"
#include "../server/messages/rpl_msg.hpp"
#include "../server/server.hpp"

const std::string command_handler::ALLOWED_NICKNAME_CHARACTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-|";
const std::string command_handler::ALLOWED_MSG_CHARACTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_-|!@#$%^&*()_+{}[]|\\:\";'<>?,./";

command_handler::command_handler(irc_server& server, logger& logger) : _server(server), _logger(logger)
{
	_commands["KILL"] = &command_handler::_kill;
	_commands["NICK"] = &command_handler::_nick;
	_commands["USER"] = &command_handler::_user;
	_commands["PASS"] = &command_handler::_pass;
	_commands["CAP"] = &command_handler::_cap;
	_commands["PING"] = &command_handler::_ping;
	_commands["JOIN"] = &command_handler::_join;
	_commands["QUIT"] = &command_handler::_quit;
	_commands["PRIVMSG"] = &command_handler::_privmsg;
	_commands["PART"] = &command_handler::_part;
	_commands["KICK"] = &command_handler::_kick;
	_commands["OPER"] = &command_handler::_oper;
	_commands["NOTICE"] = &command_handler::_notice;
	_commands["AWAY"] = &command_handler::_away;
	_commands["MOTD"] = &command_handler::_motd;
	_commands["WHO"] = &command_handler::_who;
	_commands["WHOIS"] = &command_handler::_whois;
	_commands["TOPIC"] = &command_handler::_topic;
	_commands["MODE"] = &command_handler::_mode;
	_commands["INVITE"] = &command_handler::_invite;
	_commands["SQUIT"] = &command_handler::_squit;
}

command_handler::~command_handler()
{
}

int command_handler::handle(irc_command const &command)
{
	// _dump_command(command);
	if (!command.client.handshake_done && command.command != "NICK" && command.command != "USER" && command.command != "PASS" && command.command != "CAP") {
		_logger.error("Client " + ft_to_string(command.client.fd) + " (" + command.client.address + ":" + ft_to_string(command.client.port) + ") sent command '" + command.command + "' before handshake");
		_server.send_message(command.client, err_msg::not_registered());
		return 0;
	}
	if (_commands.find(command.command) == _commands.end()) {
		_logger.error("Client " + ft_to_string(command.client.fd) + " (" + command.client.address + ":" + ft_to_string(command.client.port) + ") sent unknown command '" + command.command + "'");
		_server.send_message(command.client, err_msg::unknown_command(command.command));
		return 0;
	}
	try {
		(this->*_commands[command.command])(command);
		if (command.command == "QUIT" || command.command == "SQUIT")
			return (1);
	} catch(const std::exception& e) {
		_logger.error("Error processing command '" + command.command + "': " + e.what() + " (client " + ft_to_string(command.client.fd) + " (" + command.client.address + ":" + ft_to_string(command.client.port) + "))");
	}
	return (0);
}

void command_handler::_check_handcheck_status(irc_client& client)
{
	if (!client.handshake_done && !client.nickname.empty() && !client.realname.empty() && client.passwd_sent) {
		client.handshake_done = true;
		client.id = client.nickname + "!" + client.username + "@" + client.hostname;
		_logger.debug("Client " + ft_to_string(client.fd) + " (" + client.address + ":" + ft_to_string(client.port) + ") handshake done, sending MOTD");
		std::string motd = rpl_msg::welcome(client.nickname);
		motd += ("\n" + rpl_msg::motdstart(client.nickname, "42_ft_irc"));
		motd += ("\n" +rpl_msg::motd("        :::      ::::::::"));
		motd += ("\n" +rpl_msg::motd("        :::      ::::::::"));
		motd += ("\n" +rpl_msg::motd("      :+:      :+:    :+:"));
		motd += ("\n" +rpl_msg::motd("    +:+ +:+         +:+  "));
		motd += ("\n" +rpl_msg::motd("  +#+  +:+       +#+     "));
		motd += ("\n" +rpl_msg::motd("+#+#+#+#+#+   +#+        "));
		motd += ("\n" +rpl_msg::motd("     #+#    #+#          "));
		motd += ("\n" +rpl_msg::motd("    ###   ########.fr    "));
		motd += ("\n" +rpl_msg::motdend(client.nickname));
		_server.send_message(client, motd);
	}
}

void command_handler::_dump_command(irc_command const &command)
{
	std::string str = "Command dump from client '" + command.client.nickname + "' (fd " + ft_to_string(command.client.fd) + ")\n";
	str += "Command: " + command.command + "\nParameters:\n";
	for (std::vector<std::string>::const_iterator it = command.params.begin(); it != command.params.end(); ++it)
		str += *it + "\n";
	str += "-------------\n";
	_logger.debug(str);
}
