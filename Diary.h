#ifndef __DIARY_H__
#define __DIARY_H__

#include <string>
#include <vector>
using namespace std;
#include "Entry.h"
#include "User.h"

class Diary {
  private:
    string title;
    vector<User> user_List;
    const User* current_user;
    vector<Entry *> entry_List;
    void display() const;
    void addTopic();
    void addGenre();

  public:
    Diary();
    Diary(const string&);
    ~Diary();
    bool loadUsers(const string&);
    bool loadEntries(const string&);
    bool saveEntries(const string&);
    void login();
    void run();
    
};

#endif