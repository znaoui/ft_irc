/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:52:29 by cdudzik           #+#    #+#             */
/*   Updated: 2023/07/12 19:17:53 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "err_msg.hpp"

std::string const err_msg::no_such_nick(std::string const &nickname)
{
	return ("401 " + nickname + " :No such nick/channel");
}

std::string const err_msg::no_such_channel(std::string const &channel_name)
{
	return ("403 " + channel_name + " :No such channel");
}

std::string const err_msg::cannot_send_to_chan(std::string const &channel_name)
{
	return ("404 " + channel_name + " :Cannot send to channel");
}

std::string const err_msg::too_many_channels(std::string const &channel_name)
{
	return ("405 " + channel_name + " :You have joined too many channels");
}

std::string const err_msg::no_origin()
{
	return ("409 :No origin specified");
}

std::string const err_msg::no_recipient()
{
	return ("411 :No recipient given");
}

std::string const err_msg::no_text_to_send()
{
	return ("412 :No text to send");
}

std::string const err_msg::unknown_command(std::string const &command)
{
	return ("421 " + command + " :Unknown command");
}

std::string const err_msg::no_motd()
{
	return ("422 :MOTD File is missing");
}

std::string const err_msg::no_admin_info(std::string const &server_name)
{
	return ("423 " + server_name + " :No administrative info available");
}

std::string const err_msg::file_error(std::string const &file_name, std::string const &error_message)
{
	return ("424 " + file_name + " :File error doing " + error_message);
}

std::string const err_msg::no_nickname_given()
{
	return ("431 :No nickname given");
}

std::string const err_msg::erronous_nickname(std::string const &nickname)
{
	return ("432 " + nickname + " :Erroneous nickname");
}

std::string const err_msg::nickname_in_use(std::string const &nickname)
{
	return ("433 " + nickname + " :Nickname is already in use");
}

std::string const err_msg::user_not_in_channel(std::string const &nickname, std::string const &channel_name)
{
	return ("441 " + nickname + " " + channel_name + " :They aren't on that channel");
}

std::string const err_msg::not_on_channel(std::string const &channel_name)
{
	return ("442 " + channel_name + " :You're not on that channel");
}

std::string const err_msg::user_on_channel(std::string const &nickname, std::string const &channel_name)
{
	return ("443 " + nickname + " " + channel_name + " :is already on channel");
}

std::string const err_msg::not_registered()
{
	return ("451 :You have not registered");
}

std::string const err_msg::need_more_params(std::string const &command)
{
	return ("461 " + command + " :Not enough parameters");
}

std::string const err_msg::already_registered()
{
	return ("462 :Unauthorized command (already registered)");
}

std::string const err_msg::password_mismatch()
{
	return ("464 :Password incorrect");
}

std::string const err_msg::youre_banned_creeper()
{
	return ("465 :You are banned from this server");
}

std::string const err_msg::to_many_people_chan(std::string const& nickname, std::string const &channel_name)
{
	return ("471 " + nickname + " " + channel_name + " :Cannot join channel (+l) -- Channel is full, try later");
}

std::string const err_msg::invite_only_chan(std::string const& channel, std::string const &nickname)
{
	return ("473 " + nickname + " " + channel + " :Cannot join channel (+i) -- Invited users only");
}

std::string const err_msg::banned_from_chan(std::string const &channel_name, std::string const& nickname)
{
	return ("474 " + nickname + " " + channel_name + " :Cannot join channel (+b)");
}

std::string const err_msg::wrong_channel_key(std::string const &channel_name, std::string const& nickname)
{
	return ("475 " + nickname + " " + channel_name + " :Cannot join channel (+k) - bad channel key");
}

std::string const err_msg::no_privileges()
{
	return ("481 :Permission Denied- You're not an IRC operator");
}

std::string const err_msg::chan_op_privileges_needed(std::string const &name, std::string const &channel_name)
{
	return ("482 " + name + " " + channel_name + " :You're not channel operator");
}

std::string const err_msg::not_chan_owner(std::string const &name, std::string const &channel_name)
{
	return ("482 " + name + " " + channel_name + " :Not permitted on channel owner");
}

std::string const err_msg::unknown_mode(std::string const &mode)
{
	return ("501 " + mode + " :Unknown MODE flag");
}

std::string const err_msg::unknown_user_mode()
{
	return ("501 :Unknown MODE flag");
}

std::string const err_msg::users_do_not_match()
{
	return ("502 :Cant change mode for other users");
}

std::string const err_msg::is_not_ban(std::string const &nickname){
	return(nickname + " is not ban from the channel");
}

std::string const err_msg::youre_ban(std::string const &channelName){
	return ("you cannot join " + channelName + ": you get ban from it");
}
