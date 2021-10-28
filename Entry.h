#ifndef __ENTRY_H__
#define __ENTRY_H__

#include <string>
#include <sstream>
#include <vector>
using namespace std;

class Entry {
 protected:
	string author;
	string subject;
	string body;
	unsigned id; 
	vector<Entry *> childList;

 public:
	Entry();
	Entry(const string &, 
	        const string &, 
	        const string &, 
	        unsigned);
	virtual ~Entry();

	virtual bool isGenre() const = 0;	 
	virtual string toFormattedString() const = 0;  
      
	void print(unsigned) const;
	const string & getSubject() const;
	unsigned getID() const;
	void addChild(Entry *);
};

#endif