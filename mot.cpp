#include "mot.h"

Mot::Mot( const string & inHiraKata, const string & inRoumaji, const vector< string > * inFr ):
hiraKata_( inHiraKata ), roumaji_( inRoumaji ), isHiraKata_( false )
{
   if ( inFr != NULL )
   {
      fr_ = *inFr;
   }
}

Mot::~Mot()
{}

string Mot::getStringFr() const
{
   string out = "";
   string sep = "";
   
   for ( vector< string >::const_iterator it = fr_.begin(); it != fr_.end(); ++it )
   {
      out += sep + (*it);
      sep = ", ";
   }

   return out;
}

std::string Mot::toString() const
{
    return getHiraKata() + ":" + getRoumaji() + ":" + getStringFr();
}

bool Mot::verifFr( vector< string > & inFr )
{
   bool out;
   
   if ( inFr.size() != fr_.size() )
   {
      out = false;
   }
   else
   {
      pair< vector< string >::iterator, vector< string >::iterator > retourMismatch;

      retourMismatch = mismatch ( fr_.begin(), fr_.end(), inFr.begin() );

      out = ( retourMismatch.first == fr_.end() );
   }
   
   return out;
}
