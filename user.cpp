#include "user.hpp"
#include <iostream>

std::string User::getUser() {
    return name;
}

std::string User::getPassword() {
    return password;
}

bool User::isAdmin() {
    return admin;
}

void User::notUser() {
    nothing = true;
}

bool User::isNotUser() {
    return nothing;
}

User::User(std::string new_user, std::string new_password, bool new_admin)
: name(new_user), password(new_password), admin(new_admin) {}
