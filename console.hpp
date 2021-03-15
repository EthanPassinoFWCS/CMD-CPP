#include <string>
#include "user.hpp"
#include "command.hpp"
using namespace std;
class Console {
    User user;
    
public:
    Console(User new_user);
    User getUser();
    Command getLastCommand();
};