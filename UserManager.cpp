#include "UserManager.h"
#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <string>

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

void UserManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << filename << " 파일 없음, 빈 상태로 시작\n";
        return;
    }
    std::string line;
    getline(file, line); // 헤더 스킵
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        getline(ss, token, ','); std::string id = token;
        getline(ss, token, ','); std::string name = token;
        getline(ss, token, ','); std::string email = token;
        users.push_back(User(id, name, email));
    }
    file.close();
}

void UserManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << filename << " 저장 실패\n";
        return;
    }
    file << "id,name,email\n";
    for (const auto& u : users) {
        file << u.getId() << ","
             << u.getName() << ","
             << u.getEmail() << "\n";
    }
    file.close();
}

int UserManager::size() const {
    return users.size();
}