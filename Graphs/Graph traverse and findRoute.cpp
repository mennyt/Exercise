
// C++ program to find single source shortest paths for Directed Acyclic Graphs 
#include<iostream> 
#include <list>
#include <queue>
#include <stack>

class Graph {
public:
    explicit Graph(int numV) : V(numV) {
        _adj = new std::list<int>[numV];
    }
    
    Graph(const Graph& other) = delete;
    Graph& operator=(const Graph& other) = delete;
    
    ~Graph() {
        delete [] _adj;
    }
    
    void addEdge(int source, int target) {
        _adj[source].push_back(target);
    }
    
    bool isRouteUtilDFS(int source, int target, bool* visited) const {
        // std::cout << std::endl << source;
        
        for (auto u : _adj[source]) {
            if (u == target) {
                return true;
            }
            if (!visited[u]) {
                visited[u] = true;
                if (isRouteUtilDFS(u, target, visited)) {
                    return true;
                }
            }
        }
        return false;
    }
    
    bool isRouteDFS(int source, int target) const {
        //TODO: check that source and target are valid (between 0 to V)
        
        bool* visited = new bool[V];
        for (int i = 0; i < V; ++i) {
            visited[i] = false;
        }
        bool res = isRouteUtilDFS(source, target, visited);
        
        delete [] visited;
        return res;
    }
    
    bool isRouteBFS(int source, int target) const {
        bool* visited = new bool[V];
        for (int i = 0; i < V; ++i) {
            visited[i] = false;
        }
        
        std::queue<int> actionStack;
        actionStack.push(source);
        
        while(!actionStack.empty()) {
            source = actionStack.front();
            actionStack.pop();
            
            std::cout << std::endl << source;
            
            if (source == target) {
                return true;
            }
            visited[source] = true;
            for (auto u : _adj[source]) {
                if (!visited[u]) {
                    if (u == target) {
                        return true;
                    }
                    actionStack.push(u);
                }
            }
        }
        delete [] visited;
        return false;
    }
    
    bool getRouteUtilDFS(int source, int target, bool* visited, std::list<int>& route) const {
        // std::cout << std::endl << source;
        
        for (auto u : _adj[source]) {
            if (u == target) {
                route.push_back(u);
                return true;
            }
            if (!visited[u]) {
                visited[u] = true;
                route.push_back(u);
                if (getRouteUtilDFS(u, target, visited, route)) {
                    return true;
                }
                route.pop_back();
            }
        }
        return false;
        
    }
    
    std::list<int> getRouteDFS(int source, int target) const {
        //TODO: check that source and target are valid (between 0 to V)
        
        bool* visited = new bool[V];
        for (int i = 0; i < V; ++i) {
            visited[i] = false;
        }
        std::list<int> route{source};
        bool res = getRouteUtilDFS(source, target, visited, route);
        
        delete [] visited;
        
        if (res) {
            std::cout << " The route: ";
            for (auto node : route) {
                std::cout << node << ", ";
            }
        } else {
            std::cout << "Route was not found!!!";
        }
        return route;
    }
    
private:
    int V;
    std::list<int>* _adj;    
};

int main() {
  Graph g(9);
  g.addEdge(0, 1);
  g.addEdge(0, 7);
  g.addEdge(7, 8);
  g.addEdge(1, 2);
  g.addEdge(1, 3);
  g.addEdge(1, 4);
  g.addEdge(4, 5);
  g.addEdge(4, 6);
//   g.addEdge(6, 8);
//   std::string msg = g.isRouteDFS(0, 8) ? "\nFound!" : "\nNo!!!!";
    std::list<int> route = g.getRouteDFS(0, 8);
    
//   std::cout << msg;
  
  
}