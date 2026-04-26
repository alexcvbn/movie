#include "User.h"
#include <iostream>

User::User() : id(""), name(""), email("") {}

User::User(std::string id, const std::string& name, const std::string& email)
    : id(id), name(name), email(email) {}
    

std::string User::getId()    const {return id;}
std::string User::getName() const {return name;}
std::string User::getEmail() const {return email;}


void User::display() const {
    std::cout << "ID: " << getId() << "\n";
    std::cout << "이름: " << getName() << "\n";
    std::cout << "이메일: " <<getEmail() << "\n";

}

bool User::operator==(const User& other) const {
    return id == other.id;
}

std::ostream& operator<<(std::ostream& os, const User& u) {
    os << "ID: " << u.id << "  이름: " << u.name << "  이메일: " << u.email;
    return os;
}