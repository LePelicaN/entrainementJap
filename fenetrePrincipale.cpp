#include "fenetrePrincipale.h"

#include <rechercheMot/chercheurMot.hpp>

namespace {

QTextEdit * FabriqueTextEdit()
{
   QTextEdit * textEdit = new QTextEdit();
   textEdit->setTabChangesFocus( true );
   textEdit->setFontPointSize( 16 );
   textEdit->setFixedHeight( 36 );
   return textEdit;
}

} // unnamed namespace

FenetrePrincipale::FenetrePrincipale( const string inFileName, QWidget * parent ):
QWidget( parent )
{
   dictionnaire_              = new Dictionnaire;

   nomFichier_                = inFileName;

   messagePresent_            = false;

   //choixI_                    = 2;
   modeMot_ = ModeMot::Mot;
   modeloupe_ = ModeLoupe::Normal;
   choixII_                   = 1;

   enregistrLoupe_            = false;

   filtreEnter_               = new FiltreEnter();


   pushButtonRecharger_       = new QPushButton( tr( "Recharger Fichier" ) );
   pushButtonEditer_          = new QPushButton( tr( "Editer Fichier" ) );

   groupBoxRadioBI_           = new QGroupBox( tr( "Choix exercice I" ) );

   hBoxLayoutRadioI_          = new QHBoxLayout;

   radioHiragana_             = new QRadioButton( tr( "Hiragana" ) );
   radioKatakana_             = new QRadioButton( tr( "Katakana" ) );
   radioMot_                  = new QRadioButton( tr( "Mot" ) );
   loupeUniquement_ = new QCheckBox( tr( "Échoués uniquement" ) );

   groupBoxRadioBII_          = new QGroupBox( tr( "Choix exercice II" ) );
   hBoxLayoutRadioII_         = new QHBoxLayout;

   radioTotalAlea_            = new QRadioButton( tr( "Total aléatoire" ) );
   radioAleaSansOk_           = new QRadioButton( tr( "Aléatoire sans Ok" ) );
   radioALaSuite_             = new QRadioButton( tr( "A la Suite" ) );

   pushButtonDemarrerLoupe_   = new QPushButton( tr( "Démarrer Mots Loupés" ) );
   pushButtonArreterLoupe_    = new QPushButton( tr( "Arrêt Mots Loupés" ) );
   pushButtonRemiseAZeroLoupe_= new QPushButton( tr( "Remise à Zéro des Mots Loupés" ) );

   pushButtonEffacer_         = new QPushButton( tr( "Effacer (Left)" ) );

   labelEntrHiraKata_         = new QLabel( tr( "Hiragana / Katakana :" ) );
   labelEntrRoumaji_          = new QLabel( tr( "Roumaji : " ) );
   labelEntrFr_               = new QLabel( tr( "Français : " ) );

   textEditEntrHiraKata_      = FabriqueTextEdit();
   textEditEntrRoumaji_       = FabriqueTextEdit();
   textEditEntrFr_            = FabriqueTextEdit();

   labelResultat_             = new QLabel;

   pushButtonValider_         = new QPushButton( tr( "Valider (Enter)" ) );
   pushButtonReponse_         = new QPushButton( tr( "Réponse (Up)" ) );
   pushButtonNouveau_         = new QPushButton( tr( "Nouveau (Down)" ) );
/*
   textEditAjoutJap_          = new QTextEdit;
   textEditAjoutFr_           = new QTextEdit;

   pushButtonAjoutHiragana_   = new QPushButton( tr( "Ajout Hiragana" ) );
   pushButtonAjoutKatakana_   = new QPushButton( tr( "Ajout Katakana" ) );
   pushButtonAjoutMot_        = new QPushButton( tr( "AjoutMot" ) );
*/

   //modelGroupe_               = new QStandardItemModel;
   arbreGroupe_               = new QTreeWidget;
   pushButtonAppliquer_       = new QPushButton( tr( "Appliquer modifications" ) );


   resize( 1144, 300 );

   pushButtonRecharger_->setFont( QFont( "Times", 14 ) );
   pushButtonEditer_->setFont( QFont( "Times", 14 ) );

   radioHiragana_->setFont( QFont( "Times", 14 ) );
   radioKatakana_->setFont( QFont( "Times", 14 ) );
   radioMot_->setFont( QFont( "Times", 14 ) );
   loupeUniquement_->setFont( QFont( "Times", 14 ) );

   hBoxLayoutRadioI_->addWidget( radioHiragana_ );
   hBoxLayoutRadioI_->addWidget( radioKatakana_ );
   hBoxLayoutRadioI_->addWidget( radioMot_ );
   hBoxLayoutRadioI_->addWidget( loupeUniquement_ );

   groupBoxRadioBI_->setLayout( hBoxLayoutRadioI_ );

   radioMot_->setChecked( true );

   radioTotalAlea_->setFont( QFont( "Times", 14 ) );
   radioAleaSansOk_->setFont( QFont( "Times", 14 ) );
   radioALaSuite_->setFont( QFont( "Times", 14 ) );

   hBoxLayoutRadioII_->addWidget( radioTotalAlea_ );
   hBoxLayoutRadioII_->addWidget( radioAleaSansOk_ );
   hBoxLayoutRadioII_->addWidget( radioALaSuite_ );

   groupBoxRadioBII_->setLayout( hBoxLayoutRadioII_ );

   radioAleaSansOk_->setChecked( true );

   pushButtonDemarrerLoupe_->setFont( QFont( "Times", 14 ) );
   pushButtonArreterLoupe_->setFont( QFont ( "Times", 14 ) );
   pushButtonArreterLoupe_->hide();
   pushButtonRemiseAZeroLoupe_->setFont( QFont ( "Times", 14 ) );

   pushButtonEffacer_->setFont( QFont ( "Times", 14 ) );

   labelEntrHiraKata_->setFont( QFont ( "Times", 14 ) );
   labelEntrRoumaji_->setFont( QFont ( "Times", 14 ) );
   labelEntrFr_->setFont( QFont ( "Times", 14 ) );

   textEditEntrHiraKata_->setReadOnly( true );
   textEditEntrRoumaji_->installEventFilter( filtreEnter_ );
   textEditEntrFr_->installEventFilter( filtreEnter_ );

   labelResultat_->setFixedHeight( 34 );

   pushButtonValider_->setFont( QFont( "Times", 12 ) );
   pushButtonReponse_->setFont( QFont( "Times", 12 ) );
   pushButtonNouveau_->setFont( QFont( "Times", 12 ) );
/*
   textEditAjoutJap_->setTabChangesFocus( true );
   textEditAjoutJap_->setFontPointSize( 12 );
   textEditAjoutJap_->setFixedHeight( 26 );

   textEditAjoutFr_->setTabChangesFocus( true );
   textEditAjoutFr_->setFontPointSize( 12 );
   textEditAjoutFr_->setFixedHeight( 26 );

   pushButtonAjoutHiragana_->setFont( QFont( "Times", 12 ) );
   pushButtonAjoutKatakana_->setFont( QFont( "Times", 12 ) );
   pushButtonAjoutMot_->setFont( QFont( "Times", 12 ) );
*/

   arbreGroupe_->setColumnCount( 1 );
   arbreGroupe_->setHeaderLabels( QStringList() << tr( "Groupe" ) );

   pushButtonAppliquer_->setFont( QFont( "Times", 12 ) );


   QGridLayout * gridLayout = new QGridLayout;

   gridLayout->addWidget( pushButtonRecharger_, 0, 1, 1, 2 );
   gridLayout->addWidget( pushButtonEditer_, 0, 3, 1, 2 );

   gridLayout->addWidget( groupBoxRadioBI_, 1, 0, 1, 6 );

   gridLayout->addWidget( groupBoxRadioBII_, 2, 0, 1, 6 );

   gridLayout->addWidget( pushButtonDemarrerLoupe_,    3, 0, 1, 2 );
   gridLayout->addWidget( pushButtonArreterLoupe_,     3, 0, 1, 2 );
   gridLayout->addWidget( pushButtonRemiseAZeroLoupe_, 3, 2, 1, 2 );
   gridLayout->addWidget( pushButtonEffacer_,          3, 4, 1, 2 );

   gridLayout->addWidget( labelEntrHiraKata_,    4, 0, 1, 1 );
   gridLayout->addWidget( labelEntrRoumaji_, 5, 0, 1, 1 );
   gridLayout->addWidget( labelEntrFr_,      6, 0, 1, 1 );

   gridLayout->addWidget( textEditEntrHiraKata_,  4, 1, 1, 5 );
   gridLayout->addWidget( textEditEntrRoumaji_,   5, 1, 1, 5 );
   gridLayout->addWidget( textEditEntrFr_,        6, 1, 1, 5 );

   gridLayout->addWidget( labelResultat_,  7, 2, 1, 2 );

   gridLayout->addWidget( pushButtonValider_, 8, 0, 1, 2 );
   gridLayout->addWidget( pushButtonReponse_, 8, 2, 1, 2 );
   gridLayout->addWidget( pushButtonNouveau_, 8, 4, 1, 2 );
/*
   gridLayout->addWidget( textEditAjoutJap_, 7, 0, 1, 3 );
   gridLayout->addWidget( textEditAjoutFr_,  7, 3, 1, 3 );
   gridLayout->addWidget( pushButtonAjoutHiragana_, 8, 0, 1, 2 );
   gridLayout->addWidget( pushButtonAjoutKatakana_, 8, 2, 1, 2 );
   gridLayout->addWidget( pushButtonAjoutMot_,      8, 4, 1, 2 );
*/
   gridLayout->addWidget( arbreGroupe_, 0, 6, 8, 1 );
   gridLayout->addWidget( pushButtonAppliquer_, 8, 6, 1, 1 );

   afficherRomaji_ = new QCheckBox( "Afficher les romajis" );
   gridLayout->addWidget( afficherRomaji_, 9, 0, 1, 1 );

   labelNbAjout_ = new QLabel( tr( "Nombre d'ajout par erreur" ) );
   nbAjout_ = new QSpinBox;
   nbAjout_->setValue( 2 );
   gridLayout->addWidget( labelNbAjout_, 10, 0, 1, 1 );
   gridLayout->addWidget( nbAjout_, 10, 1, 1, 1 );
/*
   textEditAjoutJap_->hide();
   textEditAjoutFr_->hide();
   pushButtonAjoutHiragana_->hide();
   pushButtonAjoutKatakana_->hide();
   pushButtonAjoutMot_->hide();
*/
   for ( int i = 0; i < 6; ++i )
   {
      gridLayout->setColumnMinimumWidth ( i, 50 );
      gridLayout->setColumnStretch( i, 1 );
   }

   setLayout(gridLayout);

   QSize size = arbreGroupe_->size();
   size.setWidth( 50 );
   arbreGroupe_->resize( size );

   textEditEntrRoumaji_->setFocus( Qt::OtherFocusReason );

   chargementFichier();


   connect( pushButtonRecharger_, SIGNAL( clicked() ),
            this,                 SLOT(   chargementFichier() ) );
   connect( pushButtonEditer_, SIGNAL( clicked() ),
            this,               SLOT(  editer() ) );

   connect( radioHiragana_, SIGNAL( toggled( bool ) ),
            this,           SLOT(   selectHiragana( bool ) ) );
   connect( radioKatakana_, SIGNAL( toggled( bool ) ),
            this,           SLOT(   selectKatakana( bool ) ) );
   connect( radioMot_,      SIGNAL( toggled( bool ) ),
            this,           SLOT(   selectMot( bool ) ) );
   connect( loupeUniquement_, SIGNAL( stateChanged( int ) ),
            this,             SLOT(   selectLoupe( int ) ) );

   connect( radioTotalAlea_,  SIGNAL( toggled( bool ) ),
            this,             SLOT(   selectTotalAlea( bool ) ) );
   connect( radioAleaSansOk_, SIGNAL( toggled( bool ) ),
            this,             SLOT(   selectAleaSansOk( bool ) ) );
   connect( radioALaSuite_,   SIGNAL( toggled( bool ) ),
            this,             SLOT(   selectALaSuite( bool ) ) );

   connect( pushButtonDemarrerLoupe_,    SIGNAL( clicked() ),
            this,                        SLOT(   demarrerLoupe() ) );
   connect( pushButtonArreterLoupe_,     SIGNAL( clicked() ),
            this,                        SLOT(   arreterLoupe() ) );
   connect( pushButtonRemiseAZeroLoupe_, SIGNAL( clicked() ),
            this,                        SLOT(   remiseAZeroLoupe() ) );

   connect( pushButtonEffacer_, SIGNAL( clicked() ),
            this,               SLOT(   effacer() ) );

   connect( textEditEntrRoumaji_, SIGNAL( textChanged() ),
            this,                 SLOT(   textChanged() ) );
   connect( textEditEntrFr_,      SIGNAL( textChanged() ),
            this,                 SLOT(   textChanged() ) );

   connect( filtreEnter_, SIGNAL( enter() ),
            this,         SLOT(   valider() ) );
   connect( filtreEnter_, SIGNAL( up() ),
            this,         SLOT(   reponse() ) );
   connect( filtreEnter_, SIGNAL( down() ),
            this,         SLOT(   nouveau() ) );
   connect( filtreEnter_, SIGNAL( left() ),
            this,         SLOT(   effacer() ) );

   connect( pushButtonValider_, SIGNAL( clicked() ),
            this,               SLOT(   valider() ) );
   connect( pushButtonReponse_, SIGNAL( clicked() ),
            this,               SLOT(   reponse() ) );
   connect( pushButtonNouveau_, SIGNAL( clicked() ),
            this,               SLOT(   nouveau() ) );
/*
   connect( pushButtonAjoutHiragana_, SIGNAL( clicked() ),
            this,                     SLOT(   ajoutHiragana() ) );
   connect( pushButtonAjoutKatakana_, SIGNAL( clicked() ),
            this,                     SLOT(   ajoutKatakana() ) );
   connect( pushButtonAjoutMot_,      SIGNAL( clicked() ),
            this,                     SLOT(   ajoutMot() ) );*/

   connect( arbreGroupe_, SIGNAL( itemChanged( QTreeWidgetItem *, int ) ),
            this,         SLOT(   modifArbre( QTreeWidgetItem *, int ) ) );

   connect( pushButtonAppliquer_, SIGNAL( clicked() ),
            this,                 SLOT(   chargementDico() ) );

   modif_ = false;

   motRecherche_ = FabriqueTextEdit();
   QPushButton * rechercheMot = new QPushButton( tr( "Rechercher un mot" ) );
   gridLayout->addWidget( motRecherche_, 11, 0, 1, 1 );
   gridLayout->addWidget( rechercheMot, 11, 1, 1, 1 );
   connect( rechercheMot, SIGNAL( clicked() ),
            this,         SLOT(   rechercherMot() ) );
}

FenetrePrincipale::~FenetrePrincipale()
{
   sauvegardeFichier();
}

void FenetrePrincipale::chargementFichier()
{
   dictionnaire_->remiseAZero();

   ordreHiragana_.clear();
   mapHiraganaGroupe_.clear();
   mapHiraganaChecked_.clear();

   ordreKatakana_.clear();
   mapKatakanaGroupe_.clear();
   mapKatakanaChecked_.clear();

   ordreMot_.clear();
   mapMotGroupe_.clear();
   mapMotChecked_.clear();

   std::ifstream     file( nomFichier_.c_str() );

   string                       groupe;
   Qt::CheckState               actif;
   vector< Mot >              * vecteurCour;
   vector< string >           * vecteurFr;
   vector< string >::iterator   iteGroupe;

   if ( file )
   {
      string ligne;
      string couple;
      string hiraKata, roumaji, fr, partFr;

      // Hiragana
      groupe         = "Divers";
      actif          = Qt::Checked;
      vecteurCour    = new vector< Mot >;

      getline( file, ligne );

      while ( !file.eof() && ligne != "" )
      {
         getline( file, ligne );

         switch ( ligne[0] )
         {
            case '#' :
               break;
            case '!' :
               iteGroupe = std::find ( ordreHiragana_.begin(), ordreHiragana_.end(), groupe );
               if ( iteGroupe != ordreHiragana_.end() )
               {
                  ordreHiragana_.erase( iteGroupe );
               }

               ordreHiragana_.push_back( groupe );
               mapHiraganaGroupe_[ groupe ]    = *vecteurCour;
               mapHiraganaChecked_[ groupe ]   = actif;

               groupe                  = ligne.substr( 1 );
               actif                   = Qt::Checked;
               vecteurCour             = new vector< Mot >;
               break;
            case '?' :
               if ( ligne[1] == 'x' )
               {
                  actif = Qt::Checked;
               }
               else
               {
                  actif = Qt::Unchecked;
               }
               break;
            default:
               istringstream issLigne(ligne);

               while ( std::getline( issLigne, couple, ';' ) )
               {
                  istringstream issCouple( couple );

                  std::getline( issCouple, hiraKata, ':' );
                  std::getline( issCouple, roumaji, ':' );
                  std::getline( issCouple, fr, ':' );

                  vecteurCour->push_back( Hiragana( hiraKata, roumaji ) );
               }
               break;
         }
      }

      ordreHiragana_.push_back( groupe );
      mapHiraganaGroupe_[ groupe ]    = *vecteurCour;
      mapHiraganaChecked_[ groupe ]   = actif;


      // Katakana
      getline( file, ligne );

      groupe         = "Divers";
      actif          = Qt::Checked;
      vecteurCour    = new vector< Mot >;

      while ( !file.eof() && ligne != "" )
      {
         getline( file, ligne );

         switch ( ligne[0] )
         {
            case '#' :
               break;
            case '!' :
               iteGroupe = std::find ( ordreKatakana_.begin(), ordreKatakana_.end(), groupe );
               if ( iteGroupe != ordreKatakana_.end() )
               {
                  ordreKatakana_.erase( iteGroupe );
               }

               ordreKatakana_.push_back( groupe );
               mapKatakanaGroupe_[ groupe ]    = *vecteurCour;
               mapKatakanaChecked_[ groupe ]   = actif;

               groupe                  = ligne.substr( 1 );
               actif                   = Qt::Checked;
               vecteurCour             = new vector< Mot >;
               break;
            case '?' :
               if ( ligne[1] == 'x' )
               {
                  actif = Qt::Checked;
               }
               else
               {
                  actif = Qt::Unchecked;
               }
               break;
            default:
               istringstream issLigne(ligne);

               while ( std::getline( issLigne, couple, ';' ) )
               {
                  istringstream issCouple( couple );

                  std::getline( issCouple, hiraKata, ':' );
                  std::getline( issCouple, roumaji, ':' );
                  std::getline( issCouple, fr, ':' );

                  vecteurCour->push_back( Katakana( hiraKata, roumaji ) );
               }
               break;
         }
      }

      ordreKatakana_.push_back( groupe );
      mapKatakanaGroupe_[ groupe ]    = *vecteurCour;
      mapKatakanaChecked_[ groupe ]   = actif;


      // Mot

      groupe         = "Divers";
      actif          = Qt::Checked;
      vecteurCour    = new vector< Mot >;

      getline( file, ligne );

      while ( !file.eof() && ligne != "" )
      {
         getline( file, ligne );

         switch ( ligne[0] )
         {
            case '#' :
               break;
            case '!' :
               iteGroupe = std::find ( ordreMot_.begin(), ordreMot_.end(), groupe );
               if ( iteGroupe != ordreMot_.end() )
               {
                  ordreMot_.erase( iteGroupe );
               }

               ordreMot_.push_back( groupe );
               mapMotGroupe_[ groupe ]    = *vecteurCour;
               mapMotChecked_[ groupe ]   = actif;

               groupe                  = ligne.substr( 1 );
               actif                   = Qt::Checked;
               vecteurCour             = new vector< Mot >;
               break;
            case '?' :
               if ( ligne[1] == 'x' )
               {
                  actif = Qt::Checked;
               }
               else
               {
                  actif = Qt::Unchecked;
               }
               break;
            default:
               istringstream issLigne(ligne);

               while ( std::getline( issLigne, couple, ';' ) )
               {
                  istringstream issCouple( couple );

                  std::getline( issCouple, hiraKata, ':' );
                  std::getline( issCouple, roumaji, ':' );
                  std::getline( issCouple, fr, ':' );

                  istringstream issFr( fr );
                  vecteurFr = new vector< string >;

                  while ( std::getline( issFr, partFr, ',' ) )
                  {
                     vecteurFr->push_back( myTrim( partFr ) );
                  }

                  sort ( vecteurFr->begin(), vecteurFr->end() ); 
                  vecteurCour->push_back( Mot( hiraKata, roumaji, vecteurFr ) );
               }
               break;
         }
      }

      ordreMot_.push_back( groupe );
      mapMotGroupe_[ groupe ]    = *vecteurCour;
      mapMotChecked_[ groupe ]   = actif;
   }

   chargementArbre();
}

void FenetrePrincipale::sauvegardeFichier()
{
   vector< string >::iterator iteOrdre;
   vector< Mot >::iterator    iteVecteur;

   string                                 sep;

   std::ofstream                          file( ( nomFichier_ ).c_str() );

   if ( file )
   {
      //file << *dictionnaire_ << std::endl;
      
      file << "	Hiragana" << std::endl;

      for ( iteOrdre = ordreHiragana_.begin(); iteOrdre != ordreHiragana_.end(); ++iteOrdre )
      {
         if ( mapHiraganaGroupe_[ *iteOrdre ].size() != 0 )
         {
            file << "!" << *iteOrdre << std::endl;
            file << "?" << ( mapHiraganaChecked_[ *iteOrdre ] == Qt::Checked ? "x" : "o" ) << std::endl;

            sep = "";

            for ( iteVecteur = mapHiraganaGroupe_[ *iteOrdre ].begin(); iteVecteur != mapHiraganaGroupe_[ *iteOrdre ].end(); ++iteVecteur )
            {
               file << sep << (*iteVecteur).getHiraKata() << ":" << (*iteVecteur).getRoumaji();
               sep = ";";
            }

            file << std::endl;
         }
      }


      file << "\n	Katakana" << std::endl;

      for ( iteOrdre = ordreKatakana_.begin(); iteOrdre != ordreKatakana_.end(); ++iteOrdre )
      {
         if ( mapKatakanaGroupe_[ *iteOrdre ].size() != 0 )
         {
            file << "!" << *iteOrdre << std::endl;
            file << "?" << ( mapKatakanaChecked_[ *iteOrdre ] == Qt::Checked ? "x" : "o" ) << std::endl;

            sep = "";

            for ( iteVecteur = mapKatakanaGroupe_[ *iteOrdre ].begin(); iteVecteur != mapKatakanaGroupe_[ *iteOrdre ].end(); ++iteVecteur )
            {
               file << sep << (*iteVecteur).getHiraKata() << ":" << (*iteVecteur).getRoumaji();
               sep = ";";
            }

            file << std::endl;
         }
      }


      file << "\n	Mot\n#" << std::endl;

      for ( iteOrdre = ordreMot_.begin(); iteOrdre != ordreMot_.end(); ++iteOrdre )
      {
         if ( mapMotGroupe_[ *iteOrdre ].size() != 0 )
         {
            file << "#\n!" << *iteOrdre << std::endl;
            file << "?" << ( mapMotChecked_[ *iteOrdre ] == Qt::Checked ? "x" : "o" ) << std::endl;

            for ( iteVecteur = mapMotGroupe_[ *iteOrdre ].begin(); iteVecteur != mapMotGroupe_[ *iteOrdre ].end(); ++iteVecteur )
            {
               file << iteVecteur->toString() << std::endl;
            }
         }
      }
   }

}

void FenetrePrincipale::chargementArbre()
{
   vector< string >                        * ptOrdre;
   map< string, vector< Mot > >            * ptMapGroupe;
   map< string, Qt::CheckState >           * ptMapChecked;
   
   vector< string >::iterator                it;

   modif_ = true;

   arbreGroupe_->clear();

   switch ( modeMot_ )
   {
      case ModeMot::Hiragana :
         ptOrdre        = &ordreHiragana_;
         ptMapGroupe    = &mapHiraganaGroupe_;
         ptMapChecked   = &mapHiraganaChecked_;
         break;
      case ModeMot::Katakana :
         ptOrdre        = &ordreKatakana_;
         ptMapGroupe    = &mapKatakanaGroupe_;
         ptMapChecked   = &mapKatakanaChecked_;
         break;
      case ModeMot::Mot :
         ptOrdre        = &ordreMot_;
         ptMapGroupe    = &mapMotGroupe_;
         ptMapChecked   = &mapMotChecked_;
         break;
   }

   for ( it = ptOrdre->begin(); it != ptOrdre->end(); it++ )
   {
      if ( ( *ptMapGroupe )[ *it ].size() != 0 )
      {
         QTreeWidgetItem   * groupeItem   = new QTreeWidgetItem( arbreGroupe_ );

         groupeItem->setText( 0, QString::fromUtf8( (*it).c_str() ) );
         groupeItem->setCheckState( 0, ( *ptMapChecked )[ (*it) ] );
      }
   }

   modif_ = false;

   chargementDico();
}

void FenetrePrincipale::chargementDico()
{
   vector< string >               * ptOrdre;
   map< string, vector< Mot > >   * ptMapGroupe;
   map< string, Qt::CheckState >  * ptMapChecked;
   void           ( Dictionnaire::* ptFctAjout )( Mot & );

   vector< string >::iterator          itOrdre;

   vector< Mot >                  * ptVecteur;
   vector< Mot >::iterator          itVecteur;

   switch ( modeMot_ )
   {
      case ModeMot::Hiragana :
         ptOrdre        = &ordreHiragana_;
         ptMapGroupe    = &mapHiraganaGroupe_;
         ptMapChecked   = &mapHiraganaChecked_;
         ptFctAjout     = &Dictionnaire::ajouterHiragana;
         break;
      case ModeMot::Katakana :
         ptOrdre        = &ordreKatakana_;
         ptMapGroupe    = &mapKatakanaGroupe_;
         ptMapChecked   = &mapKatakanaChecked_;
         ptFctAjout     = &Dictionnaire::ajouterKatakana;
         break;
      case ModeMot::Mot :
         ptOrdre        = &ordreMot_;
         ptMapGroupe    = &mapMotGroupe_;
         ptMapChecked   = &mapMotChecked_;
         ptFctAjout     = &Dictionnaire::ajouterMot;
         break;
   }

   dictionnaire_->remiseAZero();

   for ( itOrdre = ptOrdre->begin(); itOrdre != ptOrdre->end(); ++itOrdre )
   {
      if ( (*ptMapChecked)[ *itOrdre ] == Qt::Checked )
      {
         ptVecteur = &( ( *ptMapGroupe)[ *itOrdre ] );

         for ( itVecteur = ptVecteur->begin(); itVecteur != ptVecteur->end(); ++itVecteur )
         {
            ( dictionnaire_->*ptFctAjout )( *itVecteur );
         }
      }
   }

   nouveau( false, true );
}

void FenetrePrincipale::editer()
{
   QDesktopServices::openUrl( QUrl( nomFichier_.c_str() ) );
}

void FenetrePrincipale::selectHiragana( bool inChecked )
{
   if ( inChecked )
   {
      modeMot_ = ModeMot::Hiragana;
      labelEntrFr_->hide();
      textEditEntrFr_->hide();
      chargementArbre();
   }
}

void FenetrePrincipale::selectKatakana( bool inChecked )
{
   if ( inChecked )
   {
      modeMot_ = ModeMot::Katakana;
      labelEntrFr_->hide();
      textEditEntrFr_->hide();
      chargementArbre();
   }
}

void FenetrePrincipale::selectMot( bool inChecked )
{
   if ( inChecked )
   {
      modeMot_ = ModeMot::Mot;
      labelEntrFr_->show();
      textEditEntrFr_->show();
      chargementArbre();
   }
}

void FenetrePrincipale::selectLoupe( int inNouvelEtat )
{
   modeloupe_ = ModeLoupe::Enum( inNouvelEtat );
   chargementArbre();
   // if ( inChecked )
   // {
      // choixI_ = 3;
      // labelEntrFr_->show();
      // textEditEntrFr_->show();
      // chargementArbre();
   // }
}

void FenetrePrincipale::selectTotalAlea( bool inChecked )
{
   if ( inChecked )
   {
      choixII_ = 0;
      nouveau( false, true );
   }
}

void FenetrePrincipale::selectAleaSansOk( bool inChecked )
{
   if ( inChecked )
   {
      choixII_ = 1;
      nouveau( false, true );
   }
}

void FenetrePrincipale::selectALaSuite( bool inChecked )
{
   if ( inChecked )
   {
      choixII_ = 2;
      nouveau( false, true );
   }
}

void FenetrePrincipale::demarrerLoupe()
{
   enregistrLoupe_ = true;

   pushButtonArreterLoupe_->show();
   pushButtonDemarrerLoupe_->hide();
}

void FenetrePrincipale::arreterLoupe()
{
   enregistrLoupe_ = false;

   pushButtonDemarrerLoupe_->show();
   pushButtonArreterLoupe_->hide();
}

void FenetrePrincipale::remiseAZeroLoupe()
{
   dictionnaire_->remiseAZeroLoupe();
}

void FenetrePrincipale::effacer()
{
   textEditEntrRoumaji_->clear();
   textEditEntrRoumaji_->setFontPointSize( 16 );
   textEditEntrFr_->clear();
   textEditEntrFr_->setFontPointSize( 16 );
   textEditEntrRoumaji_->setFocus( Qt::OtherFocusReason );
}

void FenetrePrincipale::textChanged()
{
   if ( messagePresent_ )
   {
      labelResultat_->setText( "" );
      messagePresent_ = false;
   }
}

void FenetrePrincipale::valider()
{
   string            saisieRoumaji = "";
   string            saisieFr      = "";

   vector< string >  vecteurFr;

   QTextDocument   * doc;

   string            sep;

   int               code;


   doc = textEditEntrRoumaji_->document();
   sep = "";

   for ( QTextBlock it = doc->begin(); it != doc->end(); it = it.next() )
   {
      saisieRoumaji += sep + it.text().toStdString();
      sep = "\n";
   }

   if ( modeMot_ == ModeMot::Mot )
   {
      doc = textEditEntrFr_->document();
      sep = "";

      for ( QTextBlock it = doc->begin(); it != doc->end(); it = it.next() )
      {
         saisieFr += sep + QString( it.text().toUtf8() ).toStdString();
         sep = "\n";
      }

      string         partFr;
      istringstream  issFr( saisieFr );

      while ( std::getline( issFr, partFr, ',' ) )
      {
         vecteurFr.push_back( myTrim( partFr ) );
      }

      sort ( vecteurFr.begin(), vecteurFr.end() );

      textEditEntrFr_->clear();
      textEditEntrFr_->setFontPointSize( 16 );
   }

   code = 0;

   if ( saisieRoumaji == motCourant_->getRoumaji() )
   {
      if ( modeMot_ == ModeMot::Mot )
      {
         if ( motCourant_->verifFr( vecteurFr ) )
         {
            code = 1;
         }
         else
         {
            code = dictionnaire_->existMulti( vecteurFr );
         }
      }
      else
      {
         code = 1;
      }
   }

   switch ( code )
   {
      case 0 :
         labelResultat_->setText( "Mauvaise réponse." );
         dictionnaire_->loupe( modeMot_, enregistrLoupe_, nbAjout_->value() );
         premierCoup_ = false;

         if (!afficherRomaji_->isChecked())
         {
            textEditEntrRoumaji_->clear();
            textEditEntrRoumaji_->setFocus( Qt::OtherFocusReason );
         }
         break;
      case 1 :
         labelResultat_->setText( "Ok !" );
         nouveau( premierCoup_ );

         // textEditEntrRoumaji_->clear();
         // textEditEntrRoumaji_->setFontPointSize( 16 );
         // textEditEntrRoumaji_->setFocus( Qt::OtherFocusReason );
         break;
      case 2 :
         labelResultat_->setText( "Un autre mot !" );

         textEditEntrFr_->setFocus( Qt::OtherFocusReason );
         break;
   }/*

   if ( saisieRoumaji == motCourant_->getRoumaji() && 
        ( saisieFr == motCourant_->getFr() ||                              // Bon
        ( choixI_ > 1 && dictionnaire_->existMulti( saisieFr ) == 1 ) ) )  // Homonyme
   {
      labelResultat_->setText( "Ok !" );
      nouveau( premierCoup_ );
      textEditEntrRoumaji_->setFocus( Qt::OtherFocusReason );
   }
   else
   {
      labelResultat_->setText( "Mauvaise réponse." );
      dictionnaire_->loupe( enregistrLoupe_ );
      premierCoup_ = false;
   }*/

   messagePresent_ = true;
}

void FenetrePrincipale::reponse()
{
   dictionnaire_->loupe( modeMot_, enregistrLoupe_, nbAjout_->value() );
   premierCoup_ = false;

   textEditEntrRoumaji_->setPlainText( QString::fromUtf8( motCourant_->getRoumaji().c_str() ) );
   textEditEntrFr_->setPlainText( QString::fromUtf8( motCourant_->getStringFr().c_str() ) );
}

void FenetrePrincipale::nouveau( const bool inOk, const bool inInit )
{
   if ( !inInit && !inOk )
   {
      dictionnaire_->loupe( modeMot_, enregistrLoupe_, nbAjout_->value() );
   }

   motCourant_ = dictionnaire_->nouveauMot( modeMot_, modeloupe_, choixII_, inOk );
   premierCoup_   = true;

   textEditEntrHiraKata_->clear();
   textEditEntrRoumaji_->clear();
   textEditEntrRoumaji_->setFontPointSize( 16 );
   textEditEntrFr_->clear();
   textEditEntrFr_->setFontPointSize( 16 );

   textEditEntrHiraKata_->setPlainText( QString::fromUtf8( motCourant_->getHiraKata().c_str() ) );
   textEditEntrRoumaji_->setFocus( Qt::OtherFocusReason );
   if (afficherRomaji_->isChecked())
   {
      textEditEntrRoumaji_->setPlainText( QString::fromUtf8( motCourant_->getRoumaji().c_str() ) );
      textEditEntrFr_->setFocus( Qt::OtherFocusReason );
   }

}/*

void FenetrePrincipale::ajoutHiragana()
{}

void FenetrePrincipale::ajoutKatakana()
{}

void FenetrePrincipale::ajoutMot()
{}

void FenetrePrincipale::ajout( const int inCode )
{
   string jap  = "";
   string fr   = "";
   QTextDocument * docJap  = textEditAjoutJap_->document();
   QTextDocument * docFr   = textEditAjoutFr_->document();

   string sep;

   sep = "";

   for ( QTextBlock it = docJap->begin(); it != docJap->end(); it = it.next() )
   {
      jap += sep + it.text().toStdString();
      sep = "\n";
   }

   sep = "";

   for ( QTextBlock it = docFr->begin(); it != docFr->end(); it = it.next() )
   {
      fr += sep + it.text().toStdString();
      sep = "\n";
   }

   // Ici traitement !

   textEditAjoutJap_->clear();
   textEditAjoutFr_->clear();
}*/

void FenetrePrincipale::modifArbre( QTreeWidgetItem * inItem, int inCol )
{
   map< string, Qt::CheckState >  * ptMapChecked;

   switch ( modeMot_ )
   {
      case 0 :
         ptMapChecked   = &mapHiraganaChecked_;
         break;
      case 1 :
         ptMapChecked   = &mapKatakanaChecked_;
         break;
      case 2 :
         ptMapChecked   = &mapMotChecked_;
         break;
   }
   if ( !modif_ )
   {
      ( *ptMapChecked )[ QString( inItem->text( 0 ).toUtf8() ).toStdString() ] = inItem->checkState( 0 );
   }
}

string FenetrePrincipale::myTrim( string & inStr )
{
   for ( string::iterator it = inStr.begin(); it < inStr.end() && (*it) == ' '; ++it )
   {
      inStr.erase ( it );
   }

   return inStr;
}

#include <rechercheMotGUI/chercheurMotWidget.hpp>

void FenetrePrincipale::rechercherMot()
{
   ChercheurMotWidget chercheurMotWidget( ChercheurMot::Chercher( motRecherche_->toPlainText().toStdString() ) );
   
   if ( chercheurMotWidget.exec() == QDialog::Accepted )
   {
      //emit nouveauManga( choixManga.recupMangaOnline() );
   }
}
