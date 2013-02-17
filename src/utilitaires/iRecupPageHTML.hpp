
#ifndef IRECUP_PAGE_HTML_HPP_NOUVOCHAP
#define IRECUP_PAGE_HTML_HPP_NOUVOCHAP

#include <QtCore/QObject>
#include <QtNetwork/QNetworkReply>

#include <string>

class IRecupPageHTML : public QObject
{
   Q_OBJECT

   public :
      virtual ~IRecupPageHTML() {};

      virtual const std::string & getPageHTML() const { return pageHTML_; }
      virtual QNetworkReply::NetworkError getErreurReception() const { return erreurReception_; }

      virtual void recuperationAsynchrone( const std::string & inUrl ) = 0;
      virtual std::string recuperationSynchrone( const std::string & inUrl ) = 0;

   signals :
      void envoiePage( const std::string & outPageHTML );
      void erreurTelechargement( QNetworkReply::NetworkError outErreur );

   protected :
      std::string                   pageHTML_;
      QNetworkReply::NetworkError   erreurReception_;
};

#endif // RECHERCHE_GOOGLE_HPP_NOUVOCHAP
