
#include "chercheurMot.hpp"

#include <regexBuilder.hpp>
#include <utilitaires/fonctionsClasseString.hpp>
#include <utilitaires/recupPageHTML.hpp>

#include <boost/regex.hpp>

#include <sstream>

namespace
{

std::string createURL( const std::string & inMotARechercher )
{
   std::ostringstream url;
   url << "http://www.dictionnaire-japonais.com/search.php?w=";
   url << inMotARechercher;
   url << "&t=1";
   return url.str();
}

int extractNbResultats( const std::string & inCodePage )
{
   int nbResultats = -1;

   RegexBuilder regexBuilder( "./regex/DictionnaireJaponais.regex" );
   std::string regExpStr = regexBuilder.getRegex( "nombre_resultat" );
   boost::regex regExp( regExpStr );
   boost::smatch resultats;

   if( boost::regex_match( inCodePage, resultats, regExp, boost::match_extra ) )
   {
      std::istringstream iss( resultats[ 1 ] );
      iss >> nbResultats;
   }

   return nbResultats;
}

std::vector< std::string > * parserMot( const std::string & inMotsFrancais )
{
   std::vector< std::string > * outListeMotsFrancais = new std::vector< std::string >();
   
   std::istringstream issMotsFrancais( inMotsFrancais );
   std::string motFrancais;
   while ( std::getline( issMotsFrancais, motFrancais, ',' ) )
   {
      outListeMotsFrancais->push_back( trim( motFrancais ) );
   }

   return outListeMotsFrancais;
}

std::vector< Mot > extractMots( const std::string & inCodePage )
{
   std::vector< Mot > outListeMots;

   RegexBuilder regexBuilder( "./regex/DictionnaireJaponais.regex" );
   std::string    regExpStr = regexBuilder.getRegex( "liste_mots" );
   boost::regex   regExp( regExpStr );
   boost::smatch  resultats;

   if( boost::regex_match( inCodePage, resultats, regExp, boost::match_extra ) )
   {
      for( unsigned int i = 0; i < resultats.captures( 1 ).size(); ++i )
      {
         std::string harakata = resultats.captures( 1 )[ i ];
         std::string kanji = resultats.captures( 2 )[ i ];
         std::string romanji = resultats.captures( 3 )[ i ];
         std::string francais = resultats.captures( 4 )[ i ];

         outListeMots.push_back( Mot( harakata, romanji, parserMot( francais ) ) );
      }
   }

   return outListeMots;
}

std::vector< Mot > parser( const std::string & inCodePage )
{
   std::vector< Mot > outListeMots;

   try
   {
      int nbResultats = extractNbResultats( inCodePage );
      if ( nbResultats > 0 )
      {
         outListeMots = extractMots( inCodePage );
      }
   }
   catch (std::exception e)
   {
   }

   return outListeMots;
}

} // unnamed namespace


std::vector< Mot > ChercheurMot::Chercher( const std::string & inMotARechercher )
{
   RecupPageHTML recupPageHTML;
   std::string codePage = recupPageHTML.recuperationSynchrone( createURL( inMotARechercher ) );
   return parser( codePage );
}
