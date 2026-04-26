#include "UserManger.h"
#include <iostream>
#include <ostream>

void UserManager::addUser(const User& user){
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
