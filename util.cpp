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
    to a set of words based on the criteria given in the assignment; 
    taking a string of many words and splitting them into individual 
    keywords (split at punctuation, with at least 2 character words)**/
std::set<std::string> parseStringToWords(string rawWords)
{
    std::set<std::string> keywords;
    string rawWords_lower = convToLower(rawWords);
    string rawWords_lower_trimmed = ltrim(rawWords_lower);
    string keyword;

    for (int i = 0; i < rawWords_lower_trimmed.size(); i++) {
        if (ispunct(rawWords_lower_trimmed[i]) || isspace(rawWords_lower_trimmed[i])) {
            if (keyword.length() >= 2) {
                keywords.insert(keyword);
            }
            keyword = "";
        }
        else {
            keyword.push_back(rawWords_lower_trimmed[i]);
        }
    }
    if (keyword.length() >= 2) {
        keywords.insert(keyword);
    }

    return keywords;
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
