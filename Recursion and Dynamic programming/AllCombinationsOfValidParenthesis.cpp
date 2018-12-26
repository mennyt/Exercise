//This program finds all possible matches for valid parethesis in size of n
//For example, when n=2: ()(), (())

#include <iostream> 
#include <list>

using StringList = std::list<std::string>;
void addParen(int leftRemain, int rightRemain, std::string currString, int strSize, StringList& stringList) {
    if (leftRemain < 0 || rightRemain < 0) {
        return;
    }
    if (leftRemain == 0 && rightRemain == 0) {
        stringList.push_back(currString);
    }
    if (leftRemain > 0) {
        currString[strSize]='(';
        addParen(leftRemain-1, rightRemain, currString, strSize+1, stringList);
    }
    if (leftRemain < rightRemain) {
        currString[strSize] = ')';
        addParen(leftRemain, rightRemain-1, currString, strSize+1, stringList);
    }
}

StringList getParens(int count) {
  StringList stringList; 
  std::string str(count*2, ' ');
  addParen(count, count, str, 0, stringList);
  return stringList;
}

void printParens(const StringList& parens) {
    std::cout << "number of combinations: " << parens.size() << "\n";
    for (auto paren : parens) {
        std::cout << paren << "\n";
    }
}

int main() {
    StringList parens = getParens(5);
    printParens(parens);
    
    return 0;
}