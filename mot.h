#ifndef MOT_H
#define MOT_H

#include <QtCore/QMetaType>

#include <string>
#include <vector>
#include <utility>

#include <iostream>

using std::string;
using std::vector;
using std::pair;

class Mot
{

protected:
   string            hiraKata_;
   string            roumaji_;
   vector< string >  fr_;

   bool              isHiraKata_;

public:
   Mot(){}
   Mot( const string & inHiraKata, const string & inRoumaji, const vector< string > * inFr = NULL );
   virtual ~Mot();

   const string           & getHiraKata() const { return hiraKata_; }
   const string           & getRoumaji()  const { return roumaji_; }
   const vector< string > & getFr()       const { return fr_; }

   const bool               isHiraKata()  const { return isHiraKata_; }

   string   getStringFr() const;
   std::string toString() const;
   bool     verifFr( vector< string > & inFr );
};

Q_DECLARE_METATYPE(Mot)

#endif
