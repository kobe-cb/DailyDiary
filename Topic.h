#ifndef __TOPIC_H__
#define __TOPIC_H__

#include "Entry.h"

class Topic : public Entry {
   
 public:
	Topic();
	Topic(const string &, 
	      const string &, 
	      const string &, 
	      unsigned);
	
	bool isGenre() const;
	string toFormattedString() const;
};

#endif