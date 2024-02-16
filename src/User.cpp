#include "User.hpp"



void User::setNewPassword(const std::string& newPassword)
{
	this->_password = newPassword;
}

void User::setNewName(const std::string& newName)
{
	this->_name = newName;
}

std::string const& User::getLogin()
{
	return this->_login;
}

std::string const& User::getPassword()
{
	return this->_password;
}

std::string const& User::getName()
{
	return this->_name;
}

