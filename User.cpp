#include "User.h"
#include <iostream>

User::User() : id(""), name(""), email("") {}

User::User(std::string id, const std::string& name, const std::string& email)
    : id(id), name(name), email(email) {}
    

std::string User::getId()    const {return id;}
std::string User::getName() const {return name;}
std::string User::getEmail() const {return email;}


void User::display() const {
    std::cout << "ID: " << getId();
    std::cout << "이름: " << getName();
    std::cout << "이메일: " <<getEmail();

}


