/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ircserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:10:41 by cdudzik           #+#    #+#             */
/*   Updated: 2023/05/17 20:39:13 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "server/server.hpp"
#include "utils/utils.hpp"

int main(int argc, char **argv)
{
	int port;
	if (argc != 3) {
		std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
		return (1);
	}
	try {
		port = ft_stoi(argv[1]);
		if (port < 0 || port > 65535)
			throw "Invalid port";
	} catch (...) {
		std::cerr << "Invalid port, must be between 0 and 65535" << std::endl;
		return (1);
	}
	irc_server server(port, argv[2]);
	return server.run();
}
