#include "Message.hpp"
#include "User.hpp"
#include <chrono>



const std::string Message::Data_time()
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%H:%M");
    return ss.str();
}


const std::shared_ptr<User> Message::getTo() const
{
    return _to;
}

const std::shared_ptr<User> Message::getFrom() const
{
    return _from;
}

const std::string & Message::getText() const
{
    return _text;
}

const std::string& Message::getTime() const
{
    return _time;
}
