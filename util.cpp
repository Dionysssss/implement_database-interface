#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{

  //replace all punctuation with space
	for(unsigned int i=0; i< rawWords.size(); i++)
	{
		if(rawWords.at(i)=='\''||rawWords.at(i)==','||rawWords.at(i)=='.')
		{
			rawWords.at(i)=' ';
		}
	}
	std::stringstream rawstream; //store rawWords into a string stream
	rawstream << rawWords;
	std::set<std::string> temp; //create a set to restore and return
	string Kword;
	while(rawstream>>Kword)
	// iterate to set up temp
	{
		if(Kword.size()>=2) 
		// character>=2
		{
			temp.insert(Kword);
		}else
		{
			continue;
		}
	}





	return temp; //memory leak



}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
