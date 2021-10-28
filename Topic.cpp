#include "Topic.h"
#include "kbDependencies.h"
using namespace std;

Topic::Topic() : Entry() {
}

Topic::Topic(const string& strAuthor,
             const string& strSubject,
             const string& strBody,
             unsigned numID) : Entry  (strAuthor, 
                                       strSubject, 
                                       strBody, 
                                       numID){
}

bool Topic::isGenre() const {
    return false;
}

string Topic::toFormattedString() const {
    ostringstream output;

    string strID("");
    strID = to_string(id);
  
    output << "<begin_topic>\n"
        << ":id: " << strID << "\n"
        << ":subject: " << subject << "\n" 
        << ":from: " << author << "\n";

        if (childList.size() != 0) {
            output << ":children: ";
            for (unsigned int i = 0; i < childList.size(); ++i) {
                if (i == childList.size() - 1) {
                    output << childList.at(i)->getID();
                }
                else {
                    output << childList.at(i)->getID() << " ";
                }
            }
            output << endl;
        }

        output << ":body: " << body;
        if (body.at(body.size()-1) != '\n') {
            output << '\n';
        }
        
        output << "<end>" << endl;

    return output.str();
}