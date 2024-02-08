#include "Message.hpp"
#include "User.hpp"

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