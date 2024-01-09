/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:49:15 by cdudzik           #+#    #+#             */
/*   Updated: 2023/07/14 18:38:37 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_HPP
# define LOGGER_HPP

# define BUILD_DEBUG 1

#include <string>
#include <fstream>

class logger
{
	public:
		logger();
		~logger();

		void info(std::string const &str);
		void debug(std::string const &str);
		void warning(std::string const &str);
		void error(std::string const &str);

	private:
		enum log_level
		{
			INFO,
			DEBUG,
			WARNING,
			ERROR
		};

		static const std::string ORANGE;
		static const std::string RED;
		static const std::string GREEN;
		static const std::string BLUE;
		static const std::string RESET;

		void _log(log_level level, std::string const &str);
		std::string _get_time();
};

#endif
