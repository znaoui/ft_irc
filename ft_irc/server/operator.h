/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc_operator.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 17:02:29 by cdudzik           #+#    #+#             */
/*   Updated: 2023/06/18 17:02:40 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_OPERATOR_H
# define IRC_OPERATOR_H

# include <string>

struct irc_operator {
	std::string password;
	irc_operator(std::string pass) : password(pass) {};
};

#endif
