#ifndef KATAKANA_H
#define KATAKANA_H

#include "mot.h"

class Katakana : public Mot
{

public:
   Katakana( const string & inHiraKata, const string & inRoumaji );
   virtual ~Katakana();

};

#endif
