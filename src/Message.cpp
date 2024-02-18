#include "Message.hpp"
#include "User.hpp"



const std::string Message::Data_time()
{    
    char buffer[80];
    std::time_t timestamp = time(NULL);
    std::strftime(buffer, 80, "%H:%M:%S", localtime(&timestamp));
    std::string result = buffer;
    return result;    
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
