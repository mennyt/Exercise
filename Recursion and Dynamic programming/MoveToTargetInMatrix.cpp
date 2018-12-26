
// Given a matrix of N*M, write a function to return the number of ways from location (x,y) to (w, z) 
// and the paths as well. You can move wither right or down.
// Also support locations that you cannot go thru...

#include<iostream> 
#include <algorithm>
#include <map>
#include <set>
#include <list>

class Point {
    public:
    Point(int x1, int y1) : x(x1), y(y1) {}
    bool operator==(const Point& point) {
        return x == point.x && y == point.y;
    }
    
    bool operator<(const Point& point) const{
        if (x < point.x) {
            return true;
        }
        if (x > point.x) {
            return false;
        }
        if (y < point.y) {
            return true;
        }
        if (y > point.y) {
            return false;
        }
        return false;
    }
    
    std::string serialize() const {
        return "(" +  std::to_string(x) + ", " + std::to_string(y) + ") ";
    }
    int x;
    int y;
};

using Path = std::list<Point>;
using PathList = std::list<Path>;
int countCalls = 0;

class Board {
public:
    Board(int lastX1, int lastY1, const std::set<Point>& trapLocation) : 
    lastX(lastX1), lastY(lastY1), traps(trapLocation) {}
    
    Point turnRight(const Point& point) const {
        return Point(point.x+1, point.y);
    }
    Point moveDown(const Point& point) const {
        return Point(point.x, point.y+1);
    }
    bool isValid(const Point& point) const {
        if (point.x < 0 || point.x > lastX ||
            point.y < 0 || point.y > lastY) {
                return false;
        }
        return (traps.find(point) == traps.end());
    }
    bool accesible(const Point& currLoc, const Point& targetLoc) const {
        if (traps.find(currLoc) != traps.end() || traps.find(targetLoc) != traps.end()) {
            return false;
        }
        if (currLoc.y > targetLoc.y) {
            return false;
        }
        if (currLoc.y < targetLoc.y) {
            return true;
        }
        return currLoc.x <= targetLoc.x;
    }
    
    int countWays(Point currLoc, Point targetLoc) const;
private:
    int lastX;
    int lastY;
    std::set<Point> traps;
    
private:
    int countWaysUtil(Point currLoc, Point targetLoc, 
    std::map<Point, int>& waysFromLocationToTarget, Path currPath, PathList& pathList) const;

    void printPaths(const PathList& pathList) const;
};

int Board::countWaysUtil(Point currLoc, Point targetLoc, 
    std::map<Point, int>& waysFromLocationToTarget, Path currPath, PathList& pathList) const {
    countCalls++;
    
    if (!isValid(currLoc) || !isValid(targetLoc) || !accesible(currLoc, targetLoc)) {
        return 0;
    }
    currPath.push_back(currLoc);
    if (currLoc == targetLoc) {
        pathList.push_back(currPath);
        return 1;
    }
   
    Point rightLoc = turnRight(currLoc);
    Point DownLoc = moveDown(currLoc);
    
    auto currLocIter = waysFromLocationToTarget.find(currLoc);
    if (currLocIter != waysFromLocationToTarget.end()) {
        return currLocIter->second;
    }
    int numWays = countWaysUtil(turnRight(currLoc), targetLoc, waysFromLocationToTarget, currPath, pathList) + 
                countWaysUtil(moveDown(currLoc), targetLoc, waysFromLocationToTarget, currPath, pathList);
                
    waysFromLocationToTarget[currLoc] = numWays;    
    
    return numWays;
}

int Board::countWays(Point currLoc, Point targetLoc) const {
    std::map<Point, int> waysFromLocationToTarget;
    Path path;
    PathList pathList;
    int res = countWaysUtil(currLoc, targetLoc, waysFromLocationToTarget, path, pathList);
    
    printPaths(pathList);
    
    return res;
}

void Board::printPaths(const PathList& pathList) const {
    std::cout << "Number of paths: " << pathList.size() << std::endl;
    for (auto path : pathList) {
        for (auto point : path) {
            std::cout << point.serialize() << ",  ";
        }
        std::cout << std::endl;
    }
}

int main() {
    int lastX = 2;
    int lastY = 2;
    std::set<Point> traps {{0, 2}, {1, 0}, {2, 0}};
    Board board{lastX, lastY, traps};
    
    Point startPoint{0, 0};
    Point targetPoint{lastX, lastY};
    
    
    std::cout << "number of ways to from " << startPoint.serialize() << " to " << 
    targetPoint.serialize() << ": " << board.countWays(startPoint, targetPoint);
    std::cout << "\nnumber of calls: " << countCalls;
}
