#include <iostream>
#include "user.hpp"
#include "console.hpp"
#include <filesystem>
#include <Windows.h>
#include <vector>
#include <tchar.h>
#include <fstream>
using namespace std;
vector<string> get_all_files_names_within_folder(string folder)
{
    vector<string> names;
    string search_path = folder + "/*.*";
    WIN32_FIND_DATA fd; 
    HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd); 
    if(hFind != INVALID_HANDLE_VALUE) { 
        do { 
            // read all (real) files in current folder
            // , delete '!' read other 2 default folder . and ..
            if(! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {
                
                names.push_back(fd.cFileName);
            }
        }while(::FindNextFile(hFind, &fd)); 
        ::FindClose(hFind); 
    } 
    return names;
}

vector<User> getUsers(vector<string> files) {
    vector<User> users;
    for(int i = 0; i < files.size(); i++) {
        ifstream myfile;
        myfile.open("users/" + files[i]);
        string us;
        string ps;
        bool isad;
        myfile >> us;
        myfile >> ps;
        myfile >> isad;
        myfile.close();
        User u(us, ps, isad);
        users.push_back(u);
    }
    return users;
}

string boolToString(bool bo) {
    if(bo) { return "true"; }
    return "false";

}

User getUser(vector<User> users, string user) {
    for(int i = 0; i < users.size(); i++) {
        if(users[i].getUser() == user) {
            return users[i];
        }
    }
    User u("", "", false);
    u.notUser();
    return u;
}

void createUser(string uname, string ps, bool admin) {
    ofstream outfile;
    outfile.open("users/" + uname + ".txt");
    
    outfile << uname + "\n" + ps + "\n" + boolToString(admin) << endl;
}

bool startRegister(vector<User> users) {
    while (true) {
        string us;
        cout << "New Username: ";
        cin >> us;
        if(us == "register") {
            cout << "This username is not available for use, sorry.\n";
            continue;
        }
        if(!(getUser(users, us).isNotUser())) {
            cout << "This username is already taken, please try a different user.\n";
            continue;
        }
        string ps;
        cout << "Password: ";
        cin >> ps;
        string cps;
        cout << "Confirm Password: ";
        cin >> cps;
        if(cps == ps) {
            createUser(us, ps, false);
            cout << "Created the user! Now you must login.\n";
            return true;
        }
        else {
            cout << "Password and Confirm Password do not match. Please try again.\n";
            continue;
        }
    }    
}

bool startLogin(vector<User> users) {
    while (true) {
        string us;
        cout << "If you want to register instead type 'register' for the username.\n";
        cout << "Username: ";
        cin >> us;
        if(us == "register") {
            startRegister(users);
            vector<string> user_strings = get_all_files_names_within_folder("users");
            users = getUsers(user_strings);
            continue;
        }
        User u = getUser(users, us);
        string ps;
        cout << "\nPassword: ";
        cin >> ps;
        if(u.isNotUser()) {
            cout << "Invalid credentials. Try again.\n";
            continue;
        }
        if(u.getPassword() == ps) {
            cout << "Logged in!\n";

        }
        else {
            cout << "Invalid credentials. Try again.\n";
            continue;
        }
    }
}

int main() {
    string path = "users/";
    vector<string> user_strings = get_all_files_names_within_folder("users");
    vector<User> users = getUsers(user_strings);
    if(user_strings.size() == 0) {
        startRegister(users);
        user_strings = get_all_files_names_within_folder("users");
        users = getUsers(user_strings);
        startLogin(users);
    }
    else {
        startLogin(users);
    }
}

