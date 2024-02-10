#include "Chat.hpp"

void OoR::Show() {
	std::cout << "������ OutOfRange\n" \
		<< "�����������: 0 - ����������: " \
		<< this->_index_get << " - " \
		<< "������������: " << this->_index_max << "\n";
}

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

const std::shared_ptr<User> Chat::getUserByLogin(const std::string& login) const
{
	for (const std::shared_ptr<User>& i : this->_users) {
		if (i->getLogin() == login) return i;
	}
	return nullptr;
}

void Chat::addUser(std::string& login, std::string& password, std::string& name)
{
	if (isValidLogin(login) && isValidPassword(password) && isValidName(name)) {
		this->_users.emplace_back(std::make_shared<User>(login, password, name));
	}
	else {
		repeat();
	}
}

void Chat::addMessage(std::shared_ptr<User> to, std::shared_ptr<User> from, std::string &text)
{
	this->_messages.emplace_back(std::make_unique<Message>(to, from, text));
}

void Chat::signUp()
{
	std::string login, password, name;
	std::cout << "������� �����:\n" << ">>";
	std::cin.get();
	std::getline(std::cin, login);

	if (isValidLogin(login))
		std::cout << "����� ������ �����������\n";
	else
	{
		std::cout << "����� �� ������ �����������\n";
		return;
	}

	std::cout << "������� ������:\n" << ">>";
	std::getline(std::cin, password);

	if (isValidPassword(password))
		std::cout << "������ ������ �����������\n";
	else
	{
		std::cout << "������ �� ������ �����������\n";
		return;
	}

	std::cout << "������� ���:\n" << ">>";
	std::getline(std::cin, name);

	if (isValidName(name))
		std::cout << "��� ������ �����������\n";
	else
	{
		std::cout << "��� �� ������ �����������\n";
		return;
	}

	addUser(login, password, name);
	this->_currentUser = getUserByLogin(login);
	menuMain();
}

void Chat::signIn()
{
}

bool Chat::isValidLogin(const std::string& login) const

{
	std::cout << login << "\n";
	if (login.length() >= 3)
	{
		if (!(getUserByLogin(login) == nullptr)) { return false;}

		for (int i{}; i < login.length(); ++i)
		{
			if (login[i] < '0' ||
				login[i] > '9' && login[i] < 'A' ||
				login[i] > 'Z' && login[i] < 'a' ||
				login[i] > 'z')
				return false;
		}
		return true;
	}
	else return false;
}

bool Chat::isValidPassword(const std::string& password) const
{

	if (password.length() >= 3)
	{
		for (int i{}; i < password.length(); ++i)
		{
			if (password[i] < '0' ||
				password[i] > '9' && password[i] < 'A' ||
				password[i] > 'Z' && password[i] < 'a' ||
				password[i] > 'z')
				return false;
		}
		return true;
	}
	else return false;

}

bool Chat::isValidName(const std::string& name) const
{
	if (name.length() >= 3)
	{
		for (int i{}; i < name.length(); ++i)
		{
			if (name[i] < '0' ||
				name[i] > '9' && name[i] < 'A' ||
				name[i] > 'Z' && name[i] < 'a' ||
				name[i] > 'z')
				return false;
		}
		return true;
	}
	else return false;
}


void Chat::showMessages()
{
	for (const std::unique_ptr<Message>& i : this->_messages) {
		if (i->getTo() == this->_currentUser || i->getTo() == nullptr) {
			printMessage(i);
		}
		else {
			continue;
		}
	}
}

void Chat::printMessage(const std::unique_ptr<Message>& message) const
{
	std::cout << "�� ����: " << message->getFrom()->getName() << "\n";
	std::cout << "����� ���������:\n" \
		<< message->getText() << '\n';
}

void Chat::sendPrivateMessage()
{
	std::string login, text;

	std::cout << "������� ����� ����������: ";
	std::cin >> login;
	if (!isValidLogin(login) && getUserByLogin(login) != nullptr) return;
	std::cout << "\n" << "������� ���������:\n";

	std::cin.get();
	std::getline(std::cin, text);
	text += ('\n');
	addMessage(getUserByLogin(login), this->_currentUser, text);
}

void Chat::sendPublicMessage()
{
	std::string text;
	std::cout << "\n" << "������� ���������:\n";
	std::cin.get();
	std::getline(std::cin, text);
	text+=('\n');
	addMessage(nullptr, this->_currentUser, text);
}

void Chat::printStartMenu()
{
	std::cout << "����� ������:\n" \
		"1: �����\n" \
		"2: �����������\n"\
		"0: �����\n";
}

void Chat::printUserMenu()
{
	std::cout << "����� ������:\n" \
		"1: �������� ���������\n" \
		"2: ��������� ������ ���������\n"\
		"3: ��������� ��������� ���������\n"\
		"4: �������� ������������ �� �������\n"\
		"0: �����\n";
}

int Chat::inputMenu(int count)
{
	int inp;
	std::cin >> inp;
	if (!std::cin.good()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cout << "������! ������� ������ �������������.\n";
		
		return -1;
	}
	if (inp >= 0 && inp <= count) return inp;
	else if (inp < 0) {
		std::cout << "�������� ������ ���� - �� �����������.\n";
	}
	else {
		std::cout << "�������� ������ " << count << " �� ������������.\n";
	}
	return -1;
}

void Chat::showUserByIndex()
{

	int index;
	std::cout << "������� ������ (�����): ";
	std::cin >> index;
	try {
		std::cout << "\n" << getUserByIndex(index);
	}
	catch (OoR& e){
		e.Show();
	}
	catch (...) {
		std::cout << "��������� ����������� ������!\n";
	}
}

const std::shared_ptr<User> Chat::getUserByIndex(const int index) const
{
	if (index < 0 || index >= this->_users.size()) throw OoR(index, this->_users.size());
	return this->_users.at(index);
}

bool Chat::repeat()
{
	return nullptr;
}
