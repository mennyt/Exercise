/*
TLDR: Transform word in dictionary by changing only one letter

Given two words of equal length that are in a dictionary, 
write a method to transform one word into another word by changing only 
one letter at a time The new word you get in each step must be in the dictionary
SOLUTION
EXAMPLE:
Input: DAMP, LIKE
Output: DAMP -> LAMP -> LIMP -> LIME -> LIKE
*/

#include <iostream> 
#include <set>
#include <list>

using StringSet = std::set<std::string>;
using StringList = std::list<std::string>;

bool isOneCharDiff(const std::string& source, const std::string& target) {
    if (source.size() != target.size()) {
        return false;
    }    
    
    bool diffFound = false;
    for (int i = 0; i < source.size(); ++i) {
        if ( source[i] != target[i]) {
            if (diffFound) {
                return false;
            }
            diffFound = true;
        }
    }
    return diffFound ? true : false;
}


StringList oneDiffStrings(const std::string& target, const StringSet& dict) {
    StringList outList;
    for (auto str : dict) {
        if (isOneCharDiff(str, target)) {
            outList.push_back(str);
        }
    }
    return outList;
}

StringList transformWord(const std::string& source, const std::string& target, 
                    const StringSet& dict, StringSet usedWords, StringList path) {
    if (source == target) {
        path.push_back(target);
        return path;
    }
    
    path.push_back(source);
    usedWords.insert(source);
    
    StringList nextStrings = oneDiffStrings(source, dict);
    for (auto nextStr : nextStrings) {
        if (usedWords.find(nextStr) != usedWords.end()) {
            continue;
        }
        StringList currPath = transformWord(nextStr, target, dict, usedWords, path);
        if (!currPath.empty()) {
            return currPath;
        }
    }
    
    return StringList();
}

StringList transformWord(const std::string& source, const std::string& target, const StringSet& dict) {
    StringSet usedWords;
    StringList path;
    return transformWord(source, target, dict, usedWords, path);                   
}

void printList(const StringList& stringList) {
    bool isFirst = true;
    for (auto str : stringList) {
        std::cout << (isFirst ? "" : " --> ") << str;
        isFirst = false;
    }
}
int main() { 
    StringSet dict = {{"ABC"}, {"GBC"}, {"ABG"}, {"ABD"}, {"AED"}, {"GEP"}, {"BED"}};
    StringList path = transformWord ("ABC", "BED", dict);
    printList (path);
    return 0;
}
