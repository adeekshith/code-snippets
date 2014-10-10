// NOt working
// http://www.mochima.com/tutorials/strings.html
#include <sstream>
#include <iostream>
    // ...
 
ostringstream person_info;
 
person_info << "Name: " << lastname << ", " << firstname << ". ";
person_info << "Birthdate: " << year << '–' << month << '–' << day << ", "<< "Age: " << current_year – year;
 
    //  At this point, person_info.str() provides the result.
    //  You could do, for instance:
 
cout << "Person info:\n" << person_info.str() << endl;