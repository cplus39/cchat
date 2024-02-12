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

void Chat::addMessage(std::shared_ptr<User> to, std::shared_ptr<User> from, std::string& text)
{
	this->_messages.emplace_back(std::make_unique<Message>(to, from, text));
}

void Chat::signUp()
{
	std::string login, password, name;
	std::cout << "Введите логин:\n" << ">>";

	std::getline(std::cin >> std::ws, login);

	if (isValidLogin(login))
		std::cout << "Логин прошёл верификацию\n";
	else

	{
		std::cout << "Логин не прошёл верификацию\n";
		return;
	}

	std::cout << "Введите Пароль:\n" << ">>";
	std::getline(std::cin >> std::ws, password);

	if (isValidPassword(password))
		std::cout << "Пароль прошёл верификацию\n";
	else
	{
		std::cout << "Пароль не прошёл верификацию\n";
		return;
	}

	std::cout << "Введите имя:\n" << ">>";
	std::getline(std::cin >> std::ws, name);

	if (isValidName(name))
		std::cout << "Имя прошло верификацию\n";
	else
	{
		std::cout << "Имя не прошло верификацию\n";
		return;
	}

	addUser(login, password, name);
	this->_currentUser = getUserByLogin(login);
	menuMain();
}

void Chat::signIn()
{
	std::string newPassword, newName;
	std::cout << "Введите новый Пароль:\n" << ">>";
	std::getline(std::cin >> std::ws, newPassword);

	if (isValidPassword(newPassword))
		std::cout << "Новый пароль прошёл верификацию\n";
	else
	{
		std::cout << "Пароль не прошёл верификацию\n";
		return;
	}
	changeUserPassword(newPassword);
	this->_currentUser = changeUserPassword(newPassword);
	menuMain();

	std::cout << "Введите новое имя:\n" << ">>";
	std::getline(std::cin >> std::ws, newName);

	if (isValidName(newName))
		std::cout << "Новое имя прошло верификацию\n";
	else
	{
		std::cout << "Имя не прошло верификацию\n";
		return;
	}

	changeUserName(newName);
	this->_currentUser = changeUserName(newName);
	menuMain();
}

bool Chat::isValidLogin(const std::string& login) const

{
	if (login.length() >= 3)
	{
		if (!(getUserByLogin(login) == nullptr)) { return false; }

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
	std::cout << "От кого: " << message->getFrom()->getName() << "\n";
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

	;
	std::getline(std::cin >> std::ws, text);
	text += ('\n');

	addMessage(getUserByLogin(login), this->_currentUser, text);
}

void Chat::sendPublicMessage()
{
	std::string text;
	std::cout << "\n" << "Введите сообщение:\n";
	;
	std::getline(std::cin >> std::ws, text);
	text += ('\n');
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

const std::shared_ptr<User> Chat::changeUserPassword(const std::string& newPassword)
{
	return std::shared_ptr<User>();
}

const std::shared_ptr<User> Chat::changeUserName(const std::string& newName)
{
	return std::shared_ptr<User>();
}

void Chat::showUserByIndex()
{

	int index;
	std::cout << "Введите индекс (число): ";
	std::cin >> index;
	try {
		std::cout << "\n" << getUserByIndex(index);
	}
	catch (OoR& e) {
		e.Show();
	}
	catch (...) {
		std::cout << "Произошла неизвестная ошибка!\n";
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
