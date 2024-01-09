/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_msg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:34:06 by cdudzik           #+#    #+#             */
/*   Updated: 2023/07/12 19:14:15 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_msg.hpp"

std::string cmd_msg::part(std::string const &channel)
{
	return ("PART " + channel);
}

std::string cmd_msg::kick(std::string const &channel, std::string const &src, std::string const &dst, std::string const &reason){
	return ("KICK " + channel + " " + dst + " " + src + " :" + reason);
}

std::string cmd_msg::oper(std::string const &nickname){
	return("MODE " + nickname + " +o");
}

std::string cmd_msg::kill(std::string const &nickname, std::string const &reason){
	return ("KILL " + nickname + " :You have been killed :" + reason);
}

std::string cmd_msg::away(std::string const &nickname)
{
	return ("306 " + nickname + " :You have been marked as being away");
}

std::string cmd_msg::away_unset(std::string const &nickname)
{
	return ("305 " + nickname + " :You are no longer marked as being away");
}

std::string cmd_msg::topic(std::string const& id, std::string const &channel, std::string const &topic){
	return (":" + id + " TOPIC " + channel + " :" + topic);
}

std::string cmd_msg::invite(std::string const& id, std::string const &target_nickname, std::string const &channel){
	return (":" + id + " INVITE " + target_nickname + " " + channel);
}

std::string cmd_msg::ban(std::string const &dest_name){
	return (dest_name + " get ban from the channel");
}

std::string cmd_msg::ban(std::string const& channel, std::string const &sender){
	return ("you get ban by " + sender + " from the chanel " + channel);
}

std::string cmd_msg::unban(std::string const &channel){
	return ("you get unban from the channel " + channel);
}
