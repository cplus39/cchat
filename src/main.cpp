#include "Chat.hpp"
#include <iostream>

int main()
{
	setlocale(LC_ALL, "Russian");

	std::cout << "тест";

	Chat chat;
	chat.run();
	return 0;
}