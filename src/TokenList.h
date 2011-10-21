#ifndef __TokenList_h__
#define __TokenList_h__

#include "Token.h"
#include <list>
using namespace std;

class TokenListIterator {
private:
  list<Token*>::iterator it, begin, end;
  
public:
  TokenListIterator(list<Token*>::iterator begin,
                    list<Token*>::iterator end);
  void toEnd ();
  Token* previous ();
  Token* next ();
  Token* peek ();
  Token* current ();
  bool hasNext ();
  bool hasPrevious ();
};

class TokenList {
private:
  list<Token*> tokens;
  
public:
  virtual ~TokenList();
  
  void push (Token* token);
  Token* pop ();

  void unshift (Token* token);
  Token* shift ();

  bool empty ();
  int size();

  bool equals(TokenList* list);

  Token* back();
  Token* front();
  Token* at(unsigned int i);

  TokenListIterator* iterator();
  TokenListIterator* reverseIterator ();

  void push(TokenList* list);
  void unshift(TokenList* list);

  /**
   * Delete all tokens in the list and remove them from the list.
   */
  void clear();

  TokenList* clone();
  
  string* toString();
};

#endif
