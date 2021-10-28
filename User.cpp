#include <iostream>
using namespace std;

#include "User.h"

User::User() {
    username = "";
    password = "";
}

User::User(const string& uname, const string& pass) {
    username = uname;
    password = pass;
}

string User::getUsername() const {
    return username;
    
}
string User::getPassword() const {
    return password;
}

bool User::check(const string &uname, const string &pass) const{
    if (uname == ""){
        return false;
    }
    else if ( (username == uname) && (password == pass) ) {
        return true;
    }
    
    return false;
}

bool User::setPassword(const string &oldpass, const string &newpass){
    if (username == ""){
        return false;
    }
    else if (oldpass == password) {
        password = newpass;
        return true;
      }
      
    return false;
  }
  