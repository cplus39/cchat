#include "Chat.hpp"

void OoR::Show() {
	std::cout << "Ошибка OutOfRange\n" \
		<< "Минимальный: 0 - Полученный: " \
		<< this->_index_get << " - " \
		<< "Максимальный: " << this->_index_max << "\n";
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
}

void Chat::signIn()
{
}

bool Chat::isValidLogin(const std::string& login) const
{
	return nullptr; // на реализации fentaliche
}

bool Chat::isValidPassword(const std::string& password) const
{
	return nullptr; // на реализации fentaliche
}

bool Chat::isValidName(const std::string& name) const
{
	return nullptr; // на реализации fentaliche
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
	std::cout << "От кого: " << message->getFrom() << "\n";
	std::cout << "Текст сообщения:\n" \
		<< message->getText() << '\n';
}

void Chat::sendPrivateMessage()
{
	std::string login, text;

	std::cout << "Введите логин получателя: ";
	std::cin >> login;
	if (!isValidLogin(login) && getUserByLogin(login) != nullptr) return;
	std::cout << "\n" << "Введите сообщение:\n";
	std::cin >> text;

	addMessage(getUserByLogin(login),this->_currentUser, text);
}

void Chat::sendPublicMessage()
{
	std::string text;
	std::cout << "\n" << "Введите сообщение:\n";
	std::cin >> text;

	addMessage(nullptr, this->_currentUser, text);
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
	std::cout << "Выбор пункта:\n" \
		"1: Показать сообщения\n" \
		"2: Отправить личное сообщение\n"\
		"3: Отправить публичное сообщение\n"\
		"4: Показать пользователя по индексу\n"\
		"0: Выход\n";
}

int Chat::inputMenu(int count)
{
	int inp;
	std::cin >> inp;
	if (!std::cin.good()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cout << "Ошибка! Вводите только целочисленные.\n";
		
		return -1;
	}
	if (inp >= 0 && inp <= count) return inp;
	else if (inp < 0) {
		std::cout << "Значение меньше нуля - не допускаются.\n";
	}
	else {
		std::cout << "Значения больше " << count << " не допускаються.\n";
	}
	return -1;
}

void Chat::showUserByIndex()
{

	int index;
	std::cout << "Введите индекс (число): ";
	std::cin >> index;
	try {
		std::cout << "\n" << getUserByIndex(index);
	}
	catch (OoR& e){
		e.Show();
	}
	catch (...) {
		std::cout << "Произошла неизвестная ошибка!\n";
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
