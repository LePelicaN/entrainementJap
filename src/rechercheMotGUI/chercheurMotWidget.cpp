
#include "chercheurMotWidget.hpp"

#include <QtGui/QGridLayout>
#include <QtGui/QStandardItem>

#include <fstream>

namespace
{

std::string motToString( const Mot & inMot )
{
   return inMot.getRoumaji() + " - " + inMot.getStringFr();
}

} // unnamed namespace

QTreeView * ChercheurMotWidget::createTree( const std::vector< Mot > & inMots )
{
   QTreeView * outTreeView = new QTreeView();

   model_ = new QStandardItemModel();
   QStandardItem * racine = model_->invisibleRootItem();

   for ( std::vector< Mot >::const_iterator motCourant = inMots.begin();
         motCourant != inMots.end();
         ++motCourant )
   {
      std::string motString = motToString( *motCourant );
      QStandardItem * mot = new QStandardItem( motString.c_str() );
      mot->setEditable( false );
      mot->setData( QVariant::fromValue( *motCourant ) );
      racine->appendRow( mot );
   }

   outTreeView->setModel( model_ );
   outTreeView->expandAll();
   outTreeView->setHeaderHidden( true );
   outTreeView->setExpandsOnDoubleClick( false );

   connect( outTreeView, SIGNAL( doubleClicked( const QModelIndex & ) ),
            this,        SLOT(   doubleClicked( const QModelIndex & ) ) );

   return outTreeView;
}

// QDialogButtonBox * ChercheurMotWidget::createButtons()
// {
   // QDialogButtonBox * outButtonBox = new QDialogButtonBox();

   // outButtonBox->addButton( QDialogButtonBox::Ok );
   // outButtonBox->addButton( QDialogButtonBox::Cancel );
   // // ok_ = outButtonBox->button( QDialogButtonBox::Ok );
   // // ok_->setEnabled( true );

   // return outButtonBox;
// }

ChercheurMotWidget::ChercheurMotWidget( const std::vector< Mot > & inMots, QWidget * inParent )
   : QDialog( inParent )
{
   QGridLayout * mainLayout = new QGridLayout();
   int ligne = 0;
   mainLayout->addWidget( createTree( inMots ), ligne++, 0 );
   //mainLayout->addWidget( createButtons(), ligne++, 0 );
   setLayout( mainLayout );
}

void ChercheurMotWidget::doubleClicked( const QModelIndex & index )
{
   QStandardItem * item = model_->itemFromIndex( index );
   Mot mot = item->data().value<Mot>(); ;
   std::ofstream oFile( "nouveauxMots.txt", std::ios_base::app );
   oFile << mot.toString() << std::endl;
   accept();
}
