/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_conv.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 20:32:22 by cdudzik           #+#    #+#             */
/*   Updated: 2023/05/26 16:39:27 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <sstream>
#include <errno.h>
#include <limits.h>
#include <cstdlib>

std::string trim(const std::string& str) {
	size_t first = str.find_first_not_of(' ');
	if (first == std::string::npos) {
		return "";
	}
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}

int ft_stoi(const std::string& str) {
	char* endPtr;
	long value = std::strtol(str.c_str(), &endPtr, 10);
	if (endPtr == str.c_str() || *endPtr != '\0') {
		throw std::invalid_argument("ft_stoi: invalid argument");
	} else if ((value == LONG_MIN || value == LONG_MAX) && errno == ERANGE) {
		throw std::invalid_argument("ft_stoi: invalid argument");
	} else if (value < INT_MIN || value > INT_MAX) {
		throw std::out_of_range("ft_stoi: out of range");
	}
	return static_cast<int>(value);
}

std::string ft_to_string(int value) {
	std::ostringstream os;
	os << value;
	return os.str();
}
