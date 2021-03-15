#include <string>
class User {
    std::string name;
    std::string password;
    bool admin;
    bool nothing = false;
public:
    User(std::string new_name, std::string new_password, bool admin);
    std::string getUser();
    std::string getPassword();
    bool isAdmin();
    void notUser();
    bool isNotUser();
};