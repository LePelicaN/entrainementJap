#ifndef HIRAGANA_H
#define HIRAGANA_H

#include "mot.h"

class Hiragana : public Mot
{

public:
   Hiragana( const string & inHiraKata, const string & inRoumaji );
   virtual ~Hiragana();

};

#endif
