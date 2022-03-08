#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

#include <cstring>
#include <ctime>

#include "SpellCheck.h"

// input all words from the file Dictionary.txt, and put them to the vector "dictionary"
void readDictionary( vector &dictionary );

// return true if and only if wordToCheck == dictionary[ i ] for some i
bool legal( string wordToCheck, vector dictionary );

void displayString(string thing);

int main()
{
   srand( static_cast< int >( time( 0 ) ) );
   vector dictionary;

   readDictionary( dictionary );

   string wordToCheck;
   SpellCheck spellCheck;
   for( int i = 0; i < 20; i++ )
   {
      wordToCheck = dictionary[ rand() + dictionary.size() - 32768 ]; // skip short words
      wordToCheck.erase( rand() % wordToCheck.size(), 1 );

      if( !legal( wordToCheck, dictionary ) )
      {
         cout << "Word to check: " << wordToCheck.c_str() << endl;

         spellCheck.equalLength( wordToCheck, dictionary );
         spellCheck.shorter( wordToCheck, dictionary );
         spellCheck.longer( wordToCheck, dictionary );

         spellCheck.output();
         spellCheck.clear();
      }
   }/**/

   system( "pause" );
}

void readDictionary( vector &dictionary )
{
    ifstream inFile("Dictionary.txt", ios::in);

    if (!inFile) {
        cout << "Not be able to read File...\n";
        exit(1);
    }

    size_t Dsize = 0;
    char dd;
    

    while (!inFile.eof()) {
        string input;
        while (inFile.read(reinterpret_cast<char*>(&dd), sizeof(char))) {
            if (dd == '\n') break;
            input.push_back(dd);
        }
        dictionary.push_back(input);
    }
/*
   for (size_t i = 0; i < dictionary.size(); i++) {
        displayString(dictionary[i]);
        cout << endl;
    } */
    

    inFile.close();
}

bool legal( string wordToCheck, vector dictionary )
{
   for( size_t i = 0; i < dictionary.size(); i++ )
      if( dictionary[ i ] == wordToCheck )
         return true;
   return false;
}

void displayString(string thing) {
    for (size_t i = 0; i < thing.size(); i++) {
        cout << thing[i];
    }
}