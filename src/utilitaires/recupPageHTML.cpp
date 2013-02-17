
#include "recupPageHTML.hpp"

#include <QtCore/QUrl>
#include <QtCore/QEventLoop>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

void RecupPageHTML::recuperationAsynchrone( const std::string & inUrl )
{
   connect( &nam_, SIGNAL( finished( QNetworkReply * ) ),
            this,  SLOT(   telechargementPageFini( QNetworkReply * ) ) );

   QUrl  url;
   url.setEncodedUrl( inUrl.c_str() );

   nam_.get( QNetworkRequest( url ) );
}

std::string RecupPageHTML::recuperationSynchrone( const std::string & inUrl )
{
   QUrl  url;
   url.setEncodedUrl( inUrl.c_str() );

   QNetworkReply *   reponse;

   while( 1 )
   {
      reponse  = nam_.get( QNetworkRequest( url ) );

      QEventLoop     eLoop;
      connect( &nam_,  SIGNAL( finished( QNetworkReply * ) ),
               &eLoop, SLOT(   quit() ) );
      eLoop.exec();

      QUrl redirection = reponse->attribute( QNetworkRequest::RedirectionTargetAttribute ).toUrl();
      if ( redirection.isValid() )
      {
         url   = redirection;
         reponse->deleteLater();
      }
      else
      {
         break;
      }
   }

   return telechargementPageFini( reponse );
}

std::string RecupPageHTML::telechargementPageFini( QNetworkReply * inReponse )
{
   QUrl redirection = inReponse->attribute( QNetworkRequest::RedirectionTargetAttribute ).toUrl();
   if ( redirection.isValid() )
   {
      nam_.get( QNetworkRequest( redirection ) );
      return "";
   }

   disconnect( &nam_, SIGNAL( finished( QNetworkReply * ) ),
               this,  SLOT(   telechargementPageFini( QNetworkReply * ) ) );

   erreurReception_  = inReponse->error();
   if ( erreurReception_ == QNetworkReply::NoError )
   {
      pageHTML_   = QString( inReponse->readAll() ).toStdString();

      emit envoiePage( pageHTML_ );
   }
   else
   {
      pageHTML_   = "";
      emit erreurTelechargement( inReponse->error() );
   }

   inReponse->deleteLater();
   return pageHTML_;
}
