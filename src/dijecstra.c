#include "pathfinder.h"
#include "../libmx/inc/libmx.h"


int** dijkstra_v2(int*** graph_info, int* graph_info_rows_length, int src, int nodes_count, int **dist_ptr, int **parent_counts) {
    int* dist = (int*)malloc(nodes_count * sizeof(int));
    int* parent_count = (int*)malloc(nodes_count * sizeof(int));
    int** parent = (int**)malloc(nodes_count * sizeof(int*));

    for (int i = 0; i < nodes_count; i++) {
        parent[i] = (int*)malloc(sizeof(int));
        parent[i][0] = -1;
        parent_count[i] = 0;
    }

    MinHeap* minHeap = createMinHeap(nodes_count);
    

    for (int i = 0; i < nodes_count; i++) {
        if (i == src) {
            continue;
        }
        dist[i] = INT_MAX;
        minHeap->array[i] = newMinHeapNode(i, dist[i]);
        minHeap->pos[i] = i;
    }

    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src] = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
    minHeap->size = nodes_count;

    while (!isEmpty(minHeap)) {
        MinHeapNode* minHeapNode = extractMin(minHeap);

        int u = minHeapNode->id;
        free(minHeapNode);

        for (int i = 0; i < graph_info_rows_length[u]; i++) {
            int v = graph_info[u][i][0];
            int weight = graph_info[u][i][1];

            if (!isInMinHeap(minHeap, v) || dist[u] == INT_MAX) { continue; }

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = (int*)mx_realloc(parent[v], sizeof(int));
                parent[v][0] = u;
                parent_count[v] = 1;
                decreaseKey(minHeap, v, dist[v]);
            }
            else if (dist[u] + weight == dist[v]) {
                parent[v] = (int*)mx_realloc(parent[v], (parent_count[v] + 1) * sizeof(int));
                parent[v][parent_count[v]] = u;
                parent_count[v] = parent_count[v] + 1;
            }
        }
    }

    free(minHeap->array);
    free(minHeap->pos);
    free(minHeap);

    *dist_ptr = dist;
    *parent_counts = parent_count;

    return parent;
}



