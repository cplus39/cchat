#include "User.hpp"
#include <memory>


void User::setNewPassword(const std::string& repassword)
{
	this->_password = repassword;// ���� ������� ����� - ����� ����� ����� �� Check-Valid
}

void User::setNewName(const std::string& rename)
{
	this->_name = rename;// ���� ������� ����� - ����� ����� ����� �� Check-Valid
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

