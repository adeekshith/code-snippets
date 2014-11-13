/**
 * Splits a string with a given delimiter
 * NOTE: The delimiter should also be a string
 * Author : Deekshith Allamaneni
 * Website: www.deekshith.in
 */
#include <sstream>
#include <iostream>
#include <vector>
//using namespace std;
std::vector<std::string> splitString(std::string stringToSplit, std::string delimiter){
    //std::string stringToSplit="orange,apple,mango,tomato,banana,pineapple";
    //std::string delimiter = ",";
    size_t pos = 0;
    size_t prev_pos = 0;
    std::vector<std::string> split_vector;
    bool endLoop=false;
    int i=5;
    do{
        //std::cout<<"("<<pos<<" ,";
        pos = stringToSplit.find(delimiter,prev_pos+delimiter.length());
        //std::cout<<pos<<") - ";
        if (pos==std::string::npos){
            split_vector.push_back(stringToSplit.substr(prev_pos+delimiter.length()));
            //std::cout<<stringToSplit.substr(prev_pos+delimiter.length())<<std::endl;
            break;
        }
        std::string token;
        std::string currentSplit;
        if (prev_pos==0)
            token=stringToSplit.substr( prev_pos, pos );
        else
            token=stringToSplit.substr(prev_pos+delimiter.length(),pos-(prev_pos+delimiter.length()) );
        std::stringstream convert(token);
        if ( !(convert >> currentSplit) )
            endLoop=true;
        split_vector.push_back(currentSplit);
        prev_pos = pos;
        //std::cout<<currentSplit<<std::endl;
    }while(!endLoop && pos!=std::string::npos);

    return split_vector;
}

int main(){
    std::vector<std::string> split_vector;
    split_vector= splitString("orange,apple,mango,tomato,banana,pineapple",",");
    for (std::vector<std::string>::iterator it = split_vector.begin(); it != split_vector.end(); ++it)
        std::cout << *it << std::endl;
    return 0;
}