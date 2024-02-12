#pragma once

#include <string>

class User
{
	std::string _login;
	std::string _password;
	std::string _name;
	std::string _newPassword;
	std::string _newName;
	
public:
	User
	(const std::string& login, const std::string& password,	const std::string& name, const std::string& newPassword, const std::string& newName) : _login(login),_password(password),_name(name), _newPassword(newPassword), _newName(newName)
	{};

	void setnewPassword(std::string& newPassword);
	void setnewName(std::string& newName);
	


	std::string const& getLogin();
	std::string const& getPassword();
	std::string const& getName();
	std::string const& getnewPassword();
	std::string const& getnewName();
	};