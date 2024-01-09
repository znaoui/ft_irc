/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broadcast_msg.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:37:02 by cdudzik           #+#    #+#             */
/*   Updated: 2023/06/19 15:22:00 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "broadcast_msg.hpp"

std::string broadcast_msg::join(std::string const &nick, std::string const &channel)
{
	return (":" + nick + " JOIN " + channel);
}

std::string broadcast_msg::priv_msg(std::string const &nick, std::string const &msg, std::string const &channel)
{
	return (":" + nick + " PRIVMSG " + channel + " :" + msg);
}

std::string broadcast_msg::quit(std::string const &nick, std::string const &msg)
{
	return (":" + nick + " QUIT :" + msg);
}

std::string broadcast_msg::nick(std::string const &old_nick, std::string const &new_nick)
{
	return (":" + old_nick + " NICK :" + new_nick);
}

std::string broadcast_msg::part(std::string const &nick, std::string const &channel)
{
	return (":" + nick + " PART " + channel + " :");
}

std::string broadcast_msg::notice(std::string const &nick, std::string const &target, std::string const &msg)
{
	return (":" + nick + " NOTICE " + target + " :" + msg);
}

std::string broadcast_msg::kick(std::string const &channel, std::string const &nick, std::string const &dest, std::string const &reason){
	return (":" + nick + " KICK " + channel + " " + dest + " :" + reason);
}

std::string broadcast_msg::mode(std::string const &channel, std::string const& mode, std::string const &password){
	return (": MODE " + channel + " " + mode + password);
}
