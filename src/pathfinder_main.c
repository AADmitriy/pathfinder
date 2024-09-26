#include "pathfinder.h"
#include "../libmx/inc/libmx.h"


int main(int argc, char *argv[]) {
    if (argc != 2) { raise_usage_error(); }
    
    char** islands;
    int nodes_count = 0;
    int edges_count = 0;
    int **edges = get_edges(argv[1], &edges_count, &islands, &nodes_count);

    int* graph_info_rows_length = (int*)malloc(sizeof(int) * nodes_count);
    for (int i = 0; i < nodes_count; i++) {
        graph_info_rows_length[i] = 0;
    }
    int*** graph_info = create_graph_info(edges, edges_count, nodes_count, graph_info_rows_length);

    int* procesed_islands = (int*)malloc(0);

    for (int src = 0; src < nodes_count; src++) {
        int* dist;
        int* parent_count;
        int** parents = dijkstra_v2(graph_info, graph_info_rows_length, src, nodes_count, &dist, &parent_count);

        printPaths(parents, parent_count, dist, islands, src, nodes_count, procesed_islands, src);
    
        del_intarr(&parents, nodes_count);
        free(parent_count);
        free(dist);
        procesed_islands = (int*)mx_realloc(procesed_islands, (src+1) * sizeof(int));
        procesed_islands[src] = src;
    }

    for (int i = 0; i < nodes_count; i++) {
        del_intarr(&graph_info[i], graph_info_rows_length[i]);
    }
    free(graph_info);
    free(graph_info_rows_length);

    free(procesed_islands);
    del_intarr(&edges, edges_count);
    del_strarr(&islands, nodes_count);


    return 0;
}



