#include "User.hpp"
#include <memory>


void User::setnewPassword(std::string& repassword)
{
	this->_newPassword = _newPassword;// ���� ������� ����� - ����� ����� ����� �� Check-Valid
}

void User::setnewName(std::string& rename)
{
	this->_newName = _newName;// ���� ������� ����� - ����� ����� ����� �� Check-Valid
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

std::string const& User::getnewPassword()
{
	return this->_newPassword;// TODO: �������� ����� �������� return
}

std::string const& User::getnewName()
{
	return this->_newName;// TODO: �������� ����� �������� return
}
