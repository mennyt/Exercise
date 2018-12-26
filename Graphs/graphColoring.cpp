
// C++ program to find single source shortest paths for Directed Acyclic Graphs 
#include<iostream> 
#include <set>
#include <list>
#include <map>
#include <vector>

class Graph {
public: 
    Graph(int V) : _V(V), _adj(new std::list<int>[V]) {
    }   
    ~Graph(void) {
        delete [] _adj;
    }
    
    bool addEdge(int u, int v) {
        if (!isVertexInRange(u) || !isVertexInRange(v)) {
            return false;
        }
        
        _adj[u].push_back(v);
        _adj[v].push_back(u);
    }
    
    void print() const {
        std::cout << "\nGraph: \n";
        for (int v = 0; v < _V; ++v) {
            for (auto u : _adj[v]) {
                std::cout << "(" << v << ", " << u << ")\n";    
            }
        }     
    }
    
    //In case no available color was found, return -1
    int pickVertexColor(int v, const std::map<int, int>& vertexColors, const std::vector<int>& colors) const {
        std::set<int> adjColors;
        for (auto u : _adj[v]) {
            auto vertexColorIter = vertexColors.find(u);
            if (vertexColorIter != vertexColors.end()) {
                adjColors.insert(vertexColorIter->second);
            }
        }
        
        for (auto color : colors) {
            if (adjColors.find(color) == adjColors.end()) {
                return color;
            }
        }
        return -1;
    }
    
     int colorGraph(std::map<int, int>& vertexColors) const {
        std::vector<int> colors = {1};
        
        for (int v = 0; v < _V; ++v) {
            if (vertexColors.find(v) != vertexColors.end()) {
                continue;
            }
            int color = pickVertexColor(v, vertexColors, colors);
            if (color == -1) {
                color = colors.size() + 1;
                colors.push_back(color);
            }
            vertexColors[v] = color;
        }
        return colors.size();
    }
    
    void printVertexColor(int numColors, const std::map<int, int>& colors) const {
        std::cout << "number of colors: " << numColors << "\n";
        for (int v = 0; v < _V; ++v) {
            std::cout << "vertex " << v << " colored with " << colors.at(v) << "\n";
        }
    }
    
private:
    bool isVertexInRange(int v) {
        return v >=0 && v < _V;
    }
    
    int _V;
    std::list<int>* _adj;
};


int main() {
    Graph g(6);
    g.addEdge(0, 3);
    g.addEdge(0, 4);
    g.addEdge(0, 5);
    
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(1, 5);
    
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(2, 5);
    
    std::map<int, int> vertexColors;
    int numColors = g.colorGraph(vertexColors);
    g.printVertexColor(numColors, vertexColors);
    
    g.print();
} 