#ifndef SPELL_CHECK_H
#define SPELL_CHECK_H

#include "vector.h"

class SpellCheck
{
public:
   // empty object constructor (default constructor)
   SpellCheck();

   // Find every word w in the vector "dictionary" which satisfies two conditions:
   // 1. the length of w is equal to the length of wordToCheck, and
   // 2. wordToCheck and w are different on exactly one character.
   // Put these words into the vector "result".
   void equalLength( const string &wordToCheck, const vector &dictionary );

   // Find every word w in the vector "dictionary" which satisfies two conditions:
   // 1. the length of w is one greater than the length of wordToCheck, and
   // 2. wordToCheck is equal to the substring obtained by deleting a character from w.
   // Put these words into the vector "result".
   void shorter( const string &wordToCheck, const vector &dictionary );

   // Find every word w in the vector "dictionary" which satisfies two conditions:
   // 1. the length of w is one less than the length of wordToCheck, and
   // 2. w is equal to the substring obtained by deleting a character from wordToCheck.
   // Put these words into the vector "result".
   void longer( const string &wordToCheck, const vector &dictionary );

   // Find the words in the vector "dictionary" whose length is equal to "length",
   // and put these words into the vector "words"
   void findWords( vector &words, const vector &dictionary, size_t length );

   void output();

   void clear();

private:
   vector result;
};

#endif 