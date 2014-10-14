#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main(){
	std::string delimiter = ",";
	size_t pos = 0;
	std::string token;

	ifstream file("devicelog2.csv"); // pass file name as argment
	std::string linebuffer;
	std::string latitude;
	std::string longitude;
	std::string thisDate;
	std::string thisTime;
	while (file && getline(file, linebuffer)){
		int substr_num=0;
		if (linebuffer.length() == 0)continue;

		while ((pos = linebuffer.find(delimiter)) != std::string::npos) {
			substr_num+=1;
		    token = linebuffer.substr(0, pos);
		    std::cout << token << std::endl;
		    linebuffer.erase(0, pos + delimiter.length());
		}
		//std::cout << linebuffer << std::endl;
		// do something

	}
	return 0;
}