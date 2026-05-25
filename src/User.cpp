#include "User.h"
#include <iostream>
#include <stdexcept>

User::User() : id(""), name(""), email("") {}

User::User(std::string id, const std::string& name, const std::string& email)
    : id(id), name(name), email(email)
{
    if (id.empty())
        throw std::invalid_argument("사용자 ID가 비어 있습니다.");
}
    

std::string User::getId()    const {return id;}
std::string User::getName() const {return name;}
std::string User::getEmail() const {return email;}



bool User::operator==(const User& other) const {
    return id == other.id;
}

std::ostream& operator<<(std::ostream& os, const User& u) {
    os << "ID: " << u.id << "  이름: " << u.name << "  이메일: " << u.email;
    return os;
}