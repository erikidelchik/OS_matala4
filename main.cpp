#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstdlib>

using namespace std;


class Graph{
    vector<vector<int>> graph;

public:
    Graph() = default;
    Graph(vector<vector<int>> &g): graph(g){}

    Graph& operator=(Graph &g2){
        this->graph.clear();
        for(int i=0;i<g2.graph.size();i++){
            this->graph.push_back(g2.graph[i]);
        }

        return *this;
    }

    bool contains(vector<int> gr, int v){
        for(int i:gr){
            if(i==v){
                return true;
            }
        }
        return false;
    }

    void generateRandomGraph(int vertices, int edges, int seed) {
        vector<vector<int>> g(vertices);
        graph = g;



        srand(seed);

        // Generate a random graph with exactly the specified number of edges
        for (int i = 0; i < edges; ++i) {
            int u = rand() % vertices;
            int v = rand() % vertices;

            // check for self loops and duplicate edges
            while (u == v || contains(graph[u],v)) {
                u = rand() % vertices;
                v = rand() % vertices;
            }

            graph[u].push_back(v);
            graph[v].push_back(u);

        }
    }

    vector<int> findEulerianCycle() {
        vector<int> cycle;
        stack<int> stack;

        Graph g1 = *this;
        vector<vector<int>> tempGraph = g1.graph;

        stack.push(0); //start vertex

        while (!stack.empty()) {
            int vertex = stack.top();
            if (!tempGraph[vertex].empty()) {
                int nextVertex = tempGraph[vertex].back();
                stack.push(nextVertex);
                //erase the edge
                tempGraph[vertex].pop_back();
                tempGraph[nextVertex].erase(find(tempGraph[nextVertex].begin(), tempGraph[nextVertex].end(), vertex));

            } else {
                cycle.push_back(vertex);
                stack.pop();
            }
        }

        return cycle;
    }


    bool checkIfExist(){
        int deg;

        //check if deg for each vertex is even
        for(int i=0;i<graph.size();i++){
            deg = this->graph[i].size();
            //count the edges from other vertices to this vertex
            for(int j=0;j<graph.size();j++){
                if(i!=j && contains(graph[j],i))
                    deg++;
            }
            if(deg%2!=0){
                cout<<"the graph does not have euler cycle because the degree of vertex "<<i<<" is odd";
                return false;
            }
        }

        vector<int> cycle = findEulerianCycle();
        string c;
        

        for(int i=0;i<cycle.size();i++){
            c+= to_string(cycle[i]);

            if(i<cycle.size()-1)
                c+="->";
        }
        cout<<c<<endl;

        return true;

    }
};



int main(int argc,char* argv[]) {
    int vertices;
    int edges;
    int seed;

    // Parse command line arguments
//    int opt;
//    while ((opt = getopt(argc, argv, "v:e:s:")) != -1) {
//        switch (opt) {
//            case 'v':
//                vertices = atoi(optarg);
//                break;
//            case 'e':
//                edges = atoi(optarg);
//                break;
//            case 's':
//                seed = atoi(optarg);
//                break;
//            default:
//                cerr << "Usage: " << argv[0] << " -v vertices -e edges -s seed" << endl;
//                return 1;
//        }
//    }
//    if (vertices <= 0 || edges <= 0) {
//        cerr << "Number of vertices and edges must be positive." << endl;
//        return 1;
//    }



    Graph g;
    g.generateRandomGraph(4,6,2);
    g.checkIfExist();

}

