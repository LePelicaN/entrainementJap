
#ifndef RECHERCHE_GOOGLE_HPP_NOUVOCHAP
#define RECHERCHE_GOOGLE_HPP_NOUVOCHAP

#include <QtNetwork/QNetworkAccessManager>

#include <string>
#include <vector>

#include <regexBuilder.hpp>

class RechercheGoogle : public QObject
{
   Q_OBJECT

   private :
      static RegexBuilder     RegexBuilderGoogle_;

      QNetworkAccessManager   nam_;

      std::string creationUrl( const std::string & inTexteARechercher );

      bool analyse( const std::string & inPageHTML );

   public :
      void rechercheAsynchrone( const std::string & inTexteARechercher );
      std::vector< std::string > rechercheSynchrone( const std::string & inTexteARechercher );

   private slots:
      std::vector< std::string > telechargementPageFiniGoogle( QNetworkReply * inReponse );

   signals :
      void envoieResultat( const std::vector< std::string > & inLiens );
};

#endif // RECHERCHE_GOOGLE_HPP_NOUVOCHAP
