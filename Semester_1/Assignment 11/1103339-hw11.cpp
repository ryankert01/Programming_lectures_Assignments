#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;
using std::setfill;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios;

#include <vector>
using std::vector;


struct Date
{
   int year = 0;
   int month = 0;
   int day = 0;
};

struct AvailTable
{
   Date date;
   int numAvailTables[ 4 ][ 6 ] = {}; // the number of available tables,
};  // numAvailTables[ 1 ][ i ] is the number of available type i tables on 11:30
    // numAvailTables[ 2 ][ i ] is the number of available type i tables on 14:30
    // numAvailTables[ 3 ][ i ] is the number of available type i tables on 17:30

struct Reservation
{
   int numCustomers = 0;              // number of customers
   Date date;                         // reservation date
   int time = 0;                      // reservation time code
   char name[ 8 ] = "";               // name
   char mobileNumber[ 12 ] = "";      // mobile phone number
   char email[ 40 ] = "";             // email address
   char password[ 12 ] = "";          // reservation password
   char reservationNumber[ 12 ] = ""; // reservation number
};

// tableTypes[ i ] is the table type for i customers
const int tableTypes[ 13 ] = { 0, 1, 1, 2, 2, 3, 4, 4, 0, 0, 5, 5, 5 };

const int TOTAL_NUM_TABLES = 2; // suppose there are totally 2 tables for all types

// return current date
Date computeCurrentDate();

// return true if and only if year is a leap year
inline bool leapYear( int year );

// input an integer in the range [ begin, end ]
int inputAnInteger( int begin, int end );

// return true if and only if date1 == date2
bool equal( Date date1, Date date2 );

// return true if and only if date1 < date2
bool less( Date date1, Date date2 );

// return true if and only if date1 <= date2
bool lessEqual( Date date1, Date date2 );

// return date + numDays
Date add( Date date, int numDays );

// delete out of date data in availTables, and append new data from rear of availTables
void initAvailTables( vector< AvailTable > &availTables, Date currentDate );

// read available table informations after currentDate, from the file AvailTables.dat
void loadAvailTables( vector< AvailTable > &availTables, Date currentDate );

// read reservation informations after or equal to currentDate, from the file Reservations.dat
void loadReservations( vector< Reservation > &reservations, Date currentDate );

// make reservation
void makeReservation( vector< Reservation > &reservations, vector< AvailTable > &availTables, Date currentDate );

// choose a date and a time
void chooseDateTime( vector< AvailTable > &availTables, Reservation &reservation, Date currentDate, int tableType );

// display dates on which there are tables available
void displayAvailDates( vector< AvailTable > &availTables, bool available[], int tableType );

// return true if there are available tables on availTables[ i ].date for corresponding table type
bool availableTables( vector< AvailTable > &availTables, size_t i, int tableType );

// --availTables[ i ].numAvailTables[ timeCode ][ tableType ], where availTables[ i ].date == date
void decreaseAvailTables( vector< AvailTable > &availTables, Date date, int timeCode, int tableType );

// use reservationNumber to make a reservation inquiry, and let user choose whether to cancel it
void reservationInquiry( vector< Reservation > &reservations, vector< AvailTable > &availTables );

// display all fields of reservation which includes
// mobileNumber, name, date, time, email, numCustomers, password and reservationNumber
void displayReservationInfo( const Reservation &reservation );

// display reservations[ i ], where
// reservations[ i ].reservationNumber is equal to the specified reservationNumber
void displayReservationInfo( const vector< Reservation > &reservations, char reservationNumber[] );

// erase reservations[ position ]
void erase( vector< Reservation > &reservations, int position );

// write availTables into the file AvailTables.dat
void saveAvailTables( const vector< AvailTable > &availTables );

// write reservations into the file Reservations.dat
void saveReservations( const vector< Reservation > &reservations );

int main()
{
   cout << "Welcome to Hi-Lai Harbour Taoyuan Location!\n";

   srand( static_cast< unsigned int >( time( 0 ) ) );
   Date currentDate = computeCurrentDate();

   vector< AvailTable > availTables; // vector of all available table informations
   initAvailTables( availTables, currentDate );

   vector< Reservation > reservations; // vector of all available table informations
   loadReservations( reservations, currentDate );

   bool userExited = false; // user has not chosen to exit

   // loop while user has not chosen option to exit system
   while( !userExited )
   {
      // show main menu and get user selection
      cout << "\n1 - Book a Table\n";
      cout << "2 - My Bookings\n";
      cout << "3 - End\n\n";

      int mainMenuSelection;
      do cout << "Enter your choice: (1~3): ";
      while( ( mainMenuSelection = inputAnInteger( 1, 3 ) ) == -1 );

      // decide how to proceed based on user's menu selection
      switch( mainMenuSelection )
      {
      case 1:
         makeReservation( reservations, availTables, currentDate ); // make reservation
         break;
      case 2:
         reservationInquiry( reservations, availTables ); // reservation inquiry
         break;
      case 3: // user chose to terminate session
         saveAvailTables( availTables );
         saveReservations( reservations );
         userExited = true; // this session should end
         cout << endl;
         break;
      default: // user did not enter an integer from 1-3
         cout << "\nIncorrect choice!" << endl;
      }
   }

   system( "pause" );
}

Date computeCurrentDate()//comfirmed
{
   Date temp;
   int second = static_cast<int>(time(0)) + 8 * 60 * 60;
   int year = 1970;
   int year_second = 365 * 24 * 60 * 60;
   if(leapYear(year)){
      year_second += 24 * 60 * 60;
   }

   //year
   while(second >= year_second){
      second -= year_second;
      year++;
      year_second = 365 * 24 * 60 * 60;
      if(leapYear(year)){
         year_second += 24 * 60 * 60;
      }
   }

   //month
   int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
   if(leapYear(year)){
      days[2] = 29;
   }
   int month = 1;
   while(second >= days[month] * 24 * 60 * 60){
      second -= days[month] * 24 * 60 * 60;
      month++;
   }

   //day
   int day = second / (24 * 60 * 60) + 1;

   //return temp
   temp.year = year;
   temp.month = month;
   temp.day = day;

   //alternative: use struct tm_
   // tm structTime;
   // time_t time1 = time(0);
   // localtime_s(&structTime, &time1);

   // temp.year = structTime.tm_year + 1900;
   // temp.month = structTime.tm_mon + 1;
   // temp.day = structTime.tm_mday;

   //test
   //temp.year = 2021;
   //temp.month = 12;
   //temp.day = 14;

   return temp;
}

inline bool leapYear( int year )
{
   return ( year % 400 == 0 || ( year % 4 == 0 && year % 100 != 0 ) );
}

int inputAnInteger( int begin, int end )
{
   char string[ 80 ];
   cin.getline( string, 80, '\n' );

   if( strlen( string ) == 0 )
      exit( 0 );

   for( unsigned int i = 0; i < strlen( string ); i++ )
      if( string[ i ] < '0' || string[ i ] > '9' )
         return -1;

   int number = atoi( string );

   if( number >= begin && number <= end )
      return number;
   else
      return -1;
}

bool equal( Date date1, Date date2 )
{
   return ( date1.year == date2.year &&
            date1.month == date2.month &&
            date1.day == date2.day );
}

bool less( Date date1, Date date2 )
{
   if( date1.year < date2.year )
      return true;
   if( date1.year > date2.year )
      return false;

   if( date1.month < date2.month )
      return true;
   if( date1.month > date2.month )
      return false;

   if( date1.day < date2.day )
      return true;

   return false;
}

bool lessEqual( Date date1, Date date2 )
{
   return less( date1, date2 ) || equal( date1, date2 );
}

Date add( Date date, int numDays )//comfirmed
{
   int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
   int day = date.day + numDays;
   int month = date.month;
   int year = date.year;

   month--;
   for(int i = 1; i <= month; i++){
      day += days[i];
   }
   //cout << "day: " << day << endl;//test

   int year_days = 365;
   if(leapYear(year)){
      year_days = 366;
   }
   while(day > year_days){
       day -= year_days;
       year++;

       year_days = 365;
       if(leapYear(year)){
           year_days = 366;
        }
   }
   month = 1;
   while(day > days[month]){
       month++;
       day -= days[month];
   }
   Date temp;
   temp.day = day;
   temp.month = month;
   temp.year = year;
   return temp;
}

void initAvailTables( vector< AvailTable > &availTables, Date currentDate )
{
   loadAvailTables( availTables, currentDate );

   while(availTables.size() > 30){
      availTables.pop_back();
   }
   

   //add if availTables is less than 30
   AvailTable temp;
   for(int i = 1; i < 4; i++){
      for(int j = 1; j < 6; j++){
         temp.numAvailTables[i][j] = 2;
      }
   }

   for(int i = availTables.size(); i < 30; i++){
      temp.date = add(currentDate, i + 1);
      availTables.push_back(temp);
   }
   // while(availTables.size() < 30){
   //    temp.date = add(availTables[availTables.size() - 1].date, 1);
   //    availTables.push_back(temp);
   // }
}

void loadAvailTables( vector< AvailTable > &availTables, Date currentDate )
{
   ifstream inFile1("AvailTables1.dat", ios::binary);
   ifstream inFile2("AvailTables2.dat", ios::binary);
   ifstream inFile4("AvailTables4.dat", ios::binary);

   if(!inFile1){
      cout << "AvailTables1.dat could not be opend.\n";
      exit(1);
   }
   if(!inFile2){
      cout << "AvailTables2.dat could not be opend.\n";
      exit(1); 
   }
   if(!inFile4){
      cout << "AvailTables4.dat could not be opend.\n";
      exit(1);
   }

   //read File2 and file4, then replace same date data from file1.
   AvailTable temp;
   while(inFile2.read(reinterpret_cast<char*>(&temp), sizeof(temp))){
      if(less(currentDate, temp.date)){
         availTables.push_back(temp);
      }
   }
   while(inFile4.read(reinterpret_cast<char*>(&temp), sizeof(temp))){
      if(less(currentDate, temp.date)){
         availTables.push_back(temp);
      }
   }
   while(inFile1.read(reinterpret_cast<char*>(&temp), sizeof(temp))){
      for(int i = 0; i < availTables.size(); i++){
         if(equal(availTables[i].date, temp.date)){
            availTables[i] = temp;
         }
      }
   }
   inFile1.close();
   inFile2.close();
   inFile4.close();
}

void loadReservations( vector< Reservation > &reservations, Date currentDate )
{
   ifstream inFile("Reservations.dat", ios::binary);
   if(!inFile){
      cout << "Reservations.dat could not be opened.\n";
      exit(1);
   }
   Reservation temp;

   while(inFile.read(reinterpret_cast<char*>(&temp), sizeof(temp))){
      if(lessEqual(currentDate, temp.date)){
         reservations.push_back(temp);
      }
   }

   inFile.close();
}

void makeReservation( vector< Reservation > &reservations, vector< AvailTable > &availTables, Date currentDate )
{
   Reservation newReservation;

   do {
      cout << "\nEnter the number of customers (1 - 7, 10 - 12): ";
      newReservation.numCustomers = inputAnInteger( 1, 12 );
   } while( newReservation.numCustomers == 8 ||
            newReservation.numCustomers == 9 ||
            newReservation.numCustomers == -1 );

   int tableType = tableTypes[ newReservation.numCustomers ];

   chooseDateTime( availTables, newReservation, currentDate, tableType );

   cout << "\nEnter name: ";
   cin >> newReservation.name;

   cout << "\nEnter mobile number: ";
   cin >> newReservation.mobileNumber;

   cout << "\nEnter email address: ";
   cin >> newReservation.email;

   cout << "\nEnter reservation password: ";
   cin >> newReservation.password;
   cin.ignore();

   newReservation.reservationNumber[ 0 ] = 1 + rand() % 9 + '0';
   for( int i = 1; i < 8; i++ )
      newReservation.reservationNumber[ i ] = rand() % 10 + '0';

   cout << setfill( ' ' ) << endl << setw( 11 ) << "Mobile No." << setw( 10 ) << "Name"
        << setw( 14 ) << "Date" << setw( 9 ) << "Time" << setw( 30 ) << "Email"
        << setw( 19 ) << "No of Customers" << setw( 12 ) << "Password"
        << setw( 19 ) << "Reservation No." << endl;

   displayReservationInfo( newReservation );

   cout << "\nReservation Completed!\n";

   reservations.push_back( newReservation );

   decreaseAvailTables( availTables, newReservation.date, newReservation.time, tableType );
}

// choose a date and a time
void chooseDateTime( vector< AvailTable > &availTables, Reservation &reservation, Date currentDate, int tableType )
{
   cout << "\nChoose a date\n";
   bool availableDate[30];
   // for (size_t i = 0; i < availTables.size(); i++){
   //    availableDate[i] = availableTables(availTables, i, tableType);
   // }
   displayAvailDates(availTables, availableDate, tableType);

   int num = 0;
   do{
      cout <<"\n?";
      num = inputAnInteger(1, 30);
   }while(num == -1);

   reservation.date = availTables[num - 1].date;
   
   cout << "\n\nChoose a time:\n";
   if(availTables[num - 1].numAvailTables[1][tableType] > 0){
      cout << "1. 11:30\n";
   }
   if(availTables[num - 1].numAvailTables[2][tableType] > 0){
      cout << "2. 14:30\n";
   }
   if(availTables[num - 1].numAvailTables[3][tableType] > 0){
      cout << "3. 17:30\n";
   }

   int numT = 0;
   do{
      cout <<"?";
      numT = inputAnInteger(1, 3);
   }while(numT == -1);
   reservation.time = numT;
   cout << endl;

}

void displayAvailDates( vector< AvailTable > &availTables, bool availableDate[], int tableType )
{
   int count = 0;
   int fit = 0;
   for(size_t i = 0; i < availTables.size(); i++){
      availableDate[i] = availableTables(availTables, i, tableType);
      count++;
      if(availableDate[i]){
         fit++;
         cout << setfill(' ') << setw(2) << count << ". ";
         cout << availTables[i].date.year << "/";
         if(availTables[i].date.month < 10){
            cout << 0;
         }
         cout << availTables[i].date.month << "/";
         if(availTables[i].date.day < 10){
            cout << 0;
         }
         cout << availTables[i].date.day << "  ";
         if(fit % 4 == 0){
            cout << endl;
         }
      }
   }
}

// returns true if there are available tables on availTables[ i ].date for corresponding table type
bool availableTables( vector< AvailTable > &availTables, size_t i, int tableType )
{
   if(availTables[i].numAvailTables[1][tableType] > 0 ||
      availTables[i].numAvailTables[2][tableType] > 0 ||
      availTables[i].numAvailTables[3][tableType] > 0){
      return 1;
   }
   else{
      return 0;
   }

}

// --availTables[ i ].numAvailTables[ timeCode ][ tableType ], where availTables[ i ].date == date
void decreaseAvailTables( vector< AvailTable > &availTables, Date date, int timeCode, int tableType )
{
   for (int i = 0; i < availTables.size(); i++){
      if(equal(availTables[ i ].date, date)){
         --availTables[ i ].numAvailTables[ timeCode ][ tableType ];
      }
   }

}

void reservationInquiry( vector< Reservation > &reservations, vector< AvailTable > &availTables )
{
   if( reservations.size() == 0 )
   {
      cout << "\nNo reservations!\n";
      return;
   }

   //cout << reservations[0].reservationNumber <<endl; //test

   cout << "\nEnter reservation number: ";
   char reservationNumber[ 12 ];
   cin >> reservationNumber;
   cin.ignore();

   int check = 0;
   for (int i = 0; i < reservations.size(); i++){
      if(strcmp(reservations[i].reservationNumber, reservationNumber) == 0){
         check = 1;
         char reservationPass[12];
         cout << "Enter your password: ";
         cin >> reservationPass;
         cin.ignore();
         if(strcmp(reservationPass, reservations[i].password) != 0){
            cout << "\n\nThe password is incorrect!\n";
            return;
         }
         cout << setfill( ' ' ) << setw( 11 ) << "Mobile No." << setw( 10 ) << "Name"
         << setw( 14 ) << "Date" << setw( 9 ) << "Time" << setw( 30 ) << "Email"
         << setw( 19 ) << "No of Customers" << setw( 12 ) << "Password"
         << setw( 19 ) << "Reservation No." << endl;
         displayReservationInfo(reservations[i]);

         char dicision;
         do{
            cout << "\nCancel this reservation? (y/n)?";
            cin >> dicision;
            cin.ignore();
         }while(dicision != 'y' && dicision != 'n');

         if(dicision == 'y'){
            for (int j = 0; j < availTables.size(); j++){
               if(equal(availTables[ j ].date, reservations[i].date)){
                  availTables[ j ].numAvailTables[ reservations[i].time ][ tableTypes[reservations[i].numCustomers] ]++;
                  reservations.erase(reservations.begin() + i);
                  break;
               }
            }

            cout << "\nThis reservation has been cancelled.\n";
            return;
         }
         else{
            return;
         }
         
      }
   }
   if(check == 0){
      cout << "\n\nNo reservations with this reservation number!\n";
   }
   
   return;
}

// displays all fields of reservation which includes
// mobileNumber, name, date, time, email, numCustomers, password and reservationNumber
void displayReservationInfo( const Reservation &reservation )
{
   char times[ 4 ][ 8 ] = { "", "11:30", "14:30", "17:30" };
   cout << setfill( ' ' ) << setw( 11 ) << reservation.mobileNumber
      << setw( 10 ) << reservation.name
      << "    " << reservation.date.year << "/" << setfill( '0' )
      << setw( 2 ) << reservation.date.month << '/'
      << setw( 2 ) << reservation.date.day
      << setfill( ' ' ) << setw( 9 ) << times[ reservation.time ]
      << setw( 30 ) << reservation.email
      << setw( 19 ) << reservation.numCustomers
      << setw( 12 ) << reservation.password
      << setw( 19 ) << reservation.reservationNumber << endl;
}

// displays reservations[ i ], where
// reservations[ i ].reservationNumber is equal to the specified reservationNumber
void displayReservationInfo( const vector< Reservation > &reservations, char reservationNumber[] )
{
   cout << setfill( ' ' ) << setw( 11 ) << "Mobile No." << setw( 10 ) << "Name"
      << setw( 14 ) << "Date" << setw( 9 ) << "Time" << setw( 30 ) << "Email"
      << setw( 19 ) << "No of Customers" << setw( 12 ) << "Password"
      << setw( 19 ) << "Reservation No." << endl;

   for( size_t i = 0; i < reservations.size(); ++i )
      if( strcmp( reservations[ i ].reservationNumber, reservationNumber ) == 0 )
         break;

   char times[ 4 ][ 8 ] = { "", "11:30", "14:30", "17:30" };
   int count = 0;
   for( size_t i = 0; i < reservations.size(); ++i )
      if( strcmp( reservations[ i ].reservationNumber, reservationNumber ) == 0 )
         displayReservationInfo( reservations[ i ] );
}


// erase reservations[ position ]
void erase( vector< Reservation > &reservations, int position )
{
   reservations.erase(reservations.begin() + position);

}

void saveAvailTables( const vector< AvailTable > &availTables )
{
   ofstream outFile("AvailTables1.dat", ios::binary);
   if(!outFile){
      cout << "Reservations.dat could not be opened\n";
      exit(1);
   }
   for(int i = 0; i < availTables.size(); i++){
      outFile.write(reinterpret_cast<const char*>(&availTables[i]), sizeof(availTables[i]));
   }
   outFile.close();
}

void saveReservations( const vector< Reservation > &reservations )
{
   ofstream outFile("Reservations.dat", ios::binary);
   if(!outFile){
      cout << "Reservations.dat could not be opened\n";
      exit(1);
   }
   for(int i = 0; i < reservations.size(); i++){
      outFile.write(reinterpret_cast<const char*>(&reservations[i]), sizeof(reservations[i]));
   }
   outFile.close();
}



//notes:
//cin.ignore()
//reinterpret_cast<char*>(&jk)
//strcmp(char1, char2) == 0
//