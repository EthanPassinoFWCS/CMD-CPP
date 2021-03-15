#include <string>
#include "user.hpp"
using namespace std;
class Command {
    string name;
    string help;
    User runner;
public:
    string getName();
    string getHelp();
    User getRunner();
    void runCommand();
};