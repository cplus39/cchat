#include "User.hpp"


void User::setPassword(std::string& login)
{

}

void User::setName(std::string& name)
{

}

std::string const &User::getLogin()
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
