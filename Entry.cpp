#include "Entry.h"
#include "kbDependencies.h"
using namespace std;

Entry::Entry() {
    author = "";
    subject = "";
    body = "";
    id = 0;
}

Entry::Entry(const string& strAuthor,
             const string& strSubject,
             const string& strBody,
             unsigned numID){
    author = strAuthor;
    subject = strSubject;
    body = strBody;
    id = numID;
}

Entry::~Entry() {


}

void Entry::print(unsigned numVal) const {
    string temp = body;
    string empty = "";
    //general message output
    for (unsigned i = 0; i < numVal; ++i) {
        empty += " ";
    }
    for (unsigned i = 0; i < temp.size() - 1; ++i) {
        if (temp.at(i) == '\n'){
            temp.insert(i + 1, empty);
            i += empty.size();
        }
    }
    
    cout << empty << "Entry #" << id << ": " << subject << '\n' << empty << "from " << author << ": " << temp;
    if (childList.size()) {
        cout << endl;
    }
    //prints children recursive
    for (unsigned i = 0; i < childList.size(); ++i) {
        childList.at(i)->print(numVal + 2);
        if (i != childList.size()-1) {
            cout << endl;
        }
    }

}

const string& Entry::getSubject() const {
    return subject;
}

unsigned Entry::getID() const {
    return id;
}

void Entry::addChild(Entry* tempPtr) {
    childList.push_back(tempPtr);
}