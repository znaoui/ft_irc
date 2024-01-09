/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motd.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:01:33 by cdudzik           #+#    #+#             */
/*   Updated: 2023/06/19 17:24:07 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implementation_base.hpp"

void command_handler::_motd(irc_command const& command)
{
	std::string motd = rpl_msg::motdstart(command.client.nickname, "42_ft_irc");
	motd += ("\n" +rpl_msg::motd("        :::      ::::::::"));
	motd += ("\n" +rpl_msg::motd("        :::      ::::::::"));
	motd += ("\n" +rpl_msg::motd("      :+:      :+:    :+:"));
	motd += ("\n" +rpl_msg::motd("    +:+ +:+         +:+  "));
	motd += ("\n" +rpl_msg::motd("  +#+  +:+       +#+     "));
	motd += ("\n" +rpl_msg::motd("+#+#+#+#+#+   +#+        "));
	motd += ("\n" +rpl_msg::motd("     #+#    #+#          "));
	motd += ("\n" +rpl_msg::motd("    ###   ########.fr    "));
	motd += ("\n" +rpl_msg::motdend(command.client.nickname));
	_server.send_message(command.client, motd);
}
