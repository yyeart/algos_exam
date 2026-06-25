#define V 6
#define INF 1000000

void dijkstra(int graph[V][V], int src){
    int dist[V];
    int visited[V];
    for(int i = 0; i < V; ++i){
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[src] = 0;

    for(int count = 0; count < V - 1; ++count){
        int min = INF, u = -1;
        for(int v = 0; v < V; ++v){
            if(!visited[v] && dist[v] <= min) {
                min = dist[v];
                u = v;
            }
        }
        if (u == -1) break;
        visited[u] = 1;

        for(int v = 0; v < V; ++v){
            if(!visited[v] && graph[u][v] && dist[u] != INF 
                && dist[u] + graph[u][v] < dist[v]){
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
}