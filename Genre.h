 #ifndef __GENRE_H__
#define __GENRE_H__

#include "Entry.h"

class Genre : public Entry {
  public:
    Genre();
    Genre(const string&,
          const string&,
          const string&,
          unsigned);
    
    bool isGenre() const;
    string toFormattedString() const;
};

#endif