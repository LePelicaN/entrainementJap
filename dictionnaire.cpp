#include "dictionnaire.h"

Dictionnaire::Dictionnaire()
{
   nbErreur_   = 0;

   srand( time( NULL ) );
}

Dictionnaire::~Dictionnaire()
{
}

void Dictionnaire::remiseAZero()
{
   vecteurHiragana_.clear();
   vecteurPasOkHiragana_.clear();
   vecteurKatakana_.clear();
   vecteurPasOkKatakana_.clear();
   multimapMot_.clear();
   multimapPasOkMot_.clear();
   nbErreur_   = 0;
}

void Dictionnaire::remiseAZeroMot()
{
   multimapMot_.clear();
   multimapPasOkMot_.clear();
   nbErreur_   = 0;
}

void Dictionnaire::remiseAZeroLoupe()
{
   ajouteLoupe_ = false;

   multimapLoupe_.clear();
   multimapPasOkLoupe_.clear();
}

void Dictionnaire::ajouterHiragana( const string & inHiraKata, const string & inRoumaji )
{
   vecteurHiragana_.push_back( Hiragana( inHiraKata, inRoumaji ) );
   vecteurPasOkHiragana_.push_back( Hiragana( inHiraKata, inRoumaji ) );
}

void Dictionnaire::ajouterKatakana( const string & inHiraKata, const string & inRoumaji )
{
   vecteurKatakana_.push_back( Katakana( inHiraKata, inRoumaji ) );
   vecteurPasOkKatakana_.push_back( Katakana( inHiraKata, inRoumaji ) );
}

void Dictionnaire::ajouterMot( const string & inHiraKata, const string & inRoumaji, const vector< string > & inFr )
{
   multimapMot_.insert( pair< string, Mot >( inHiraKata, Mot( inHiraKata, inRoumaji, &inFr ) ) );
   multimapPasOkMot_.insert( pair< string, Mot >( inHiraKata, Mot( inHiraKata, inRoumaji, &inFr ) ) );
}

void Dictionnaire::ajouterHiragana( Mot & inMot  )
{
   vecteurHiragana_.push_back( inMot );
   vecteurPasOkHiragana_.push_back( inMot );
}

void Dictionnaire::ajouterKatakana( Mot & inMot  )
{
   vecteurKatakana_.push_back( inMot );
   vecteurPasOkKatakana_.push_back( inMot );
}

void Dictionnaire::ajouterMot( Mot & inMot )
{
   multimapMot_.insert( pair< string, Mot >( inMot.getHiraKata(), inMot ) );
   multimapPasOkMot_.insert( pair< string, Mot >( inMot.getHiraKata(), inMot ) );
}

void Dictionnaire::aleaHiraKata( const int inTypeMot, const int inTypeParcours )
{
   switch ( inTypeMot )
   {
      // Hiragana
      case 0 :
         switch ( inTypeParcours )
         {
            // Total
            case 0 :
               ptVecteurCour_ =  &vecteurHiragana_;
               break;
            // Pas Ok
            case 1 :
               ptVecteurCour_ =  &vecteurPasOkHiragana_;
               break;
         }
         ptVecteur_        =  &vecteurHiragana_;
         ptVecteurPasOk_   =  &vecteurPasOkHiragana_;
         break;
      // Katakana
      case 1 :
         switch ( inTypeParcours )
         {
            // Total
            case 0 :
               ptVecteurCour_ =  &vecteurKatakana_;
               break;
            // Pas Ok
            case 1 :
               ptVecteurCour_  =  &vecteurPasOkKatakana_;
               break;
         }
         ptVecteur_        =  &vecteurKatakana_;
         ptVecteurPasOk_   =  &vecteurPasOkKatakana_;
         break;
   }

   ptMultimapCour_ = NULL;

   aleaPrec_       = (int)( (double)rand() / ( (double)RAND_MAX + 1 ) * ptVecteurCour_->size() );

   iteVecteur_     = ptVecteurCour_->begin() + aleaPrec_;

   motCourant_     = &( (*iteVecteur_) );
}

void Dictionnaire::aleaMot( const int inTypeMot, const int inTypeParcours )
{
   multimap< string, Mot >::iterator ite;

   switch ( inTypeMot )
   {
      // Mot
      case 2 :
         switch ( inTypeParcours )
         {
            // Total
            case 0 :
               ptMultimapCour_ = &multimapMot_;
               break;
            // Pas Ok
            case 1 :
               ptMultimapCour_ = &multimapPasOkMot_;
               /*
               std::cout << "Mot pas ok" << std::endl;
               std::cout << "\ptMultimapCour_->size() : " << ptMultimapCour_->size() << std::endl;
               for ( ite = ptMultimapCour_->begin(); ite != ptMultimapCour_->end(); ++ite )
               {
                  std::cout << "\t( ( *ite ).second ).getFr() : " << ( ( *ite ).second ).getFr() << std::endl;
               }
               */ 
               break;
         }
         ptMultimap_       = &multimapMot_;
         ptMultimapPasOk_  = &multimapPasOkMot_;
         break;
      // Loupe
      case 3 :
         switch ( inTypeParcours )
         {
            // Total
            case 0 :
               ptMultimapCour_ = &multimapLoupe_;
               break;
            // Pas Ok
            case 1 :
               ptMultimapCour_ = &multimapPasOkLoupe_;
               break;
         }
         ptMultimap_       = &multimapLoupe_;
         ptMultimapPasOk_  = &multimapPasOkLoupe_;
         break;
   }

   ptVecteurCour_ = NULL;

   aleaPrec_      = (int)( (double)rand() / ( (double)RAND_MAX + 1 ) * ptMultimapCour_->size() );

   iteMultimap_   = ptMultimapCour_->begin();
   for ( int i = 0; i < aleaPrec_; ++i, ++iteMultimap_ )
   {}

   motCourant_ = &( ( *( iteMultimap_ ) ).second );
}

void Dictionnaire::messageFin()
{
   QString       message;
   QMessageBox   msgBox;
   
   if ( nbErreur_ == 0 )
   {
      message = QString( "C'est un PERFECT !" );
   }
   else
   {
      message = QString( "Bravo, c'est fini ! (%0 erreur(s))" ).arg( nbErreur_ );
   }

   msgBox.setText( message );
   msgBox.exec();

   nbErreur_   = 0;
}

Mot * Dictionnaire::nouveauMot( const int inTypeMot, const int inTypeParcours, const bool inPrecValide )
{
   int tailleConteneur;

   switch ( inTypeMot )
   {
      case 0 :
         switch ( inTypeParcours )
         {
            case 0 :
            case 2 :
               tailleConteneur = vecteurHiragana_.size();
               break;
            case 1 :
               tailleConteneur = vecteurPasOkHiragana_.size();
               break;
         }
         break;
      case 1 :
         switch ( inTypeParcours )
         {
            case 0 :
            case 2 :
               tailleConteneur = vecteurKatakana_.size();
               break;
            case 1 :
               tailleConteneur = vecteurPasOkKatakana_.size();
               break;
         }
         break;
      case 2 :
         switch ( inTypeParcours )
         {
            case 0 :
            case 2 :
               tailleConteneur = multimapMot_.size();
               break;
            case 1 :
               tailleConteneur = multimapPasOkMot_.size();
               break;
         }
         break;
      case 3 :
         switch ( inTypeParcours )
         {
            case 0 :
            case 2 :
               tailleConteneur = multimapLoupe_.size();
               break;
            case 1 :
               tailleConteneur = multimapPasOkLoupe_.size();
               break;
         }
         break;
   }

   if ( tailleConteneur == 0 )
   {
      QMessageBox msgBox;
      msgBox.setText( "Liste vide !" );
      msgBox.exec();
   }
   else
   {
      if ( inPrecValide && ( ptVecteurCour_ == ptVecteurPasOk_ || ptMultimapCour_ == ptMultimapPasOk_ ) )
      {
         if ( ptVecteurCour_ )
         {
            if ( ptVecteurPasOk_->size() > 1 )
            {
               ptVecteurPasOk_->erase( iteVecteur_ );
            }
            else
            {
               messageFin();
               *ptVecteurPasOk_ = *ptVecteur_;
            }
         }
         else
         {
            if ( ptMultimapPasOk_->size() > 1 )
            {
               ptMultimapPasOk_->erase( iteMultimap_ );
            }
            else
            {
               messageFin();
               *ptMultimapPasOk_ = *ptMultimap_;
            }
         }
      }

      switch ( inTypeParcours )
      {
         case 0:
         case 1:
            switch ( inTypeMot )
            {
               case 0 :
               case 1 :
                  aleaHiraKata( inTypeMot, inTypeParcours );
                  break;
               case 2 :
               case 3 :
                  aleaMot( inTypeMot, inTypeParcours );
                  break;
            }
            break;
         case 2:
            switch ( inTypeMot )
            {
               case 0 :
               case 1 :
                  ++iteVecteur_;
                  if ( iteVecteur_ == ptVecteurCour_->end() )
                  {
                     iteVecteur_ = ptVecteurCour_->begin();
                  }
                  motCourant_ = &( (*iteVecteur_) );
                  break;
               case 2 :
               case 3 :
                  ++iteMultimap_;
                  if ( iteMultimap_ == ptMultimapCour_->end() )
                  {
                     iteMultimap_ = ptMultimapCour_->begin();
                  }
                  motCourant_ = &( ( *( iteMultimap_ ) ).second );
                  break;
            }
            break;
      }

      ajouteLoupe_ = false;
   }

   return motCourant_;
}

int Dictionnaire::existMulti( vector< string > & inSaisieFr )
{
   int out;
   pair< multimap< string, Mot >::iterator,
         multimap< string, Mot >::iterator >  retour;
   multimap< string, Mot >::iterator          it;

   pair< vector< string >::iterator, vector< string >::iterator > retourMatch;

   out = 0;

   if ( multimapMot_.count( motCourant_->getHiraKata() ) > 1 )
   {
      retour = ptMultimap_->equal_range( motCourant_->getHiraKata() );
      it     = retour.first;
      it     = ptMultimap_->find( motCourant_->getHiraKata() );

      while ( it != retour.second && !( (*it).second.verifFr( inSaisieFr ) ) )
      {
         ++it;
      }

      if ( (*it).second.verifFr( inSaisieFr ) )
      {
         out            = 2;
         //iteMultimap_   = it;
         //motCourant_    = &( ( *it ).second );
      }
      else if ( ptMultimapCour_ != &multimapMot_ )
      {
         retour = multimapMot_.equal_range( motCourant_->getHiraKata() );
         it     = retour.first;

         while ( it != retour.second && !( (*it).second.verifFr( inSaisieFr ) ) )
         {
            ++it;
         }

         if ( (*it).second.verifFr( inSaisieFr ) )
         {
            out = 2;
         }
      }
   }

   return out;
}

void Dictionnaire::loupe( const bool inEnregistrLoupe )
{
   ++nbErreur_;

   if ( inEnregistrLoupe && !ajouteLoupe_ && ptMultimap_ != &multimapPasOkLoupe_ )
   {
      multimapLoupe_.insert( pair< string, Mot >( motCourant_->getHiraKata(), *motCourant_ ) );
      multimapPasOkLoupe_.insert( pair< string, Mot >( motCourant_->getHiraKata(), *motCourant_ ) );

      ajouteLoupe_ = true;
   }
}

std::ostream & operator<<( std::ostream & o, Dictionnaire & inDictionnaire )
{
   vector< Mot >::iterator    itVecteur;
   int                        i;
   int                        nbIte;
   string                     sep;

   o << "	Hiragana" << std::endl;

   for ( i = 0, itVecteur = inDictionnaire.vecteurHiragana_.begin();
         itVecteur != inDictionnaire.vecteurHiragana_.end();
         ++i )
   {
      switch ( i )
      {
         case 7:
            nbIte = 3;
            break;
         case 9:
            nbIte = 2;
            break;
         case 10:
            nbIte = 1;
            break;
         default:
            nbIte = 5;
            break;
      }

      sep = "";
      for ( int i = 0; i < nbIte && itVecteur != inDictionnaire.vecteurHiragana_.end(); ++i, ++itVecteur )
      {
         o << sep << (*itVecteur).getHiraKata() << ":" << (*itVecteur).getRoumaji();
         sep = ";";
      }

      o << std::endl;
   }

   o << "\n	Katakana" << std::endl;

   for ( i = 0, itVecteur = inDictionnaire.vecteurKatakana_.begin();
         itVecteur < inDictionnaire.vecteurKatakana_.end();
         ++i )
   {
      switch ( i )
      {
         case 7:
            nbIte = 3;
            break;
         case 9:
            nbIte = 2;
            break;
         case 10:
            nbIte = 1;
            break;
         default:
            nbIte = 5;
            break;
      }

      sep = "";
      for ( int i = 0; i < nbIte && itVecteur != inDictionnaire.vecteurKatakana_.end(); ++i, ++itVecteur )
      {
         o << sep << (*itVecteur).getHiraKata() << ":" << (*itVecteur).getRoumaji();
         sep = ";";
      }

      o << std::endl;
   }
   return o;
}
