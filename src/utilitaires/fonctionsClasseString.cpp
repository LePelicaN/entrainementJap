
#include "fonctionsClasseString.hpp"

std::string replace( const std::string & inStr, const std::string & inCh1, const std::string & inCh2 )
{
   std::string    outChaineRetour;
   size_t         found;

   outChaineRetour   = inStr;
   found             = outChaineRetour.find( inCh1 );

   while ( found != std::string::npos )
   {
      outChaineRetour.erase( found, inCh1.length() );
      outChaineRetour.insert( found, inCh2 );

      found          = outChaineRetour.find( inCh1, found + 1 );
   }

   return outChaineRetour;
}

std::string trim( std::string & inStr )
{
   for ( std::string::iterator it = inStr.begin(); it < inStr.end() && (*it) == ' '; ++it )
   {
      inStr.erase ( it );
   }
   return inStr;
}
