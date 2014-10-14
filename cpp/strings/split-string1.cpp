#include <iostream>
#include <string>

int main(){
	std::string s = "10,2014-09-03 16:25:56,32,,7,40.09758659,-88.24529301,3.53553,0,238,off,Pay,,,";
	std::string delimiter = ",";
	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {
	    token = s.substr(0, pos);
	    std::cout << token << std::endl;
	    s.erase(0, pos + delimiter.length());
	}
std::cout << s << std::endl;
}