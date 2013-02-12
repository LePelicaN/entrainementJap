#ifndef FILTREENTER_H
#define FILTREENTER_H

#include <QObject>
#include <QEvent>
#include <QKeyEvent>

class FiltreEnter : public QObject
{
    Q_OBJECT

public:
   FiltreEnter();
   virtual ~FiltreEnter();

protected:
   bool eventFilter( QObject * inObj, QEvent * inEvent );

signals:
   void enter();
   void up();
   void down();
   void left();
   void right();
};

#endif
