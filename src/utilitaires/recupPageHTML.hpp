
#ifndef RECUP_PAGE_HTML_HPP_NOUVOCHAP
#define RECUP_PAGE_HTML_HPP_NOUVOCHAP

#include <QtNetwork/QNetworkAccessManager>

#include <string>

#include "iRecupPageHTML.hpp"

class RecupPageHTML : public IRecupPageHTML
{
   Q_OBJECT

   private :
      QNetworkAccessManager   nam_;

   public :
      virtual void recuperationAsynchrone( const std::string & inUrl );
      virtual std::string recuperationSynchrone( const std::string & inUrl );

   private slots:
      std::string telechargementPageFini( QNetworkReply * inReponse );
};

#endif // RECHERCHE_GOOGLE_HPP_NOUVOCHAP
