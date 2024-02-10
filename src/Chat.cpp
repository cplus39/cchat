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
	for (std::shared_ptr<User> i : this->_users) {
		if (i->getLogin() == login) return i;
	}
	return nullptr;
}

void Chat::addUser(std::string& login, std::string& password, std::string& name)
{
	if (isValidLogin(login) && isValidPassword(password) && isValidName(name)) {
		this->_users.emplace_back(std::make_shared<User>(User(login, password, name)));
	}
	else {
		repeat();
	}
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
	std::cout << "Выбор пункта:\n" \
		"1: Войти\n" \
		"2: Регистрация\n"\
		"0: Выход\n";
}

void Chat::printUserMenu()
{
}

int Chat::inputMenu(int count)
{
	int inp;
	std::cin >> inp;
	if (inp > 0 && inp <= count) return inp;
	return 0;
}

bool Chat::isValidLogin(const std::string& login ) const
{
	return nullptr;
}

bool Chat::isValidPassword(const std::string& password) const
{
	return nullptr;
}

bool Chat::isValidName(const std::string& name) const
{
	return nullptr;
}

void Chat::showUserByIndex()
{
}

const std::shared_ptr<User> Chat::getUserByIndex(int index) const
{
	return nullptr;
}

bool Chat::repeat()
{
	return nullptr;
}
