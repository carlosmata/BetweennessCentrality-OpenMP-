#include <iostream>
#include "Graph.h"
#include <bits/stdc++.h>
#include <chrono>
#include <omp.h>

using namespace std;

#pragma omp declare reduction(vec_float_plus : std::vector<float> : \
                              std::transform(omp_out.begin(), omp_out.end(), omp_in.begin(), omp_out.begin(), std::plus<float>())) \
                    initializer(omp_priv = omp_orig)

int main(int argc, char **argv)
{
    int NUMBERTHREADS = 4;
    string filename = "datasets/test2.txt";
    if(argc > 1){
    	filename = argv[1];
    }

    if(argc > 2){
        NUMBERTHREADS = atoi(argv[2]);
    }

    cout<< "Number of threads: "<< NUMBERTHREADS << endl;
    Graph *g = new Graph(filename);

    if(g->getNumberNodes() > 0)
    {
        auto start = chrono::high_resolution_clock::now();
        ios_base::sync_with_stdio(false);

        cout << "Number of Nodes: " << g->getNumberNodes() << endl;
        //----------------------------PARALLEL PART-------------------------------------------------
        int nodo_i, tid;
        int n = g->numberNodes;

        int s, e;
        int threadLen = n / NUMBERTHREADS;

        omp_set_num_threads(NUMBERTHREADS);
        //
        #pragma omp parallel private(nodo_i, tid, s, e) //shared(g)
        {
            tid = omp_get_thread_num();

            cout<< tid <<endl;
            
            s = tid * threadLen;
            e   = s + threadLen;

            g->computePartCentrality(s, e);
            //#pragma omp for reduction(vec_float_plus: g->centrality)
            /*for (nodo_i = start; nodo_i < end; nodo_i++) {
                cout << endl;
                cout<< "Hilo:" << tid << ", Nodo" << nodo_i << endl;
                g->dijkstra(nodo_i);
                //c[nodo_i] += g->centrality[nodo_i];
            }*/
        }

        //---------------------------------------------------------------------------------------
        auto end = chrono::high_resolution_clock::now();

        cout << "Centrality: " << endl;
        g->printCentrality();

        // Calculating total time taken by the program.
        double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        time_taken *= 1e-9;

        cout << "Time taken by program is : " << fixed
             << time_taken << setprecision(9);
        cout << " sec" << endl;

    }
    else
        cout << "Data null in the dataset";

    delete g;
}

