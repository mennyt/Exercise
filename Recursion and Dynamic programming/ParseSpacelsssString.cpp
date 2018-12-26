//This program parses a string with no spaces based on a dictionary.
//It returns the best translations in terms of the minimal number of untranslated characters.

//TODO: Can be improved by using dynamic programming method and cache the results to prevent 
//redundant recursive calls

#include <iostream>
#include <map>
#include <climits>
#include <list>
#include <set>

// using Dict = std::map<std::string, int>;
using Dict = std::set<std::string>;
using Words = std::list<std::string>;
int translate(const std::string& str, const Dict& dict, Words& words) {
    if (str.empty()) {
        return 0;
    }
    if (dict.find(str) != dict.end()) {
        words.push_back(str);
        return 0;
    }
    if (str.size() == 1) {
        words.push_back(str);
        return 1;
    }
    const int size = str.size();
    int minUnt = INT_MAX;
    for (int splitIndex = 1; splitIndex < size; ++splitIndex) {
        Words translatedWordsLeft;
        std::string leftStr = str.substr(0, splitIndex);
        
        Words translatedWordsRight;
        std::string rightStr = str.substr(splitIndex, size - splitIndex + 1);
        
        int currUnt =   translate(leftStr, dict, translatedWordsLeft) +
                        translate(rightStr, dict, translatedWordsRight);
        if (currUnt < minUnt) {
            translatedWordsRight.insert(translatedWordsRight.begin(), translatedWordsLeft.begin(), translatedWordsLeft.end());
            words.clear();
            words.insert(words.begin(), translatedWordsRight.begin(), translatedWordsRight.end());
            minUnt = currUnt;
        }
    }
    
    return minUnt;
    
}

int main() {
    Dict dict{"this", "is", "a", "dog"};
    std::string str ("thisisaidogi");
    Words words;
    int count = translate(str, dict, words);
    std::cout << "minimal untranslated text: " << count << "\n";
    for (auto word : words) {
        std::cout << word << ", ";
    }
}