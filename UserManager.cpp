#include "UserManger.h"
#include <iostream>
#include <ostream>

void UserManager::addUser(const User& user){
    for (const auto& u : users) {
        if (u == user) {
            std::cout << "이미 등록된 사용자입니다.\n";
            return;
        }
    }
    users.push_back(user);
}

void UserManager::printAll() const {
    if(users.empty()) {
        std::cout <<"사용자가 없습니다.\n";
        return;
    }
    for(const auto& u : users){
        std::cout << u << "\n";
    }
}

User* UserManager::findId(const std::string& id){
    for(auto& u : users) {
        if(u.getId() == id)
            return &u;
    }

    return nullptr;
}
