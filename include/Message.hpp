#pragma once

#include "User.hpp"
#include <iostream>
#include <ctime>   
#include <sstream>
#include <string>
#include <iomanip>
#include <memory>

class Message
{
	const std::shared_ptr<User> _to;
	const std::shared_ptr<User> _from;
	const std::string _text;
	const std::string _time;


public:
	Message(std::shared_ptr<User> to, std::shared_ptr<User> from, const std::string& text):
	_to(to), _from(from), _text(text), _time(Data_time())
	{};

	const std::shared_ptr<User> getTo() const;
	const std::shared_ptr<User> getFrom() const;
	const std::string& getText() const;
	const std::string& getTime() const;
	const std::string Data_time();
	
};