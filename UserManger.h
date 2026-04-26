#pragma once
#include <vector>
#include <string>
#include "User.h"

class UserManager {
    private:
        std::vector<User> users;

    public:
        void addUser(const User& user);
        void printAll() const;
        User* findId(const std::string& id);

};