
#ifndef RECHERCHE_MOT_GUI_CHERCHER_MOT_WIDGET_ENTRAINEMENT_JAP
#define RECHERCHE_MOT_GUI_CHERCHER_MOT_WIDGET_ENTRAINEMENT_JAP

#include <mot.h>

#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QTreeView>

#include <string>
#include <vector>

class ChercheurMotWidget : public QDialog
{
   public :
      ChercheurMotWidget( const std::vector< Mot > & inMots, QWidget * inParent = NULL );

   private :
      QTreeView * createTree( const std::vector< Mot > & inMots );
      // QDialogButtonBox * createButtons();
};

#endif // RECHERCHE_MOT_GUI_CHERCHER_MOT_WIDGET_ENTRAINEMENT_JAP
