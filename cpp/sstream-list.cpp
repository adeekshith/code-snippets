// Compiled and executed successfully
// http://www.dreamincode.net/forums/topic/95826-stringstream-tutorial/
#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <cctype>

using namespace std;

int main() {
  stringstream ss;
  std::list<std::string> datalog_list;
  ss << "Deekshith " << 21 << " coding";
  datalog_list.push_back(ss.str());
  ss.str("");
  ss << "Chris "<<"is "<<"coming";
  datalog_list.push_back(ss.str());
  for(std::list<std::string>::iterator list_iter = datalog_list.begin(); list_iter != datalog_list.end(); list_iter++)
	{
	    std::cout<<*list_iter<<std::endl;
	}
  //cout << ss2.str()<<endl;

}

