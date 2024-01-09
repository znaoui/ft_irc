/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:51:44 by cdudzik           #+#    #+#             */
/*   Updated: 2023/07/12 17:03:46 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <string>
#include <vector>
#include <map>
#include "client.hpp"
#include "channel_mode.h"
#include "../utils/utils.hpp"

class irc_channel
{
	public:
		struct irc_topic {
			std::string		topic;
			std::string		set_by;
			std::string		date;
		};

		irc_channel();
		irc_channel(std::string const &name, std::string const &owner);
		~irc_channel();

		std::string const &get_name() const;
		bool add_client(irc_client& client);
		bool remove_client(int fd);
		bool has_client(int fd) const;
		std::map<int, irc_client&> const &get_clients() const;
		void remove_operator(irc_client &client);
		bool isOpeChanel(irc_client &client);
		int clients_count() const;
		bool invitMod(char i);
		bool topicCmd(char i);
		std::string	get_channel_mode();
		std::string	get_channel_owner();
		bool setOperator(char c, irc_client &client);
		std::string get_pass();
		irc_topic get_topic();
		void set_topic(std::string topic, std::string set_by, std::string date);
		bool setPass(char i, std::string password);
		bool setUserLimit(char i, int limit);
		int getClientsLimit() const;
		void addToBan(std::string name);
		void unban(std::string name);
		bool isBan(std::string name);


	private:
		channel_mode				_mode;
		std::string					_name;
		std::map<int, irc_client&>	_clients;
		std::vector<std::string>	_operators;
		std::vector<std::string>	_orderEntry;
		std::string					_owner;
		irc_topic					_topic;
		std::vector<std::string>	_banList;
};

#endif
