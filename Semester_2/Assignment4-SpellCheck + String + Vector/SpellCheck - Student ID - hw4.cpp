#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "SpellCheck.h"

SpellCheck::SpellCheck()
   : result()
{
}

void SpellCheck::equalLength( const string &wordToCheck, const vector &dictionary )
{
   size_t length = wordToCheck.size();
   vector words;

   findWords( words, dictionary, length );

   string buffer1;
   string buffer2;
   for( size_t i = 0; i < words.size(); i++ )
      for( size_t j = 0; j < length; j++ )
      {
          buffer1 = wordToCheck;
          buffer2 = words[i];
          buffer1.erase(j, 1);
          buffer2.erase(j, 1);
          if (buffer1 == buffer2) {
              result.push_back(words[i]);
              break;
          }
      }
}

void SpellCheck::shorter( const string &wordToCheck, const vector &dictionary )
{
   size_t length = wordToCheck.size() + 1;
   vector words;

   findWords( words, dictionary, length );

   string buffer;
   for( size_t i = 0; i < words.size(); i++ )
      for( size_t j = 0; j < length; j++ )
      {

          buffer = words[i];
          buffer.erase(j, 1);
          if (buffer == wordToCheck) {
              result.push_back(words[i]);
              break;
          }
         
      }
}

void SpellCheck::longer( const string &wordToCheck, const vector &dictionary )
{
   size_t length = wordToCheck.size() - 1;
   vector words;

   findWords( words, dictionary, length );

   string buffer;
   for( size_t i = 0; i < words.size(); i++ )
      for( size_t j = 0; j < wordToCheck.size(); j++ )
      {
          buffer = wordToCheck;
          buffer.erase(j, 1);
          if (buffer == words[i]) {
              result.push_back(words[i]);
              break;
          }
      }
   //cout << "result: " << result.size() << endl;
}

void SpellCheck::findWords( vector &words, const vector &dictionary, size_t length )
{
   for( size_t i = 0; i < dictionary.size(); i++ )
      if( dictionary[ i ].size() == length )
         words.push_back( dictionary[ i ] );
}

void SpellCheck::output()
{
   cout << "Similar legal words: ";
   cout << result[ 0 ].c_str();
   for( size_t i = 1; i < result.size(); i++ )
      cout << ", " << result[ i ].c_str();
   cout << endl << endl;
}

void SpellCheck::clear()
{
   result.clear();
}