#define V 6
#define INF 1000000

void floyd_warshall(int graph[V][V]){
    int d[V][V];
    for(int i = 0; i < V; ++i){
        for(int j = 0; j < V; ++j){
            d[i][j] = graph[i][j];
        }
    }
    for(int k = 0; k < V; ++k){
        for(int i = 0; i < V; ++i){
            for(int j = 0; j < V; ++j){
                if (d[i][k] != INF && d[k][j] != INF && d[i][k] + d[k][j] < d[i][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }
    for(int i = 0; i < V; ++i){
        if(d[i][i] < 0){
            printf("Обраружен цикл с отрицательным весом");
        }
    }
}