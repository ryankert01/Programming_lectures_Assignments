#include <iostream>
using namespace::std;
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <ctime>

// input all words from the file Dictionary.txt, and put them to the vector "dictionary"
void readDictionary( vector< string > &dictionary );

// return true if and only if wordToCheck == dictionary[ i ] for some i
bool legal( string wordToCheck, vector< string > dictionary );

// Find every word w in the vector "dictionary" which satisfies two conditions:
// 1. the length of w is equal to the length of wordToCheck, and
// 2. wordToCheck and w are different on exactly one character.
// Put these words into the vector "result".
void spellCheck1( string wordToCheck, vector< string > dictionary, vector< string > &result );

// Find every word w in the vector "dictionary" which satisfies two conditions:
// 1. the length of w is one greater than the length of wordToCheck, and
// 2. wordToCheck is equal to the substring obtained by deleting a character from w.
// Put these words into the vector "result".
void spellCheck2( string wordToCheck, vector< string > dictionary, vector< string > &result );

// Find every word w in the vector "dictionary" which satisfies two conditions:
// 1. the length of w is one less than the length of wordToCheck, and
// 2. w is equal to the substring obtained by deleting a character from wordToCheck.
// Put these words into the vector "result".
void spellCheck3( string wordToCheck, vector< string > dictionary, vector< string > &result );

// find the words in the vector "dictionary" whose length is equal to the last parameter "length",
// and puts these words into the vector "words"
void findWords( vector< string > &words, vector< string > dictionary, size_t length );

// output all words in the vector "result" to the file result
void saveWords( vector< string > result );

int main()
{
   srand( 1 );
   vector< string > dictionary;

   readDictionary( dictionary );

   string wordToCheck;
   vector< string > result;
   for( int i = 0; i < 10; i++ )
   {
      wordToCheck = dictionary[ rand() + dictionary.size() - 32768 ]; // skip short words
      wordToCheck.erase( rand() % wordToCheck.size(), 1 );

      if( legal( wordToCheck, dictionary ) )
         cout << wordToCheck << " is a legal english word.\n";
      else
      {
         cout << wordToCheck << endl;
         result.push_back( wordToCheck );

         spellCheck1( wordToCheck, dictionary, result );
         spellCheck2( wordToCheck, dictionary, result );
         spellCheck3( wordToCheck, dictionary, result );
         result.push_back( "" );
      }
   }

   saveWords( result );

   system( "pause" );
}

void readDictionary( vector< string > &dictionary )
{
    ifstream inFile("Dictionary.txt", ios::in);
    if(!inFile)
    {
       cerr << "File could not be opened";
       exit(1);
    }
    string input;
    while(inFile >> input){
       dictionary.push_back(input);
    }
    inFile.close();

}

bool legal( string wordToCheck, vector< string > dictionary )
{
   for( size_t i = 0; i < dictionary.size(); i++ )
      if( dictionary[ i ] == wordToCheck )
         return true;
   return false;
}

void spellCheck1( string wordToCheck, vector< string > dictionary, vector< string > &result )
{
   size_t length = wordToCheck.size();
   vector< string > words;

   findWords( words, dictionary, length );

   string buffer1;
   string buffer2;
   for( size_t i = 0; i < words.size(); i++ )
      for( size_t j = 0; j < length; j++ )
      {
          buffer1 = words[i];
          buffer2 = wordToCheck;

          buffer1[j] = 32;
          buffer2[j] = 32;

          if (buffer1 == buffer2)
          {
              result.push_back(words[i]);
          }

      }
}

void spellCheck2( string wordToCheck, vector< string > dictionary, vector< string > &result )
{
   size_t length = wordToCheck.size() + 1;
   vector< string > words;

   findWords( words, dictionary, length );

   string buffer;
   for( size_t i = 0; i < words.size(); i++ )
      for( size_t j = 0; j < length; j++ )
      {
          buffer = words[i];
          buffer.erase(j, 1);
          if (buffer == wordToCheck)
          {
              result.push_back(words[i]);
          }

      }
}

void spellCheck3( string wordToCheck, vector< string > dictionary, vector< string > &result )
{
   size_t length = wordToCheck.size() - 1;
   vector< string > words;

   findWords( words, dictionary, length );

   string buffer;
   for( size_t i = 0; i < words.size(); i++ )
      for( size_t j = 0; j < wordToCheck.size(); j++ )
      {
          buffer = wordToCheck;
          buffer.erase(j, 1);
          if (buffer == words[i])
          {
              result.push_back(words[i]);
          }

      }
}

void findWords( vector< string > &words, vector< string > dictionary, size_t length )
{
   for( size_t i = 0; i < dictionary.size(); i++ )
      if( dictionary[ i ].size() == length )
         words.push_back( dictionary[ i ] );
}

void saveWords( vector< string > result )
{
    ofstream outFile("Result.txt", ios::out);
    if (!outFile) {
        cerr << "File could not be opened" << endl;
        system("pause");
        exit(1);
    }
    for (int i = 0; i < result.size(); i++)
    {
        outFile << result[i] << endl;
    }
    outFile.close();

}