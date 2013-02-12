#include "fenetrePrincipale.h"

#include <QApplication>

int main( int argc, char *argv[] ) {

   QApplication app(argc, argv);

   FenetrePrincipale fenetre( argc == 1 ? "listeJap.txt" : argv[1] );

   fenetre.show();

   return app.exec();
}
