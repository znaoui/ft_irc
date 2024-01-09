/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:50:34 by cdudzik           #+#    #+#             */
/*   Updated: 2023/07/13 00:04:47 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <string>
#include <vector>

struct irc_client
{
	int							fd;
	std::string					address;
	int							port;
	std::string					buffer;
	std::string					username;
	std::string					nickname;
	std::string					realname;
	std::string					hostname;
	std::string					id;
	bool						handshake_done;
	bool						passwd_sent;
	std::vector<std::string>	channels;
	std::vector<std::string>	invite;
	bool						isOp;
	std::string					away_msg;
	irc_client() : fd(-1), address(""), port(-1), buffer(""), nickname(""), realname(""), id(""), handshake_done(false), passwd_sent(false), isOp(false){}
};

#endif
