#include "Chat.hpp"
#include <iostream>
#include <windows.h>

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	Chat chat;
	chat.run();
	return 0;
}