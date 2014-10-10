/*
	C++ Program to find week day of a given date.
*/
#include <iostream>

int dayofweek(int d, int m, int y)
{
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    y -= m < 3;
    return ( y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}
/*
// This works well too but the above one looks simple
// #include <ctime>
int dayofweek2(std::tm this_time){
	this_time.tm_year=this_time.tm_year-1900;
	this_time.tm_mon=this_time.tm_mon-1;
	this_time.tm_mday=this_time.tm_mday;
	mktime(&this_time);
	return int(this_time.tm_wday);
}
*/

/* Driver function to test above function */
int main()
{
    int day = dayofweek(12, 10, 2014); 
    // Above statement finds the week day for 10/23/2013
    //dayofweek(<day in month>,<month>,<year>)
    std::cout << day;
 
    return 0;
}