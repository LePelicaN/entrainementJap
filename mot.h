#ifndef MOT_H
#define MOT_H

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
   Mot( const string & inHiraKata, const string & inRoumaji, const vector< string > * inFr = NULL );
   virtual ~Mot();

   const string           & getHiraKata() { return hiraKata_; }
   const string           & getRoumaji()  { return roumaji_; }
   const vector< string > & getFr()       { return fr_; }

   const bool               isHiraKata()  { return isHiraKata_; }

   string   getStringFr();
   bool     verifFr( vector< string > & inFr );
};

#endif
