#ifndef GRAPH_H
#define GRAPH_H

#include <pthread.h>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;


class Graph
{
    public:
        Graph(string filename);
        Graph(int numberNodes);
        virtual ~Graph();

        //Graph
        int getNumberNodes();
        void computeCentrality();
        void computePartCentrality(int start, int end);
        void printCentrality();
        void dijkstra(int source);

        //To centrality
        vector<float> centrality;
        int numberNodes;

    protected:

    private:
        int INFINITY = std::numeric_limits<int>::max();

        //CSC (compress sparce column)
        vector<float> edges_cost;
        vector<int> edges_tail;
        vector<int> indexs;

        //Graph
        bool addEdges(string filename);
        int readNumberOfNodes(string filename);
        int getSmallDistance(vector<bool> visited, vector<int> distance);
        void computeCentralityPath(int source, int tail, float incremento, vector<int> parents[]);


        //Node
        vector<float> getEdgesCost(int source);
        vector<int> getEdgesEdpoints(int source);
        int getNextIndex(int source);
        void resetCentrality(int source);
        void incrementCentrality(int source, float increment);
        float getCentrality(int source);
};

#endif // GRAPH_H
