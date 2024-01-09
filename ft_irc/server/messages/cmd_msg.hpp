/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_msg.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:33:36 by cdudzik           #+#    #+#             */
/*   Updated: 2023/07/12 19:14:35 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_MSG_HPP
# define CMD_MSG_HPP

#include <string>

class cmd_msg
{
	public:
		static std::string part(std::string const &channel);
		static std::string kick(std::string const &channel, std::string const &src, std::string const &dst, std::string const &reason);
		static std::string oper(std::string const &nickname);
		static std::string kill(std::string const &nickname, std::string const &reason);
		static std::string away(std::string const &nickname);
		static std::string away_unset(std::string const &nickname);
		static std::string invite(std::string const& id, std::string const &target_nickname, std::string const &channel);
		static std::string topic(std::string const& id, std::string const &channel, std::string const &topic);
		static std::string ban(std::string const& channel, std::string const &sender);
		static std::string ban(std::string const &dest_name);
		static std::string unban(std::string const &channel);
};

#endif
