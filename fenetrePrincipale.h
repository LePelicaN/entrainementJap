#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QTextBlock>
#include <QLabel>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QDesktopServices>
#include <QUrl>
#include <QCheckBox>
#include <QShortcut>
#include <QKeySequence>
#include <QStandardItemModel>
#include <QtGui/QSpinBox>
#include <QTreeView>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

#include "dictionnaire.h"
#include "filtreEnter.h"

using std::string;
using std::map;
using std::vector;
using std::istringstream;
using namespace std;

class FenetrePrincipale : public QWidget
{
   Q_OBJECT

public :

protected:
   Dictionnaire   * dictionnaire_;
   Mot            * motCourant_;

   string           nomFichier_;

   bool             messagePresent_;
   bool             premierCoup_;

   //int              choixI_;
   ModeMot::Enum modeMot_;
   ModeLoupe::Enum modeloupe_;
   int              choixII_;

   bool             enregistrLoupe_;

   FiltreEnter    * filtreEnter_;

   vector< string >              ordreHiragana_;
   map< string, vector< Mot > >  mapHiraganaGroupe_;
   map< string, Qt::CheckState > mapHiraganaChecked_;

   vector< string >              ordreKatakana_;
   map< string, vector< Mot > >  mapKatakanaGroupe_;
   map< string, Qt::CheckState > mapKatakanaChecked_;

   vector< string >              ordreMot_;
   map< string, vector< Mot > >  mapMotGroupe_;
   map< string, Qt::CheckState > mapMotChecked_;


   QPushButton    * pushButtonRecharger_;
   QPushButton    * pushButtonEditer_;

   QGroupBox      * groupBoxRadioBI_;
   QHBoxLayout    * hBoxLayoutRadioI_;

   QRadioButton   * radioHiragana_;
   QRadioButton   * radioKatakana_;
   QRadioButton   * radioMot_;
   QCheckBox * loupeUniquement_;

   QGroupBox      * groupBoxRadioBII_;
   QHBoxLayout    * hBoxLayoutRadioII_;

   QRadioButton   * radioTotalAlea_;
   QRadioButton   * radioAleaSansOk_;
   QRadioButton   * radioALaSuite_;

   QLabel * labelNbAjout_;
   QSpinBox * nbAjout_;

   QPushButton    * pushButtonDemarrerLoupe_;
   QPushButton    * pushButtonArreterLoupe_;
   QPushButton    * pushButtonRemiseAZeroLoupe_;

   QPushButton    * pushButtonEffacer_;

   QLabel         * labelEntrHiraKata_;
   QLabel         * labelEntrRoumaji_;
   QLabel         * labelEntrFr_;

   QTextEdit      * textEditEntrHiraKata_;
   QTextEdit      * textEditEntrRoumaji_;
   QTextEdit      * textEditEntrFr_;

   QLabel         * labelResultat_;

   QPushButton    * pushButtonValider_;
   QPushButton    * pushButtonReponse_;
   QPushButton    * pushButtonNouveau_;

   QCheckBox * afficherRomaji_;
/*
   QTextEdit      * textEditAjoutJap_;
   QTextEdit      * textEditAjoutFr_;

   QPushButton    * pushButtonAjoutHiragana_;
   QPushButton    * pushButtonAjoutKatakana_;
   QPushButton    * pushButtonAjoutMot_;
*/

//   QStandardItemModel   * modelGroupe_;
   QTreeWidget    * arbreGroupe_;

   QPushButton    * pushButtonAppliquer_;

   bool             modif_;

   QTextEdit * motRecherche_;
   
   void ajout( const int inCode );

   string myTrim( string & inStr );

public:
   FenetrePrincipale( const string inFileName, QWidget * parent = 0 );
   virtual ~FenetrePrincipale();

   void sauvegardeFichier();

public slots:
   void chargementFichier();
   void chargementArbre();
   void chargementDico();
   void editer();

   void selectHiragana( bool inChecked );
   void selectKatakana( bool inChecked );
   void selectMot(      bool inChecked );
   void selectLoupe( int inNouvelEtat );

   void selectTotalAlea( bool inChecked );
   void selectAleaSansOk( bool inChecked );
   void selectALaSuite( bool inChecked );

   void demarrerLoupe();
   void arreterLoupe();
   void remiseAZeroLoupe();

   void effacer();

   void textChanged();

   void valider();
   void reponse();
   void nouveau( const bool inOk = false, const bool inInit = false );
/*
   void ajoutHiragana();
   void ajoutKatakana();
   void ajoutMot();
*/

   void modifArbre( QTreeWidgetItem * inItem, int inCol );
   
   void rechercherMot();
};

#endif
