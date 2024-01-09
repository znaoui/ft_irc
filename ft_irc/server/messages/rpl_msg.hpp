/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl_msg.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:59:30 by cdudzik           #+#    #+#             */
/*   Updated: 2023/07/12 17:19:41 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPL_MSG_HPP
# define RPL_MSG_HPP

#include <string>

class rpl_msg
{
	public:
		static std::string welcome(std::string const &nickname);
		static std::string created(std::string const &date);
		static std::string myinfo(std::string const &server_name, std::string const &version, std::string const &available_user_modes, std::string const &available_channel_modes);
		static std::string motdstart(std::string const &nickname, std::string const &server_name);
		static std::string motd(std::string const &motd_line);
		static std::string motdend(std::string const &nickname);
		static std::string topic(std::string const &channel_name, std::string const &topic, std::string const &nickname);
		static std::string topic_set_by(std::string const &channel_name, std::string const &nickname, std::string const &date);
		static std::string notopic(std::string const &channel_name, std::string const &nickname);
		static std::string oper(std::string const &nickname);
		static std::string kill(std::string const &nickname);
		static std::string names(std::string const &channel_name, std::string const& nickname, std::string const &nicknames);
		static std::string names_end(std::string const &channel_name, std::string const& nickname);
		static std::string who(std::string const &nickname, std::string const &channel, std::string const &username, std::string const &hostname, std::string const &realname, std::string const &server_name, bool away, std::string const &operator_status);
		static std::string who_end(std::string const &nickname, std::string const &channel);
		static std::string whois_user(std::string const &nickname, std::string const& target, std::string const &username, std::string const &hostname, std::string const &realname);
		static std::string whois_server(std::string const &nickname, std::string const& target, std::string const &server_name, std::string const &server_info);
		static std::string whois_operator(std::string const &nickname, std::string const& target);
		static std::string whois_channels(std::string const &nickname, std::string const& target, std::string const &channels);
		static std::string whois_end(std::string const &nickname, std::string const& target);
		static std::string whois_away(std::string const &nickname, std::string const &target, std::string const &away_message);
		static std::string mode(std::string const&nickname, std::string const&channel_name, std::string const &enableModes);
};

#endif
