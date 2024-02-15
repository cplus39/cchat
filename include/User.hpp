#pragma once

#include <string>
#include <memory>

class User
{
	std::string _login;
	std::string _password;
	std::string _name;
	
public:
	User(const std::string& login, const std::string& password,	const std::string& name) : _login(login),_password(password),_name(name) {};

	void setNewPassword(const std::string& newPassword);
	void setNewName(const std::string& newName);
	


	std::string const& getLogin();
	std::string const& getPassword();
	std::string const& getName();
	};