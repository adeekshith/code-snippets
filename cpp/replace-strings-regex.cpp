#include <iostream>
#include <iterator>
#include <regex>
#include <string>
 
int main()
{
   std::string text = "I was, happy?";
   std::regex vowel_re("[,*\?<>@&\"]");
   //std::regex vowel_re("was");
 
   // write the results to an output iterator
   /*
   std::regex_replace(std::ostreambuf_iterator<char>(std::cout),
                      text.begin(), text.end(), vowel_re, "*");
   */
   std::string replaced_result;
   // construct a string holding the results
   replaced_result = std::regex_replace(text, vowel_re, "");
   //replaced_result = std::regex_replace(text, vowel_re, "am");
   std::cout << replaced_result<<std::endl;
}