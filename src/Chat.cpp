#include "Chat.hpp"


void OoR::Show() {
	std::cout << "Ошибка OutOfRange\n" \
		<< "Минимальный: 0 - Полученный: " \
		<< this->_index_get << " - " \
		<< "Максимальный: " << this->_index_max - 1 << "\n";
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
		int input = inputMenu(6);
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
		case 5:
			changeUserName();
			break;
		case 6:
			changeUserPassword();
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

void Chat::addUser(const std::string& login, const std::string& password, const std::string& name)
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
	std::cout << "\n";
	std::cout << "*** *** ***\n";
	std::cout << "Введите логин:\n" << ">>";


	std::getline(std::cin >> std::ws, login);


	if (isValidLogin(login) && (getUserByLogin(login) == nullptr))

		std::cout << "Логин прошёл верификацию\n";
	else
	{
		std::cout << "\n" << "*** *** ***" << "\n" << "Логин не прошёл верификацию\n" << "\n";
		return;
	}

	std::cout << "\n";
	std::cout << "*** *** ***\n";
	std::cout << "Введите Пароль:\n" << ">>";
	std::getline(std::cin >> std::ws, password);

	if (isValidPassword(password))
		std::cout << "\n" << "*** *** ***" << "\n" << "Пароль прошёл верификацию\n" << "\n";
	else
	{
		std::cout << "\n" << "*** *** ***" << "\n" << "Пароль не прошёл верификацию\n" << "\n";
		return;
	}

	std::cout << "\n";
	std::cout << "*** *** ***\n";
	std::cout << "Введите Пароль:\n" << ">>";
	std::cout << "Введите имя:\n" << ">>";
	std::getline(std::cin >> std::ws, name);

	if (isValidName(name))
		std::cout << "\n" << "*** *** ***" << "\n" << "Имя прошло верификацию\n" << "\n";
	else
	{
		std::cout << "\n" << "*** *** ***" << "\n" << "Имя не прошло верификацию\n" << "\n";
		return;
	}

	addUser(login, password, name);
	this->_currentUser = getUserByLogin(login);
	menuMain();
}


void Chat::signIn()
{
	std::string login, password;
	std::cout << "\n";
	std::cout << "*** *** ***\n";
	std::cout << "Введите логин:\n" << ">>";
	std::getline(std::cin >> std::ws, login);

	std::cout << "\n";
	std::cout << "*** *** ***\n";

	if (!isValidLogin(login) || getUserByLogin(login) == nullptr) return;

	std::cout << "\n";
	std::cout << "*** *** ***\n";
	std::cout << "Введите Пароль:\n" << ">>";
	std::getline(std::cin >> std::ws, password);


	if (!isValidPassword(password) || !(getUserByLogin(login)->getPassword() == password)) return;


	this->_currentUser = getUserByLogin(login);
	menuMain();

}


bool Chat::isValidLogin(const std::string& login) const

{
	if (login.length() >= 3)
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
	std::cout << "\nКогда: " << message->getTime() << "\n";
	std::cout << "\nОт кого: " << message->getFrom()->getName() << "\n";
	std::cout << "\nТекст сообщения: " << message->getText() << '\n';
}

void Chat::sendPrivateMessage()
{
	std::string login, text;

	std::cout << "\n";
	std::cout << "*** *** ***\n";
	std::cout << "Введите логин получателя: ";
	std::cin >> login;
	if (!isValidLogin(login) || getUserByLogin(login) == nullptr) return;
	std::cout << "\n" << "Введите сообщение:\n";

	;
	std::getline(std::cin >> std::ws, text);
	text += ('\n');

	addMessage(getUserByLogin(login), this->_currentUser, text);
}

void Chat::sendPublicMessage()
{
	std::string text;
	std::cout << "\n";
	std::cout << "*** *** ***\n";
	std::cout << "\n" << "Введите сообщение:\n";
	std::getline(std::cin >> std::ws, text);
	text += ('\n');
	addMessage(nullptr, this->_currentUser, text);
}

void Chat::printStartMenu()
{
	std::cout << "Выбор пункта:\n"\
		"\n"\
		"*** *** ***\n"\
		"1: Войти\n" \
		"2: Регистрация\n"\
		"0: Выход\n"\
		"*** *** ***\n";
}

void Chat::printUserMenu()
{
	std::cout << "Выбор пункта:\n"\
		"\n"\
		"*** *** ***\n"\
		"1: Показать сообщения\n" \
		"2: Отправить личное сообщение\n"\
		"3: Отправить публичное сообщение\n"\
		"4: Показать пользователя по индексу\n"\
		"5: Сменить Имя\n"\
		"6: Сменить Пароль\n"\
		"0: Выход\n"\
		"*** *** ***\n";
}

int Chat::inputMenu(int count)
{
	int inp;
	std::cin >> inp;
	if (!std::cin.good()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "\n";
		std::cout << "*** *** ***\n";
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

void Chat::changeUserPassword()
{
	std::string newPassword;
	std::cout << "\n";
	std::cout << "*** *** ***\n";
	std::cout << "Введите новый Пароль:\n" << ">>";
	std::getline(std::cin >> std::ws, newPassword);

	if (isValidPassword(newPassword))

		std::cout << "\n" << "*** *** ***" << "\n" << "Новый пароль прошёл верификацию\n" << "\n" << "*** *** ***" << "\n";

	else
	{
		std::cout << "\n" << "*** *** ***" << "\n" << "Новый пароль не прошёл верификацию\n" << "\n" << "*** *** ***" << "\n";
		return;
	}

	this->_currentUser->setNewPassword(newPassword);
}

void Chat::changeUserName()
{
	std::string newName;
	std::cout << "\n";
	std::cout << "*** *** ***\n";
	std::cout << "Введите новое имя:\n" << ">>";
	std::getline(std::cin >> std::ws, newName);

	if (isValidName(newName))
		std::cout << "\n" << "*** *** ***" << "\n" << "Новое имя прошло верификацию\n" << "\n" << "*** *** ***" << "\n";
	else
	{
		std::cout << "\n" << "*** *** ***" << "\n" "Новое имя не прошло верификацию\n" << "\n" << "*** *** ***" << "\n";
		return;
	}

	this->_currentUser->setNewName(newName);
}

void Chat::showUserByIndex()
{

	int index;
	std::cout << "\n";
	std::cout << "*** *** ***\n";
	std::cout << "Введите индекс (число): ";
	std::cin >> index;
	if (!std::cin.good()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "\n";
		std::cout << "*** *** ***\n";
		std::cout << "Ошибка! Вводите только целочисленные.\n";

		return;
	}
	try {
		std::cout << "\nЛогин: " << getUserByIndex(index)->getLogin() + "\n" << \
			"\nИмя: " << getUserByIndex(index)->getName() << "\n\n";
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
