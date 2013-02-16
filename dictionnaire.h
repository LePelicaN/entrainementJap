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

struct ModeMot
{
   enum Enum
   {
      Hiragana,
      Katakana,
      Mot
   };
};
struct ModeLoupe
{
   enum Enum
   {
      Normal,
      LoupeUniquement
   };
};

class Dictionnaire
{

protected:
   vector< Mot >                       vecteurHiragana_;
   vector< Mot >                       vecteurHiraganaLoupe_;
   vector< Mot >                       vecteurKatakana_;
   vector< Mot >                       vecteurKatakanaLoupe_;
   multimap< string, Mot >             multimapMot_;
   multimap< string, Mot >             multimapMotLoupe_;

   vector< Mot >                       vecteurPasOkHiragana_;
   vector< Mot >                       vecteurPasOkHiraganaLoupe_;
   vector< Mot >                       vecteurPasOkKatakana_;
   vector< Mot >                       vecteurPasOkKatakanaLoupe_;
   multimap< string, Mot >             multimapPasOkMot_;
   multimap< string, Mot >             multimapPasOkMotLoupe_;

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

   void aleaHiragana( ModeLoupe::Enum inModeLoupe, const int inTypeParcours );
   void aleaKatakana( ModeLoupe::Enum inModeLoupe, const int inTypeParcours );
   void aleaMot( ModeLoupe::Enum inModeLoupe, const int inTypeParcours );

   void  messageFin();

   Mot * nouveauMot( ModeMot::Enum inModeMot, ModeLoupe::Enum inModeLoupe,
                     const int inTypeParcours, const bool inPrecValide );

   int existMulti( vector< string > & inSaisieFr );

   void loupe( ModeMot::Enum inModeMot,
               const bool inEnregistrLoupe,
               unsigned int nbAjout );

   friend std::ostream & operator<<( std::ostream & o, Dictionnaire & inDictionnaire );
};

#endif
