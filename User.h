#pragma once
#include <ostream>
#include <string>

class User {
    private:
        std::string id;
        std::string name;
        std::string email;
        

    public:
        User();
        User(std::string id, const std::string& name, const std::string& email);

        std::string getId() const;
        std::string getName() const;
        std::string getEmail() const;

        void display() const;

        friend std::ostream& operator<<(std::ostream& os, const User& u);
};


