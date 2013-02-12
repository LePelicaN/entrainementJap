#include "katakana.h"

Katakana::Katakana( const string & inHiraKata, const string & inRoumaji ):
Mot( inHiraKata, inRoumaji )
{
   isHiraKata_ = true;
}

Katakana::~Katakana()
{
}
