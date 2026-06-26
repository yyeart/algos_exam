#include <stdio.h>
#include <stdlib.h>

#define V 5
#define INF 1000000

int min_key(int key[], int mst_set[]){
    int min = INF, min_index = -1;
    for(int v = 0; v < V; ++v){
        if(!mst_set[v] && key[v] < min){
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void prim_mst(int graph[V][V]) {
    int parent[V];
    int key[V];
    int mst_set[V];
    for(int i = 0; i < V; ++i){
        key[i] = INF;
        mst_set[i] = 0;
    }
    key[0] = 0;
    parent[0] = -1;

    for(int count = 0; count < V - 1; count++) {
        int u = min_key(key, mst_set);
        if(u == -1) break;
        mst_set[u] = 1;
        for(int v = 0; v < V; ++v){
            if(graph[u][v] && !mst_set[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }
    for(int i = 1; i < V; ++i){
        printf("%d - %d \tВес: %d\n", parent[i], i, graph[i][parent[i]]);
    }
}