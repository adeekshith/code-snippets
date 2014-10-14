/*
	Current Time, date, weekday, etc
*/
#include <ctime>
#include <iostream>
using namespace std;

int main() {
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    cout << (now->tm_year + 1900) << '-' 
         << (now->tm_mon + 1) << '-'
         <<  now->tm_mday
         << endl;
}

/*
	Members of tm:
	tm_sec	
	tm_min	
	tm_hour	
	tm_mday	
	tm_mon	
	tm_year	
	tm_wday	
	tm_yday	
	tm_isdst

	Example: These can be accessed by using now->tm_sec
*/