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
//#include <ctime>

#include <vector>
using std::vector;

struct Date
{
   int year = 0;
   int month = 0;
   int day = 0;
};

struct AvailRoom
{
   Date date;
   int numAvailRooms[ 6 ] = {}; // number of available rooms
   // numAvailRooms[ 0 ]: not used
   // numAvailRooms[ 1 ]: the number of available superior rooms
   // numAvailRooms[ 2 ]: the number of available deluxe rooms
   // numAvailRooms[ 3 ]: the number of available deluxe twin rooms
   // numAvailRooms[ 4 ]: the number of available superior suites
   // numAvailRooms[ 5 ]: the number of available deluxe suites
};

struct Reservation
{
   char id[ 12 ] = "";
   char name[ 12 ] = "";
   char mobile[ 12 ] = "";
   int roomType = 0; // 1: superior rooms, 2: deluxe rooms, 3: deluxe twin rooms,
                     // 4: superior suites, 5: deluxe suites
   int numRooms = 0; // number of rooms reserved
   Date checkInDate;
   Date checkOutDate;
};

const int roomRate[ 6 ] = { 0, 5390, 6270, 6270, 6820, 8470 }; // room rate per night for each room type
const int totalNumRooms[ 6 ] = { 0, 9, 5, 3, 5, 4 }; // total number of rooms for each type
const char roomTypeName[ 6 ][ 20 ] = { "", "Superior Room", "Deluxe Room", "Deluxe Twin Room",
                                           "Superior Suite", "Deluxe Suite" };
// return the current date
Date computeCurrentDate();

// return true if and only if year is a leap year
inline bool leapYear( int year );

// return true if and only if date1 == date2
bool equal( Date date1, Date date2 );

// return true if and only if date1 < date2
bool less( const Date &date1, const Date &date2 );

// return true if and only if date1 <= date2
bool lessEqual( Date date1, Date date2 );

// read reservations information whose checkInDate are after or equal to currentDate,
// from the file Reservations.dat
void loadReservations( vector< Reservation > &reservations, const Date &currentDate );

// load all available rooms information after or equal to currentDate,
// from the file Available Rooms.dat
void loadAvailRooms( vector< AvailRoom > &availRooms, const Date &currentDate );

// create available rooms information for 6 months, starting from currentDate
// provided that availRooms.size() == 0
void initAvailRooms( vector< AvailRoom > &availRooms, const Date &currentDate );

// append new available rooms information, provided that availRooms.size() != 0
void completeAvailRooms( vector< AvailRoom > &availRooms, const Date &currentDate );

// input an integer in the range [ begin, end ]
int inputAnInteger( int begin, int end );

void makeReservation( vector< AvailRoom > &availRooms, vector< Reservation > &reservations, const Date &currentDate );

// input check in date and check out date by user, and
// put them into reservation.checkInDate and reservation.checkOutDate, respectively.
void inputDates( const Date &currentDate, Reservation &newReservation );

// return the minimum between availRooms[ first .. last ].numAvailRooms[ roomType ],
// where availRooms[ first ].date == reservation.checkInDate and
// availRooms[ last ].date == reservation.checkOutDate.
int compMinNumRooms( const Reservation &reservation, vector< AvailRoom > &availRooms, int roomType );

void displayAvailRooms( const AvailRoom &availableRoom );

void displayReservations( const Reservation &reservation );

// return the number of nights for reservation
int numNights( Reservation reservation );

void reservationInquiry( const vector< Reservation > &reservations, const Date &currentDate );

bool exist( const vector< Reservation > &reservations, const Date &currentDate, char id[] );

// save all available rooms information into the file Available Rooms.dat
void saveAvailRooms( const vector< AvailRoom > &availRooms );

// save all reservations information into the file Reservations.dat
void saveReservations( const vector< Reservation > &reservations );

int main()
{
   cout << "Evergreen Laurel Hotel Online Reservation System\n";

   srand( static_cast< unsigned int >( time( 0 ) ) );
   Date currentDate = computeCurrentDate();

   vector< Reservation > reservations;
   loadReservations( reservations, currentDate ); // load all reservation informations

   vector< AvailRoom > availRooms;
   loadAvailRooms( availRooms, currentDate ); // load all available rooms information

//   for( size_t i = 0; i < availRooms.size(); i++ )
//      displayAvailRooms( availRooms[ i ] );

   if( availRooms.size() == 0 )
      initAvailRooms( availRooms, currentDate ); // create available rooms information for 6 months
   else
      completeAvailRooms( availRooms, currentDate ); // append new available rooms information

   bool userExited = false; // user has not chosen to exit

   // loop while user has not chosen option to exit system
   while( !userExited )
   {
      // show main menu and get user selection
      cout << "\n1 - Making Reservation\n";
      cout << "2 - Reservation Inquiry\n";
      cout << "3 - End\n\n";

      int mainMenuSelection;
      do cout << "Enter your choice: (1~3): ";
      while( ( mainMenuSelection = inputAnInteger( 1, 3 ) ) == -1 );

      Date temp;
      // decide how to proceed based on user's menu selection
      switch( mainMenuSelection )
      {
      case 1:
         makeReservation( availRooms, reservations, currentDate ); // make reservation
         break;

      case 2:
         reservationInquiry( reservations, currentDate ); // reservation inquiry
         break;

      case 3: // user chose to terminate session
         saveAvailRooms( availRooms );
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

Date computeCurrentDate()
{
   tm structuredTime;
   time_t rawTime = time( 0 );
   localtime_s( &structuredTime, &rawTime );

   Date currentDate;
   currentDate.year = structuredTime.tm_year + 1900;
   currentDate.month = structuredTime.tm_mon + 1;
   currentDate.day = structuredTime.tm_mday;

   return currentDate;
}

inline bool leapYear( int year )
{
   return ( year % 400 == 0 || ( year % 4 == 0 && year % 100 != 0 ) );
}

bool equal( Date date1, Date date2 )
{
   return ( date1.year == date2.year &&
      date1.month == date2.month &&
      date1.day == date2.day );
}

bool less( const Date &date1, const Date &date2 )
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
   else
      return false;
}

bool lessEqual( Date date1, Date date2 )
{
   return less( date1, date2 ) || equal( date1, date2 );
}

void loadReservations( vector< Reservation > &reservations, const Date &currentDate )
{
	ifstream inFile("Reservations.dat", ios::binary);
	if (!inFile) { cout << "File could not be opened.1\n"; exit(1); }
	Reservation temp;
	while (inFile.read(reinterpret_cast<char*>(&temp), sizeof(temp))) {
		if (lessEqual(currentDate, temp.checkInDate)) {
			reservations.push_back(temp);
		}
	}
	inFile.close();


}

void loadAvailRooms( vector< AvailRoom > &availRooms, const Date &currentDate )
{
	ifstream inFile("Available Rooms.dat", ios::binary);
	if (!inFile) { cout << "File could not be opened.2\n"; exit(1); }
	AvailRoom temp;
	while (inFile.read(reinterpret_cast<char*>(&temp), sizeof(temp))) {
		if (lessEqual(currentDate, temp.date)) {
			availRooms.push_back(temp);
		}
	}
	inFile.close();


}

void initAvailRooms( vector< AvailRoom > &availRooms, const Date &currentDate )
{
   // number of days in each month
   int days[ 13 ] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
   if (leapYear(currentDate.year)) {
	   days[2] = 29;
   }

   AvailRoom temp;
   for (int i = 0; i < 6; i++) {
	   temp.numAvailRooms[i] = totalNumRooms[i];
   }

   Date aimDate;
   aimDate = currentDate;
   aimDate.month += 5;
   int initialmo = 0;

   if (availRooms.size() < 1) {
	   initialmo = 1;
   }
   else {
	   initialmo = availRooms[availRooms.size() - 1].date.month + 1;
   }

   for (int i = initialmo; i < currentDate.month + 6; i++) {
	   temp.date.year = currentDate.year;
	   temp.date.month = i;
	   for (int j = 1; j <= days[i]; j++) {
		   temp.date.day = j;
		   if (lessEqual(currentDate, temp.date)) {
			   availRooms.push_back(temp);
			   //cout << temp.date.year << " " << temp.date.month << " " << temp.date.day << endl;
		   }

	   }
   }



}

void completeAvailRooms( vector< AvailRoom > &availRooms, const Date &currentDate )
{
   // number of days in each month
	int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (leapYear(currentDate.year)) {
		days[2] = 29;
	}

	AvailRoom temp;
	for (int i = 0; i < 6; i++) {
		temp.numAvailRooms[i] = totalNumRooms[i];
	}

	Date aimDate;
	aimDate = currentDate;
	aimDate.month += 5;
	int initialmo = 0;

	if (availRooms.size() < 1) {
		initialmo = 1;
	}
	else {
		initialmo = availRooms[availRooms.size() - 1].date.month + 1;
	}

	for (int i = initialmo; i < currentDate.month + 6; i++) {
		temp.date.year = currentDate.year;
		temp.date.month = i;
		for (int j = 1; j <= days[i]; j++) {
			temp.date.day = j;
			if (less(currentDate, temp.date)) {
				availRooms.push_back(temp);
				//cout << temp.date.year << " " << temp.date.month << " " << temp.date.day << endl;
			}
		}
	}
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

void makeReservation(vector< AvailRoom >& availRooms, vector< Reservation >& reservations, const Date& currentDate)
{
	Reservation newReservation;

	// input check in date and check out date by user, and
	// put them into reservation.checkInDate and reservation.checkOutDate, respectively.
	inputDates(currentDate, newReservation);

	cout << "\nCheck in date: " << newReservation.checkInDate.year << '-'
		<< setw(2) << setfill('0') << newReservation.checkInDate.month << '-'
		<< setw(2) << newReservation.checkInDate.day << endl;

	cout << "Check out date: " << newReservation.checkOutDate.year << '-'
		<< setw(2) << newReservation.checkOutDate.month << '-'
		<< setw(2) << newReservation.checkOutDate.day << endl;


	//display roomavilble or return
	if (compMinNumRooms(newReservation, availRooms, 1) > 0 ||
		compMinNumRooms(newReservation, availRooms, 2) > 0 ||
		compMinNumRooms(newReservation, availRooms, 3) > 0 ||
		compMinNumRooms(newReservation, availRooms, 4) > 0 ||
		compMinNumRooms(newReservation, availRooms, 5) > 0) {
		cout << "\nThe number of available rooms of each room type:\n";
		cout << "\n      Date   Superior Room   Deluxe Room   Deluxe Twin Room   Superior Suite   Deluxe Suite\n";
		for (int i = 0; i < availRooms.size(); i++) {
			if (equal(newReservation.checkOutDate, availRooms[i].date)) {
				break;
			}
			if (lessEqual(newReservation.checkInDate, availRooms[i].date)) {
				displayAvailRooms(availRooms[i]);
			}
		}

	}
	else {
		cout << "\nThere are no rooms available!\n";
		return;
	}

	// input room type and put it into newReservation.roomType


	int roomtype;
	do {
		cout << "\nSelect Room Type:";

		if (compMinNumRooms(newReservation, availRooms, 1) > 0) {
			cout << "\n1. Superior Room";
		}
		if (compMinNumRooms(newReservation, availRooms, 2) > 0) {
			cout << "\n2. Deluxe Room";
		}
		if (compMinNumRooms(newReservation, availRooms, 3) > 0) {
			cout << "\n3. Deluxe Twin Room";
		}
		if (compMinNumRooms(newReservation, availRooms, 4) > 0) {
			cout << "\n4. Superior Suite";
		}
		if (compMinNumRooms(newReservation, availRooms, 5) > 0) {
			cout << "\n5. Deluxe Suite";
		}
		cout << "\n6. Give up";
		cout << "\n?";
		roomtype = inputAnInteger(1, 6);
	} while (roomtype == -1 ||
		(compMinNumRooms(newReservation, availRooms, 1) == 0 && roomtype == 1) ||
		(compMinNumRooms(newReservation, availRooms, 2) == 0 && roomtype == 2) ||
		(compMinNumRooms(newReservation, availRooms, 3) == 0 && roomtype == 3) ||
		(compMinNumRooms(newReservation, availRooms, 4) == 0 && roomtype == 4) ||
		(compMinNumRooms(newReservation, availRooms, 5) == 0 && roomtype == 5));
	if (roomtype == 6) {
		return;
	}
	newReservation.roomType = roomtype;

	// input number of rooms and put it into newReservation.numRooms
	int numofroom = 0;
	int maxnumroom = compMinNumRooms(newReservation, availRooms, newReservation.roomType);
	do {
		cout << "\nNumber of rooms ( " << maxnumroom << " rooms available ): ";
		numofroom = inputAnInteger(1, maxnumroom);
	} while (numofroom == -1);

	newReservation.numRooms = numofroom;


	cout << "\nID Number:";
	cin >> newReservation.id;
	cout << "\nName:";
	cin >> newReservation.name;
	cout << "\nMobile Phone:";
	cin >> newReservation.mobile;
	cin.ignore();

	cout << "\nYour reservations:\n\n";
	cout << "    Name   Fare       Mobile          Room type"
		<< "   Number of rooms   Check in date   Check out date\n";
	displayReservations(newReservation);

	reservations.push_back(newReservation);

	for (int i = 0; i < availRooms.size(); i++) {
		if (equal(availRooms[i].date, newReservation.checkInDate)) {
			for (int j = 0; j < numNights(newReservation); j++) {
				availRooms[i + j].numAvailRooms[newReservation.roomType] -= newReservation.numRooms;
			}
			break;
		}
	}
}

void inputDates( const Date &currentDate, Reservation &newReservation )
{
	int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (leapYear(currentDate.year)) {
		days[2] = 29;
	}
	cout << "\nPlease Input Check In Date\n";
	cout << "\nMonth:";
	for (int i = 1; i <= 6; i++) {
		cout << endl << i << ". " << currentDate.year << "-" << setw(2) << setfill('0') << currentDate.month + i - 1;
	}
	int month;
	do {
		cout << "\n?";
		month = inputAnInteger(1, 6);
	} while (month == -1);

	int rand11 = 0;
	int day = 0;
	int rand12 = 0;
	do {
		cout << "\nDay (";
		if (currentDate.month == month) {
			cout << currentDate.day;
			rand11 = currentDate.day;
		}
		else {
			cout << 1;
			rand11 = 1;
		}
		rand12 = days[month];
		if (month == currentDate.month + 5) {
			rand12 = days[month] - 1;
		}
		cout << " ~ " << rand12 << "):";
		day = inputAnInteger(rand11, rand12);
	} while (day == -1);

	newReservation.checkInDate.year = currentDate.year;
	newReservation.checkInDate.month = month;
	newReservation.checkInDate.day = day;

	cout << "\nPlease Input Check Out Date\n";
	cout << "\nMonth:";
	for (int i = 1; i <= 6; i++) {
		if (i >= newReservation.checkInDate.month) {
			if (i > newReservation.checkInDate.month || newReservation.checkInDate.day < days[newReservation.checkInDate.month]) //added
				cout << endl << i << ". " << currentDate.year << "-" << setw(2) << setfill('0') << currentDate.month + i - 1;
		}  
	}
	do {
		cout << "\n?";
		month = inputAnInteger(newReservation.checkInDate.month, 6);
	} while (month == -1);

	do {
		cout << "\nDay (";
		if (newReservation.checkInDate.month == month) {
			cout << newReservation.checkInDate.day + 1;
			rand11 = newReservation.checkInDate.day + 1;
		}
		else {
			cout << 1;
			rand11 = 1;
		}
		cout << " ~ " << days[month] << "):";
		day = inputAnInteger(rand11, days[month]);
	} while (day == -1);
	newReservation.checkOutDate.year = currentDate.year;
	newReservation.checkOutDate.month = month;
	newReservation.checkOutDate.day = day;
}

int compMinNumRooms( const Reservation &reservation, vector< AvailRoom > &availRooms, int roomType )
{
	//reservation.checkInDate
	//reservation.checkOutDate
	//find first and last in availRooms
	int first = 0;
	int last = 0;
	for (int i = 0; i < availRooms.size(); i++) {
		if (equal(reservation.checkInDate, availRooms[i].date)) {
			first = i;
		}
		if (equal(reservation.checkOutDate, availRooms[i].date)) {
			last = i;
		}
	}

	int minNum = totalNumRooms[roomType];
	for (int i = first; i < last; i++) {
		if (availRooms[i].numAvailRooms[roomType] <= minNum) {
			minNum = availRooms[i].numAvailRooms[roomType];
		}
	}

	return minNum;
}

void displayAvailRooms( const AvailRoom &availableRoom )
{
   cout << availableRoom.date.year << "-"
        << setw( 2 ) << setfill( '0' ) << availableRoom.date.month << "-"
        << setw( 2 ) << availableRoom.date.day
        << setw( 16 ) << setfill( ' ' ) << availableRoom.numAvailRooms[ 1 ]
        << setw( 14 ) << availableRoom.numAvailRooms[ 2 ]
        << setw( 19 ) << availableRoom.numAvailRooms[ 3 ]
        << setw( 17 ) << availableRoom.numAvailRooms[ 4 ]
        << setw( 15 ) << availableRoom.numAvailRooms[ 5 ] << endl;
}

void displayReservations( const Reservation &reservation )
{
   cout << setw( 8 ) << setfill( ' ' ) << reservation.name
        << setw( 7 ) << reservation.numRooms * roomRate[ reservation.roomType ] * numNights( reservation )
        << setw( 13 ) << reservation.mobile
        << setw( 19 ) << roomTypeName[ reservation.roomType ]
        << setw( 18 ) << reservation.numRooms
        << setw( 10 ) << reservation.checkInDate.year << "-"
        << setw( 2 ) << setfill( '0' ) << reservation.checkInDate.month << "-"
        << setw( 2 ) << reservation.checkInDate.day
        << setw( 11 ) << setfill( ' ' ) << reservation.checkOutDate.year << "-"
        << setw( 2 ) << setfill( '0' ) << reservation.checkOutDate.month << "-"
        << setw( 2 ) << reservation.checkOutDate.day << endl;
}

int numNights( Reservation reservation )
{
   tm time1 = { 0, 0, 8, 0, 0, 0, 0, 0, 0 };
   tm time2 = { 0, 0, 8, 0, 0, 0, 0, 0, 0 };
   time1.tm_year = reservation.checkInDate.year - 1900;
   time1.tm_mon = reservation.checkInDate.month - 1;
   time1.tm_mday = reservation.checkInDate.day;
   time2.tm_year = reservation.checkOutDate.year - 1900;
   time2.tm_mon = reservation.checkOutDate.month - 1;
   time2.tm_mday = reservation.checkOutDate.day;
   int numSeconds = static_cast< int >( mktime( &time2 ) - mktime( &time1 ) );
   return numSeconds / ( 24 * 3600 );
}

void reservationInquiry( const vector< Reservation > &reservations, const Date &currentDate )
{
   cout << "\nEnter Your ID Number¡G";
   char id[ 12 ];
   cin >> id;
   cin.ignore();

   if( !exist( reservations, currentDate, id ) )
   {
      cout << "\nSorry! You do not have reservations!\n";
      return;
   }

   cout << "\n    Name   Fare       Mobile          Room type"
        << "   Number of rooms   Check in date   Check out date\n";
   for( size_t i = 0; i < reservations.size(); i++ )
      if( strcmp( reservations[ i ].id, id ) == 0 )
         displayReservations( reservations[ i ] );
}

bool exist( const vector< Reservation > &reservations, const Date &currentDate, char id[] )
{
   for( size_t i = 0; i < reservations.size(); i++ )
      if( strcmp( reservations[ i ].id, id ) == 0 &&
          lessEqual( currentDate, reservations[ i ].checkInDate ) )
          return true;

   return false;
}

void saveAvailRooms( const vector< AvailRoom > &availRooms )
{
	ofstream outFile("Available Rooms.dat", ios::binary);
	if (!outFile) { cout << "File could not be opened.\n"; exit(1); }
	for (size_t i = 0; i < availRooms.size(); i++) {
		outFile.write(reinterpret_cast<const char*>(&availRooms[i]), sizeof(availRooms[i]));
	}
	outFile.close();

}

void saveReservations( const vector< Reservation > &reservations )
{
	ofstream outFile("Reservations.dat", ios::binary);
	if (!outFile) { cout << "File could not be opened.\n"; exit(1); }
	for (size_t i = 0; i < reservations.size(); i++) {
		outFile.write(reinterpret_cast<const char*>(&reservations[i]), sizeof(reservations[i]));
	}
	outFile.close();


}