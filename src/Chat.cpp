#include "Chat.hpp"

void Chat::run()
{
	menuStart();
}

void Chat::menuStart()
{
	while (true)
	{
		printStartMenu();
		int input = inputMenu(2);
		switch (input)
		{
		case 1:
			signIn();
			break;
		case 2:
			signUp();
			break;
		case 0:
			return;
		default:
			continue;
		}
	}
}

void Chat::menuMain()
{
	while (true)
	{
		printUserMenu();
		int input = inputMenu(4);
		switch (input)
		{
		case 1:
			showMessages();
			break;
		case 2:
			sendPrivateMessage();
			break;
		case 3:
			sendPublicMessage();
			break;
		case 4:
			showUserByIndex();
			break;
		case 0:
			_currentUser = nullptr;
			return;
		default:
			break;
		}
	}
}

const std::shared_ptr<User> Chat::getUserByLogin(std::string &login) const
{
}

void Chat::addUser(std::string& login, std::string& password, std::string& name)
{
}

void Chat::addMessage(std::shared_ptr<User> to, std::shared_ptr<User> from, std::string &text)
{
}

void Chat::signUp()
{
}

void Chat::signIn()
{
}

void Chat::showMessages()
{
}

void Chat::printMessage(const std::unique_ptr<Message>& message) const
{
}

void Chat::sendPrivateMessage()
{
}

void Chat::sendPublicMessage()
{
}

void Chat::printStartMenu()
{
}

void Chat::printUserMenu()
{
}

int Chat::inputMenu(int count)
{
}

bool Chat::isValidLogin(const std::string& login ) const
{
}

bool Chat::isValidPassword(const std::string& password) const
{
}

void Chat::showUserByIndex()
{
}

const std::shared_ptr<User> Chat::getUserByIndex(int index) const
{
}

bool Chat::repeat()
{
}
