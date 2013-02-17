
#ifndef RECHERCHE_MOT_CHERCHER_MOT_ENTRAINEMENT_JAP
#define RECHERCHE_MOT_CHERCHER_MOT_ENTRAINEMENT_JAP

#include "../../Mot.h"

#include <string>

class ChercheurMot
{
   public:
      static std::vector< Mot > Chercher( const std::string & inMotARechercher );

   private:
      ChercheurMot();
      ChercheurMot( const ChercheurMot & );
      ChercheurMot operator=( const ChercheurMot & );
};

#endif // RECHERCHE_MOT_CHERCHER_MOT_ENTRAINEMENT_JAP
