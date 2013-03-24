
#ifndef RECHERCHE_MOT_GUI_CHERCHER_MOT_WIDGET_ENTRAINEMENT_JAP
#define RECHERCHE_MOT_GUI_CHERCHER_MOT_WIDGET_ENTRAINEMENT_JAP

#include <mot.h>

#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QStandardItemModel>
#include <QtGui/QTreeView>

#include <string>
#include <vector>

class ChercheurMotWidget : public QDialog
{
   Q_OBJECT

   public :
      ChercheurMotWidget( const std::vector< Mot > & inMots, QWidget * inParent = NULL );
      ~ChercheurMotWidget() {}

   public slots :
      void doubleClicked( const QModelIndex & index );

   private :
      QStandardItemModel * model_;

      QTreeView * createTree( const std::vector< Mot > & inMots );
      // QDialogButtonBox * createButtons();
};

#endif // RECHERCHE_MOT_GUI_CHERCHER_MOT_WIDGET_ENTRAINEMENT_JAP
