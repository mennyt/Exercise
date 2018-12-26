
// C++ program to find single source shortest paths for Directed Acyclic Graphs 
#include<iostream> 
#include <set>
#include <list>

static int s_count = 0;

class Edge {
public:
    Edge(int v1, int v2) : u(v1), v(v2) {}
  
    virtual bool operator<(const Edge& other) const {
        if (u < other.u) {
            return true;
        }
        if (u > other.u) {
            return false;
        }
        
        if (v < other.v) {
            return true;
        }
        if (v > other.v) {
             return false;
        }
    }

    int u;
    int v;
};

class Graph {
public: 
    Graph(int V) : _V(V) {
    }   
    ~Graph(void) {
    }
    
    bool addEdge(int u, int v) {
        if (!isVertexInRange(u) || !isVertexInRange(v)) {
            return false;
        }
        
        _edges.push_back({u, v});
    }
    
    void print() const {
        std::cout << "\nGraph: \n";
        for (auto edge : _edges) {
            std::cout << "(" << edge.u << ", " << edge.v << ")\n";    
        }     
    }
    
    std::set<int> vertexCoverUtil2(std::set<int> cover, std::list<Edge> availableEdges) const {
        std::cout << "\nAvailableEdges size: " << availableEdges.size();
        while(!availableEdges.empty()) {
            s_count++;
            auto iter = availableEdges.begin();
            const Edge& edge = *iter;
            availableEdges.erase(iter);
            
            if (cover.find(edge.u) != cover.end() ||
                cover.find(edge.v) != cover.end()) {
                continue;
            }
            
            cover.insert(edge.u);
            std::set<int> coverWithU = vertexCoverUtil2(cover, availableEdges);
            
            cover.erase(edge.u);
            cover.insert(edge.v);
            std::set<int> coverWithV = vertexCoverUtil2(cover, availableEdges);
            
            return (coverWithU.size() < coverWithV.size() ?  coverWithU : coverWithV);
        }
        return cover;
    }
    
    std::set<int> vertexCoverUtil(std::set<int> cover, std::set<Edge> coveredEdges) const {
        if (coveredEdges.size() == _edges.size()) {
            return cover;
        }
        
        for (auto edge : _edges) {
            s_count++;
            if (coveredEdges.find(edge) != coveredEdges.end()) {
                continue;
            }
            if (cover.find(edge.u) != cover.end() ||
                cover.find(edge.v) != cover.end()) {
                coveredEdges.insert(edge);
                continue;
            }
            
            //either cover u or v...
            coveredEdges.insert(edge);
            
            cover.insert(edge.u);
            std::set<int> coverWithU = vertexCoverUtil(cover, coveredEdges);
            
            cover.erase(edge.u);
            cover.insert(edge.v);
            std::set<int> coverWithV = vertexCoverUtil(cover, coveredEdges);
            
            return (coverWithU.size() < coverWithV.size() ?  coverWithU : coverWithV);
        }
        return cover;
    }
    
    std::set<int> vertexCover() const {
        std::set<int> cover;
        std::set<Edge> coveredEdges;
        
        return vertexCoverUtil(cover, coveredEdges);
    }
    
    std::set<int> vertexCover2() const {
        std::set<int> cover;
        std::list<Edge> availableEdges = _edges;
        
        return vertexCoverUtil2(cover, availableEdges);
    }
    
private:
    bool isVertexInRange(int v) {
        return v >=0 && v < _V;
    }
    
    int _V;
    std::list<Edge> _edges;
    
};

void printCover(const std::set<int>& cover) {
    std::cout << "vertex cover with " << s_count << " calls: ";
    for (int u : cover) {
        std::cout << u << ", ";
    }
}

int main() {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    
    std::set<int> cover = g.vertexCover2();
    printCover(cover);
    
    
    g.print();
} 