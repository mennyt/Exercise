/*
Print graph in DFS/BFS using recusrsive
Print graph iteratively
*/

#include <iostream> 
#include <list>
#include <stack>

class Graph {
public:
    Graph(int v) : V(v) {
        adj = new std::list<int>[V];
    }   
    
    ~Graph() {
        delete [] adj;
    }
    
    void addEdge(int source, int target) {
        adj[source].push_back(target);
    }
    
    void printDFS() const {
        std::cout << "\nDFS Print: \n";
        bool* visited = new bool [V];
        for (int i = 0; i < V; ++i) {
            visited [i] = false;
        }
        
        for (int edge = 0; edge < V; ++edge) {
            if (visited[edge]) {
                continue;
            }
            printDFSUtil(edge, visited);
        }
        delete [] visited;
    }
    
    void printBFS() const {
        std::cout << "\nBFS Print: \n";
        
        for (int v = 0; v < V; ++v) {
            for (auto u : adj[v]) {
                std::cout << "(" << v << ", " << u << ")\n";    
            }
        }     
    }
    
    void printIterative(int source) {
        std::cout << "\nPrint iteratively: \n";
        
        bool* visited = new bool [V];
        for (int i = 0; i < V; ++i) {
            visited [i] = false;
        }
        
        std::stack<int> actionQueue;
        actionQueue.push(source);
        visited[source] = true;
        
        while (!actionQueue.empty()) {
            int u = actionQueue.top();
            actionQueue.pop();
            
            for (auto v : adj[u]) {
                std::cout << u << " --> " << v << "\n";
                
                if (!visited[v]) {
                    visited[v] = true;
                    actionQueue.push(v);
                }
            }
        }
    }
    
private:
    int V;
    std::list<int>* adj;
    
    void printDFSUtil(int source, bool* visited) const {
        visited[source] = true;
        for (auto target : adj[source]) {
            std::cout << source << " --> " << target << "\n";
            
            if (!visited[target]) {
                printDFSUtil(target, visited);
            }
        }
    }
};

int main() { 
    Graph g(5);
    g.addEdge(0, 3);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 4);
    
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    
    g.addEdge(2, 3);
    
    g.addEdge(3, 0);
    
    g.printIterative(0);
    // g.printBFS();
    // g.printDFS();
    
    return 0;
}
