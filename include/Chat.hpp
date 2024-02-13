#pragma once

#include "Message.hpp"
#include <iostream>
#include <vector>
#include <memory>

class OoR : public std::exception {
	const int _index_get, _index_max;
public:
	OoR(const int& index_get, const int& index_max) : _index_get(index_get), _index_max(index_max) {};
	virtual void Show();
};

class Chat
{
	std::vector <std::shared_ptr<User>> _users;
	std::vector <std::unique_ptr<Message>> _messages;

	std::shared_ptr<User> _currentUser = nullptr;

	void menuStart();
	void menuMain();

	const std::shared_ptr<User> getUserByLogin(const std::string& login) const;
	const std::shared_ptr<User> getUserByIndex(const int index) const noexcept(false);
	void changeUserName();
	void changeUserPassword();
	void showUserByIndex();

	void addUser(const std::string& login, const std::string& password, const std::string& name);
	void addMessage(std::shared_ptr<User> to, std::shared_ptr<User> from, std::string& text);

	void signUp();
	void signIn();
	
	void showMessages();
	void printMessage(const std::unique_ptr<Message>& Message) const;

	void sendPrivateMessage();
	void sendPublicMessage();

	void printStartMenu();
	void printUserMenu();
	int inputMenu(int countMenuItem);

	bool isValidLogin(const std::string& login) const;
	bool isValidPassword(const std::string& password) const;
	bool isValidName(const std::string& name) const;

	bool repeat();

public:
	void run();
};