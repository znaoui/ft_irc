/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broadcast_msg.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:59:38 by cdudzik           #+#    #+#             */
/*   Updated: 2023/06/19 15:21:44 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BROADCAST_MSG_HPP
# define BROADCAST_MSG_HPP

#include <string>

class broadcast_msg
{
	public:
		static std::string join(std::string const &nick, std::string const &channel);
		static std::string priv_msg(std::string const &nick, std::string const &msg, std::string const &channel);
		static std::string quit(std::string const &nick, std::string const &msg);
		static std::string nick(std::string const &old_nick, std::string const &new_nick);
		static std::string part(std::string const &nick, std::string const &channel);
		static std::string kick(std::string const &channel, std::string const &nick, std::string const &dest, std::string const &reason);
		static std::string notice(std::string const &nick, std::string const &target, std::string const &msg);
		static std::string mode(std::string const &channel, std::string const &mode, std::string const &password);
};

#endif
