/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_msg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 21:01:15 by cdudzik           #+#    #+#             */
/*   Updated: 2023/07/12 16:58:26 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rpl_msg.hpp"

std::string rpl_msg::welcome(std::string const &nickname)
{
	return ("001 " + nickname + " :Welcome to the 42_ft_irc server " + nickname);
}

std::string rpl_msg::created(std::string const &date)
{
	return ("003 :This server was created " + date);
}

std::string rpl_msg::myinfo(std::string const &server_name, std::string const &version, std::string const &available_user_modes, std::string const &available_channel_modes)
{
	return ("004 " + server_name + " " + version + " " + available_user_modes + " " + available_channel_modes);
}

std::string rpl_msg::motdstart(std::string const &nickname, std::string const &server_name)
{
	return ("375 " + nickname + " :- " + server_name + " Message of the day - ");
}

std::string rpl_msg::motd(std::string const &motd_line)
{
	return ("372 :- " + motd_line);
}

std::string rpl_msg::motdend(std::string const &nickname)
{
	return ("376 " + nickname + " :End of /MOTD command");
}

std::string rpl_msg::notopic(std::string const &channel_name, std::string const &nickname)
{
	return ("332 " + nickname + " " + channel_name + " :");
}

std::string rpl_msg::topic(std::string const &channel_name, std::string const &topic, std::string const &nickname)
{
	return ("332 " + nickname + " " + channel_name + " :" + topic);
}

std::string rpl_msg::topic_set_by(std::string const &channel_name, std::string const &nickname, std::string const &date)
{
	return ("333 " + nickname + " " + channel_name + " " + date);
}

std::string rpl_msg::oper(std::string const &nickname){
	return("381 " + nickname + ": You are now an IRC operator");
}

std::string rpl_msg::kill(std::string const &nickname){
	return("361 " + nickname + "User has been killed");
}

std::string rpl_msg::names(std::string const &channel_name, std::string const& nickname, std::string const &nicknames){
	return("353 " + nickname + " = " + channel_name + " :" + nicknames);
}

std::string rpl_msg::names_end(std::string const &channel_name, std::string const& nickname){
	return("366 " + nickname + " " + channel_name + " :End of NAMES list");
}

std::string rpl_msg::who(std::string const &nickname, std::string const &channel, std::string const &username, std::string const &hostname, std::string const &realname, std::string const &server_name, bool away, std::string const &operator_status) {
	return("352 " + nickname + " " + channel + " " + username + " " + hostname + " " + server_name + " " + nickname + " " + (away ? "G" : "H") + operator_status + " :0 " + realname);
}

std::string rpl_msg::who_end(std::string const &nickname, std::string const &channel) {
	return("315 " + nickname + " " + channel + " :End of WHO list");
}

std::string rpl_msg::whois_user(std::string const &nickname, std::string const &target, std::string const &username, std::string const &hostname, std::string const &realname) {
	return("311 " + nickname + " " + target + " " + username + " " + hostname + " * :" + realname);
}

std::string rpl_msg::whois_server(std::string const &nickname, std::string const &target, std::string const &server_name, std::string const &server_info) {
	return("312 " + nickname + " " + target + " " + server_name + " :" + server_info);
}

std::string rpl_msg::whois_operator(std::string const &nickname, std::string const &target) {
	return("313 " + nickname + " " + target + " :is an IRC operator");
}

std::string rpl_msg::whois_channels(std::string const &nickname, std::string const &target, std::string const &channels) {
	return("319 " + nickname + " " + target + " :" + channels);
}

std::string rpl_msg::whois_end(std::string const &nickname, std::string const &target) {
	return("318 " + nickname + " " + target + " :End of WHOIS list");
}

std::string rpl_msg::whois_away(std::string const &nickname, std::string const &target, std::string const &away_message) {
	return("301 " + nickname + " " + target + " :" + away_message);
}

std::string rpl_msg::mode(std::string const &nickname, std::string const&channel_name, std::string const &enableModes){
	return ("324 " + nickname + " " + channel_name + " " + enableModes);
}

