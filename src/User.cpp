#include "User.hpp"
#include "sha256.h"

void User::setNewPassword(const std::string& newPassword)
{
	this->_password = sha256(newPassword);
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

