#include "filtreEnter.h"

FiltreEnter::FiltreEnter()
{
}

FiltreEnter::~FiltreEnter()
{
}
   
bool FiltreEnter::eventFilter( QObject * inObj, QEvent * inEvent )
{
   if ( inEvent->type() == QEvent::KeyPress )
   {
      QKeyEvent * keyEvent = static_cast<QKeyEvent *>( inEvent );
      if ( keyEvent->key() == Qt::Key_Return )
      {
         emit enter();
         return true;
      }
      if ( keyEvent->key() == Qt::Key_Up )
      {
         emit up();
         return true;
      }
      if ( keyEvent->key() == Qt::Key_Down )
      {
         emit down();
         return true;
      }
      if ( keyEvent->key() == Qt::Key_Left )
      {
         emit left();
         return true;
      }
      if ( keyEvent->key() == Qt::Key_Right )
      {
         emit right();
         return true;
      }
   }
   
   return QObject::eventFilter( inObj, inEvent );
}
