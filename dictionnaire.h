#ifndef DICTIONNAIRE_H
#define DICTIONNAIRE_H

#include <QMessageBox>

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <utility>

#include "hiragana.h"
#include "katakana.h"
#include "mot.h"

using std::vector;
using std::multimap;
using std::pair;
using std::iterator;

class Dictionnaire
{

protected:
   vector< Mot >                       vecteurHiragana_;
   vector< Mot >                       vecteurKatakana_;
   multimap< string, Mot >             multimapMot_;
   multimap< string, Mot >             multimapLoupe_;

   vector< Mot >                       vecteurPasOkHiragana_;
   vector< Mot >                       vecteurPasOkKatakana_;
   multimap< string, Mot >             multimapPasOkMot_;
   multimap< string, Mot >             multimapPasOkLoupe_;

   Mot                               * motCourant_;
   vector< Mot >                     * ptVecteurCour_;
   multimap< string, Mot >           * ptMultimapCour_;
   vector< Mot >                     * ptVecteur_;
   multimap< string, Mot >           * ptMultimap_;
   vector< Mot >                     * ptVecteurPasOk_;
   multimap< string, Mot >           * ptMultimapPasOk_;

   vector< Mot >::iterator             iteVecteur_;
   multimap< string, Mot >::iterator   iteMultimap_;

   int                     aleaPrec_;

   bool                    ajouteLoupe_;

   int                     nbErreur_;

public:
   Dictionnaire();
   virtual ~Dictionnaire();

   void remiseAZero();
   void remiseAZeroMot();
   void remiseAZeroLoupe();

   void ajouterHiragana( const string & inHiraKata, const string & inRoumaji );
   void ajouterKatakana( const string & inHiraKata, const string & inRoumaji );
   void ajouterMot(      const string & inHiraKata, const string & inRoumaji , const vector< string > & inFr );
   void ajouterHiragana( Mot & inMot  );
   void ajouterKatakana( Mot & inMot  );
   void ajouterMot(      Mot & inMot );

   void aleaHiraKata( const int inTypeMot, const int inTypeParcours );
   void aleaMot(      const int inTypeMot, const int inTypeParcours );

   void  messageFin();

   Mot * nouveauMot( const int inTypeMot, const int inTypeParcours, const bool inPrecValide );

   int existMulti( vector< string > & inSaisieFr );

   void loupe( const bool inEnregistrLoupe );

   friend std::ostream & operator<<( std::ostream & o, Dictionnaire & inDictionnaire );
};

#endif
