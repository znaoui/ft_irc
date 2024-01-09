/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc_command.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:50:19 by cdudzik           #+#    #+#             */
/*   Updated: 2023/05/26 15:52:09 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_COMMAND_HPP
# define IRC_COMMAND_HPP

# include <string>
# include <vector>
# include "../server/client.hpp"

struct irc_command
{
	irc_client& client;
	std::string command;
	std::vector<std::string> params;
	irc_command(irc_client& client) : client(client) {}
};

#endif
