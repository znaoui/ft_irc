/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:53:23 by cdudzik           #+#    #+#             */
/*   Updated: 2023/06/27 01:39:47 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <ctime>
#include "logger.hpp"

const std::string logger::ORANGE = "\033[38;5;208m";
const std::string logger::RED = "\033[38;5;196m";
const std::string logger::GREEN = "\033[38;5;46m";
const std::string logger::BLUE = "\033[38;5;45m";
const std::string logger::RESET = "\033[0m";

logger::logger()
{
}

logger::~logger()
{
}

void logger::_log(log_level level, std::string const &str)
{
	std::string time = _get_time();
	switch (level)
	{
		case INFO:
			std::cout << time << GREEN << " [INFO] " << RESET << str << std::endl;
			break;
		case DEBUG:
			std::cout << time << BLUE << " [DEBUG] " << RESET << str<< std::endl;
			break;
		case WARNING:
			std::cerr << time << ORANGE << " [WARNING] " << RESET << str << std::endl;
			break;
		case ERROR:
			std::cerr << time << RED << " [ERROR] " << RESET << str << std::endl;
			break;
		default:
			break;
	}
}

void logger::info(std::string const &str)
{
	_log(INFO, str);
}

void logger::debug(std::string const &str)
{
	if (BUILD_DEBUG)
		_log(DEBUG, str);
}

void logger::warning(std::string const &str)
{
	_log(WARNING, str);
}

void logger::error(std::string const &str)
{
	_log(ERROR, str);
}

std::string logger::_get_time()
{
	std::time_t currentTime = std::time(0);
	std::tm* localTime = std::localtime(&currentTime);
	char timeBuffer[9];
	std::strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", localTime);
	return std::string("[") + timeBuffer + "]";
}
