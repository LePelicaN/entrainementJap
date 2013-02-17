
#include "rechercheGoogle.hpp"

#include <boost/regex.hpp>

#include <QtCore/QUrl>
#include <QtCore/QEventLoop>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

RegexBuilder RechercheGoogle::RegexBuilderGoogle_( "./regex/google.regex" );

std::string RechercheGoogle::creationUrl( const std::string & inTexteARechercher )
{
   std::string    outUrl   = "";
   outUrl   = "http://www.google.fr/search?hl=fr&q=";
   outUrl  += inTexteARechercher;

   return outUrl;
}

void RechercheGoogle::rechercheAsynchrone( const std::string & inTexteARechercher )
{
   connect( &nam_, SIGNAL( finished( QNetworkReply * ) ),
            this,  SLOT(   telechargementPageFiniGoogle( QNetworkReply * ) ) );

   QUrl  urlGoogle;
   urlGoogle.setEncodedUrl( creationUrl( inTexteARechercher ).c_str() );

   nam_.get( QNetworkRequest( urlGoogle ) );
}

std::vector< std::string >  RechercheGoogle::rechercheSynchrone( const std::string & inTexteARechercher )
{
   QUrl  urlGoogle;
   urlGoogle.setEncodedUrl( creationUrl( inTexteARechercher ).c_str() );

   QNetworkReply *   reponse;
   reponse  = nam_.get( QNetworkRequest( urlGoogle ) );

   QEventLoop     eLoop;
   connect( &nam_,  SIGNAL( finished( QNetworkReply * ) ),
            &eLoop, SLOT(   quit() ) );
   eLoop.exec();

   return telechargementPageFiniGoogle( reponse );
}
#include <iostream>
std::vector< std::string > RechercheGoogle::telechargementPageFiniGoogle( QNetworkReply * inReponse )
{
   disconnect( &nam_, SIGNAL( finished( QNetworkReply * ) ),
               this,  SLOT(   telechargementPageFiniGoogle( QNetworkReply * ) ) );

   if ( inReponse->error() == QNetworkReply::NoError )
   {
      std::string    pageHTML    = QString( inReponse->readAll() ).toStdString();

      std::string    regExpStr = RegexBuilderGoogle_.getRegex( "home" );                              
      boost::regex   regExp( regExpStr );
      boost::smatch  resultats;

      if( boost::regex_match( pageHTML, resultats, regExp, boost::match_extra ) )
      {
         std::vector< std::string >    outLiens;
         for (
               unsigned int indiceReponse = 0;
               indiceReponse < resultats.captures( 1 ).size();
               ++indiceReponse
             )
         {
            outLiens.push_back( resultats.captures( 1 )[ indiceReponse ] );
         }

         emit envoieResultat( outLiens );

         return outLiens;
      }
      else
      {
         // TODO : Gestion de l'erreur ! -> prevenir l'utilisateur
      }
   }
   else
   {
      // TODO : Gestion de l'erreur ! -> prevenir l'utilisateur
   }

   return std::vector< std::string >();
}
