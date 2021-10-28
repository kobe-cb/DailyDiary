#include "kbDependencies.h"

#include "Diary.h"
#include "Entry.h"
#include "Genre.h"
#include "Topic.h"
#include "User.h"

Diary::Diary() {
  title = "Generic Title";
  current_user = nullptr;
}

Diary::Diary(const string& strTitle) {
  title = strTitle;
  current_user = nullptr;
}
Diary::~Diary() {
  for (unsigned i = 0; i < entry_List.size(); ++i) {
    delete entry_List.at(i);
  }
}

bool Diary::loadUsers(const string &strFile){
    ifstream inFS(strFile);
    if (! inFS.is_open()) {
        return false;
    }
    
    string strName;
    string strPass;
    User temp;
    while ( (inFS >> strName >> strPass) && (strName != "end") ) {
        temp = User(strName, strPass);
        user_List.push_back(temp);
    }
    
    inFS.close();
    return true;
}
bool Diary::loadEntries(const string &dataFile){
  ifstream iFS(dataFile);
  if (!iFS.is_open()) {
    cout << "Error opening " << dataFile << "." << endl;
    return false;
    //exit(EXIT_FAILURE);
  }
  int key = 6;
  char c;
  vector<char> keyHold;

  while (iFS >> noskipws >> c) {
    int temp = (c - key);
    keyHold.push_back(char(temp));
  }
  iFS.close();
  ofstream otFS(dataFile);
  if (!otFS.is_open()) {
    cout << "Error opening " << dataFile << "." << endl;
    return false;
    //exit(EXIT_FAILURE);
  }
  for (unsigned i = 0; i < keyHold.size(); ++i) {
    otFS << keyHold.at(i);
  }
  otFS.close();

  //-----------------------------------------------
    ifstream inFS(dataFile);
    if (!inFS.is_open()) {
        return false;
    }

    string strMsgNum = "";
    getline(inFS, strMsgNum);
    int numMsg = stoi(strMsgNum);
    vector<vector<int>> children(numMsg);

    for (int i = 0; i < numMsg; ++i) {
        string temp;
        string strEnd;
        string strType, strID, strSub, strBody, strAuthor, strChild;
        unsigned numID;
        int childIndex;
        //Type
        getline(inFS, strType);
        //ID
        inFS >> temp >> strID >> temp;
        numID = stoi(strID);
        getline(inFS, temp, ' ');
        //Subject
        getline(inFS, strSub);
        //Author
        inFS >> temp >> strAuthor;
        //Check Children
        inFS >> temp; //checks body or children
        if (temp.at(1) == 'c') {
            getline(inFS, strChild); //grabs n number of children id's
            istringstream inSS(strChild); //put each number to vector
            while (inSS >> childIndex){
                children.at(i).push_back(childIndex);
            }
            inFS >> temp;
        }

        //Body
        getline(inFS, temp, ' ');        
        getline(inFS, temp);
        while (temp != "<end>") {
            strBody += temp + '\n';
            getline(inFS, temp);
        }

        if (strType.at(7) == 'g') {
            entry_List.push_back(new Genre(strAuthor, strSub, strBody, numID));
        }

        else if (strType.at(7) == 't') {
            entry_List.push_back(new Topic(strAuthor, strSub, strBody, numID));
        }

    }

    //add children
    for (unsigned i = 0; i < children.size(); ++i) {
        for (unsigned j = 0; j < children.at(i).size(); ++j) {
             entry_List.at(i)->addChild( entry_List.at(children.at(i).at(j)-1));
        }
    }
    inFS.close();
    return true;
}
bool Diary::saveEntries(const string &dataFile){
    ofstream outFS(dataFile);
    if(!outFS.is_open()){
        return false;
    }

    outFS <<  entry_List.size() << endl;
    for (unsigned i = 0; i <  entry_List.size(); ++i) {
        outFS <<  entry_List.at(i)->toFormattedString();
    }

    outFS.close();
//-----------------------------------------------------
    ifstream iFS(dataFile);
    if (!iFS.is_open()) {
      cout << "Error opening " << dataFile << "." << endl;
      return false;
    //exit(EXIT_FAILURE);
   }

    int key = 6;
    char c;
    vector<char> keyHold;

    while (iFS >> noskipws >> c) {
      int temp = (c + key);
      keyHold.push_back(char(temp));
    }
    iFS.close();

    ofstream otFS(dataFile);
    if (!otFS.is_open()) {
      cout << "Error opening " << dataFile << "." << endl;
      return false;
      //exit(EXIT_FAILURE);
    }
    for (unsigned i = 0; i < keyHold.size(); ++i) {
      otFS << keyHold.at(i);
    }
    otFS.close();

    return true;
}

void Diary::login() {
    string strUser;
    string strPass;
    bool tUser = false;
    
    cout << "Welcome to " << title << endl;
    
    do {
        cout << "Enter your username (\'Q\' or \'q\' to quit): ";
        cin >> strUser;
        if ( (strUser == "q") || (strUser == "Q") ) {
            break;
        }
        cout << "Enter your password: ";
        cin >> strPass;

        for (unsigned i = 0; i < user_List.size(); ++i) {
            if (user_List.at(i).check(strUser, strPass)) {
                current_user = &user_List.at(i);
                tUser = true;
            }
        }

        if (tUser) {
            cout << endl << "Welcome back " << current_user->getUsername() << '!' << endl;
            cout << endl;
            return;
        }
        else {
            cout << "Invalid Username or Password!" << endl;
            cout << endl;
        }
    }
    while( (strUser != "q") && (strUser != "Q") );
    cout << "Bye!" << endl;
} 
void Diary::run(){
    string userAction;

    if (!current_user) {
        return;
    }

    do {
        cout << "Menu" << endl;
        cout << "- Display Entries ('D' or 'd')" << endl;
        cout << "- Add New Topic ('A' or 'a')" << endl;
        cout << "- Add Genre to an Entry ('G' or 'g')" << endl;
        cout << "- Quit ('Q' or 'q')" << endl;
        cout << "Choose an action: "; 
        cin  >> userAction;

        if ( (userAction == "d") || (userAction == "D") ){
            display();
        }
        else if ( (userAction == "a") || (userAction == "A") ){
            addTopic();
        }
        else if ( (userAction == "g") || (userAction == "G") ){
            addGenre();
        }
        else if ( (userAction == "q") || (userAction == "Q") ) {
            cout << "Bye!" << endl;
        }
    }
    while ( (userAction != "q") && (userAction != "Q") );
    return;
}

void Diary::display() const {
    if (!entry_List.size()) {
        cout << endl;
        cout << "Nothing to Display." << endl << endl;
        return;
    }
    cout << endl;
    for (unsigned i = 0; i < entry_List.size(); ++i) {
        if ( !entry_List.at(i)->isGenre()) {
            if (i == 0) {
                cout << "---------------------------------------------------------" << endl;
            }
        
        entry_List.at(i)->print(0);
        cout << "---------------------------------------------------------" << endl;
        }
    }
    cout << endl;
}

void Diary::addTopic() {
    string subject;
    string body, temp;
    string author(current_user->getUsername());
    cin.ignore();
    cout << "Enter Subject: ";
    getline(cin, subject);

    cout << "Enter Body: ";
    getline(cin, temp);

    while (temp != "") {
        body += temp + '\n';

        getline(cin, temp);
    }
    cout << endl;

    unsigned msgID = entry_List.size() + 1;
    entry_List.push_back(new Topic(author, subject, body, msgID));
    
}

void Diary::addGenre() {
    string subject;
    string body, temp;
    string author(current_user->getUsername());

    int partID;

    cout << "Enter Message ID (-1 for Menu): ";
    cin >> partID;

    if (partID == -1) {
        return;
    }

    while( static_cast<unsigned>(partID - 1) >= entry_List.size()) {
        cout << "Invalid Message ID!!" << endl;

        cout << endl;
        cout << "Enter Message ID (-1 for Menu): ";
        cin >> partID;
    }
    cin.ignore();
    cout << endl;

    subject = entry_List.at(partID-1)->getSubject();

    string userGenre("");
    cout << "Enter Genre: ";
    getline(cin, userGenre);

    cout << "Enter Body: ";
    getline(cin, temp);
    while (temp != "") {
        body+= temp + '\n';
        getline(cin, temp);
    }
    cout << endl;

    unsigned numID = entry_List.size() + 1;

    entry_List.push_back(new Genre(author, userGenre + ": " + subject, body ,numID));
    entry_List.at(partID-1)->addChild(entry_List.at(numID-1));

}
