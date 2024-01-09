/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdudzik <cdudzik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 15:54:25 by cdudzik           #+#    #+#             */
/*   Updated: 2023/07/14 18:33:42 by cdudzik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include "channel.hpp"

irc_channel::irc_channel()
{
}

irc_channel::irc_channel(std::string const &name, std::string const& owner) : _name(name)
{
	_operators.push_back(owner);
	_owner = owner;
}

irc_channel::~irc_channel()
{
}

int irc_channel::clients_count() const {
	return (_clients.size());
}

std::string const &irc_channel::get_name() const
{
	return (_name);
}

bool irc_channel::add_client(irc_client& client)
{
	if (has_client(client.fd))
		return (false);
	_clients.insert(std::pair<int, irc_client&>(client.fd, client));
	_orderEntry.push_back(client.nickname);
	return (true);
}

bool irc_channel::remove_client(int fd)
{
	std::map<int, irc_client&>::iterator it = this->_clients.find(fd);
	if (it == this->_clients.end())
		return (false);
	if (isOpeChanel(it->second) == true)
		remove_operator(it->second);
	if (_owner == it->second.nickname && !_operators.empty())
		_owner = *_operators.begin();
	else if (_owner == it->second.nickname && _operators.empty()){
		_owner = *_orderEntry.begin();
	}

	_orderEntry.erase(std::find(_orderEntry.begin(), _orderEntry.end(), it->second.nickname));
	if (_operators.empty()){
		if (!this->_clients.empty()){
			_operators.push_back(*_orderEntry.begin());
		}
	}
	this->_clients.erase(it);
	return (true);
}

bool irc_channel::has_client(int fd) const
{
	return (_clients.find(fd) != _clients.end());
}

std::map<int, irc_client&> const &irc_channel::get_clients() const
{
	return (_clients);
}

bool irc_channel::isOpeChanel(irc_client &client){
	if (std::find(_operators.begin(), _operators.end(), client.nickname) != _operators.end())
		return(true);
	return (false);
}

void irc_channel::remove_operator(irc_client &client) {
	std::vector<std::string>::iterator it = find(_operators.begin(), _operators.end(), client.nickname);
	if (it != _operators.end())
		_operators.erase(it);
}

bool irc_channel::setPass(char i, std::string password){
	if (i == '-'){
		if (_mode.turnChannelKey == true){
			_mode.turnChannelKey = false;
			return (true);
		}
		else
			return (false);
	}
	else {
		if (_mode.turnChannelKey == false || password != _mode.password){
		_mode.password = password;
		_mode.turnChannelKey = true;
		return (true);
		}
		else
			return (false);
	}
}

bool irc_channel::topicCmd(char i){
	if (i == '-'){
		if (_mode.topicCmd == true){
			_mode.topicCmd = false;
			return (true);
		}
	}
	else{
		if (_mode.topicCmd == false){
			_mode.topicCmd = true;
			return (true);
		}
	}
	return (false);
}

bool irc_channel::invitMod(char i){
	if (i == '-'){
		if (_mode.onlyInvite == true){
			_mode.onlyInvite = false;
			return (true);
		}
	}
	else {
		if (_mode.onlyInvite == false){
			_mode.onlyInvite = true;
			return (true);
		}
	}
	return (false);
}

bool irc_channel::setOperator(char c, irc_client &client){
	if (c == '-'){
		if (isOpeChanel(client)){
			_operators.erase(std::find(_operators.begin(), _operators.end(), client.nickname));
			return (true);
		}
		else
			return (false);
	}
	else {
		if (isOpeChanel(client))
			return (false);
		else{
			_operators.push_back(client.nickname);
			return (true);
		}
	}
}

bool irc_channel::setUserLimit(char i, int limit){
	if (i == '-'){
		if (_mode.limitUser == true){
			_mode.limitUser = false;
			return (true);
		}
	}
	else{
		if (_mode.limitUser == false || limit != _mode.nbMaxUser){
			_mode.limitUser = true;
			_mode.nbMaxUser = limit;
			return (true);
		}
	}
	return (false);
}

std::string irc_channel::get_channel_mode(){
	std::string mode;
	if (this->_mode.onlyInvite == true)
		mode += "i";
	if (this->_mode.topicCmd == true)
		mode += "t";
	if (this->_mode.turnChannelKey == true)
		mode += "k";
	if (this->_mode.limitUser == true)
		mode += "l " + ft_to_string(this->_mode.nbMaxUser);
	if (!mode.empty())
		mode = "+" + mode;
	return (mode);
}

std::string irc_channel::get_pass(){
	return (this->_mode.password);
}


std::string irc_channel::get_channel_owner(){
	return (_owner);
}

void irc_channel::set_topic(std::string topic, std::string set_by, std::string date){
	this->_topic.topic = topic;
	this->_topic.set_by = set_by;
	this->_topic.date = date;
}

irc_channel::irc_topic irc_channel::get_topic(){
	return (_topic);
}

int irc_channel::getClientsLimit() const{
	return (_mode.nbMaxUser);
}

void irc_channel::addToBan(std::string name){
	_banList.push_back(name);
}

void irc_channel::unban(std::string name){
	std::vector<std::string>::iterator it = std::find(_banList.begin(), _banList.end(), name);
	if (it != _banList.end())
		_banList.erase(it);
}

bool irc_channel::isBan(std::string name){
	return (std::find(_banList.begin(), _banList.end(), name) != _banList.end());
}
