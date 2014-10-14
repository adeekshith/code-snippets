#include <string>
#include <iostream>
#include <sstream>
using namespace std;

int main(){
	string Text = "456";//string containing the number
	int Result;//number which will contain the result

	stringstream convert(Text); // stringstream used for the conversion initialized with the contents of Text

	if ( !(convert >> Result) )//give the value to Result using the characters in the string
	    Result = 0;//if that fails set Result to 0
	//Result now equal to 456 
	cout<<Result+2<<Text<<endl;
}