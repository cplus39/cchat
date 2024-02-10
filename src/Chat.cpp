#include "Chat.hpp"

void OoR::Show() {
	std::cout << "Îøèáêà OutOfRange\n" \
		<< "Ìèíèìàëüíûé: 0 - Ïîëó÷åííûé: " \
		<< this->_index_get << " - " \
		<< "Ìàêñèìàëüíûé: " << this->_index_max << "\n";
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
			std::cin.get();
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
	std::cout << "Ââåäèòå ëîãèí, ñîñòîÿùèé èç íå ìåíåå âîñüìè ëàòèíñêèõ áóêâ è öèôð è áåç ïðîáåëîâ:\n" << ">>";
	getline(std::cin, login);

	if (isValidLogin(login)) 
		std::cout << "Âaø ëîãèí ïðîøåë âàëèäàöèþ\n";
	else 
		std::cout << "Âaø ëîãèí íå ïðîøåë âàëèäàöèþ\n";
}

void Chat::signIn()
{
}

bool Chat::isValidLogin(const std::string& login) const

{	
	if (login.length() == 8)
	{
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
=======
}

bool Chat::isValidPassword(const std::string& password) const
{

	if (password.length() == 8)
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
	return nullptr; // íà ðåàëèçàöèè fentaliche
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
	std::cout << "Îò êîãî: " << message->getFrom() << "\n";
	std::cout << "Òåêñò ñîîáùåíèÿ:\n" \
		<< message->getText() << '\n';
}

void Chat::sendPrivateMessage()
{
	std::string login, text;

	std::cout << "Ââåäèòå ëîãèí ïîëó÷àòåëÿ: ";
	std::cin >> login;
	if (!isValidLogin(login) && getUserByLogin(login) != nullptr) return;
	std::cout << "\n" << "Ââåäèòå ñîîáùåíèå:\n";
	std::cin >> text;

	addMessage(getUserByLogin(login),this->_currentUser, text);
}

void Chat::sendPublicMessage()
{
	std::string text;
	std::cout << "\n" << "Ââåäèòå ñîîáùåíèå:\n";
	std::cin >> text;

	addMessage(nullptr, this->_currentUser, text);
}

void Chat::printStartMenu()
{
	std::cout << "Âûáîð ïóíêòà:\n" \
		"1: Âîéòè\n" \
		"2: Ðåãèñòðàöèÿ\n"\
		"0: Âûõîä\n";
}

void Chat::printUserMenu()
{
	std::cout << "Âûáîð ïóíêòà:\n" \
		"1: Ïîêàçàòü ñîîáùåíèÿ\n" \
		"2: Îòïðàâèòü ëè÷íîå ñîîáùåíèå\n"\
		"3: Îòïðàâèòü ïóáëè÷íîå ñîîáùåíèå\n"\
		"4: Ïîêàçàòü ïîëüçîâàòåëÿ ïî èíäåêñó\n"\
		"0: Âûõîä\n";
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
	std::cout << "Ââåäèòå èíäåêñ (÷èñëî): ";
	std::cin >> index;
	try {
		std::cout << "\n" << getUserByIndex(index);
	}
	catch (OoR& e){
		e.Show();
	}
	catch (...) {
		std::cout << "Ïðîèçîøëà íåèçâåñòíàÿ îøèáêà!\n";
	}
}

const std::shared_ptr<User> Chat::getUserByIndex(int index) const
{
	if (index < 0 || index >= this->_users.size()) throw OoR(index, this->_users.size());
	return this->_users.at(index);
}

bool Chat::repeat()
{
	return nullptr;
}
