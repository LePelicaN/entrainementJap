#include "hiragana.h"

Hiragana::Hiragana( const string & inHiraKata, const string & inRoumaji ):
Mot( inHiraKata, inRoumaji )
{
   isHiraKata_ = true;
}

Hiragana::~Hiragana()
{
}
