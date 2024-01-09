/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:31:33 by cdudzik           #+#    #+#             */
/*   Updated: 2023/07/12 19:10:34 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_MSG_HPP
# define ERR_MSG_HPP

#include <string>

class err_msg
{
	public:
		static std::string const no_such_nick(std::string const &nickname);
		static std::string const no_such_channel(std::string const &channel_name);
		static std::string const cannot_send_to_chan(std::string const &channel_name);
		static std::string const too_many_channels(std::string const &channel_name);
		static std::string const no_origin();
		static std::string const no_recipient();
		static std::string const no_text_to_send();
		static std::string const unknown_command(std::string const &command);
		static std::string const no_motd();
		static std::string const no_admin_info(std::string const &server_name);
		static std::string const file_error(std::string const &file_name, std::string const &error_message);
		static std::string const no_nickname_given();
		static std::string const erronous_nickname(std::string const &nickname);
		static std::string const nickname_in_use(std::string const &nickname);
		static std::string const user_not_in_channel(std::string const &nickname, std::string const &channel_name);
		static std::string const not_on_channel(std::string const &channel_name);
		static std::string const user_on_channel(std::string const &nickname, std::string const &channel_name);
		static std::string const not_registered();
		static std::string const need_more_params(std::string const &command);
		static std::string const already_registered();
		static std::string const password_mismatch();
		static std::string const youre_banned_creeper();
		static std::string const unknown_mode(std::string const &mode);
		static std::string const invite_only_chan(std::string const& channel, std::string const &nickname);
		static std::string const banned_from_chan(std::string const &channel_name, std::string const& nickname);
		static std::string const no_privileges();
		static std::string const chan_op_privileges_needed(std::string const &name, std::string const &channel_name);
		static std::string const unknown_user_mode();
		static std::string const wrong_channel_key(std::string const &channel_name, std::string const& nickname);
 		static std::string const no_op_mode(std::string const &command_name, std::string const &channel_name);
		static std::string const to_many_people_chan(std::string const& nickname, std::string const &channel_name);
		static std::string const users_do_not_match();
		static std::string const is_not_ban(std::string const &nickname);
		static std::string const youre_ban(std::string const &channelName);
		static std::string const not_chan_owner(std::string const &name, std::string const &channel_name);
};

#endif
