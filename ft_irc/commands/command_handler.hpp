/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:46:51 by cdudzik           #+#    #+#             */
/*   Updated: 2023/07/14 17:55:02 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HANDLER_HPP
# define COMMAND_HANDLER_HPP

#include <string>
#include <map>
#include "../server/client.hpp"
#include "./irc_command.hpp"
#include "../utils/logger.hpp"

class irc_server;

class command_handler
{
	typedef void (command_handler::*CmdHandler)(irc_command const &);

	public:
		command_handler(irc_server& server, logger &logger);
		~command_handler();

		static const std::string ALLOWED_NICKNAME_CHARACTERS;
		static const std::string ALLOWED_MSG_CHARACTERS;

		int handle(irc_command const &command);

	private:
		irc_server& _server;
		void _dump_command(irc_command const &command);
		logger &_logger;

		//commands
		std::map<std::string, CmdHandler> _commands;
		void _check_handcheck_status(irc_client &client);
		void _pass(irc_command const &command);
		void _nick(irc_command const &command);
		void _user(irc_command const &command);
		void _cap(irc_command const &command);
		void _ping(irc_command const &command);
		void _join(irc_command const &command);
		void _quit(irc_command const &command);
		void _privmsg(irc_command const &command);
		void _part(irc_command const &command);
		void _kick(irc_command const &command);
		void _oper(irc_command const &command);
		void _kill(irc_command const &command);
		void _notice(irc_command const &command);
		void _away(irc_command const &command);
		void _motd(irc_command const &command);
		void _who(irc_command const &command);
		void _whois(irc_command const &command);
		void _mode(irc_command const &command);
		void _topic(irc_command const& command);
		void _invite(irc_command const &command);
		void _squit(irc_command const &command);
};

#endif
