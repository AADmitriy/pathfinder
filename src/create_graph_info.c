#include "pathfinder.h"
#include "../libmx/inc/libmx.h"


int*** create_graph_info(int** edges, int edges_size, int nodes_count, int* graph_info_rows_length) {
    int*** graph_table = (int***)malloc(sizeof(int**) * nodes_count);
    for (int i = 0; i < nodes_count; i++) {
        graph_table[i] = (int**)malloc(0);
    }

    for (int i = 0; i < edges_size; i++) {
        int *link1 = (int*)malloc(sizeof(int) * 2);
        link1[0] = edges[i][1];
        link1[1] = edges[i][2];
        append_to_intptrarr(&graph_table[edges[i][0]], &(graph_info_rows_length[edges[i][0]]), link1);
        int *link2 = (int*)malloc(sizeof(int) * 2);
        link2[0] = edges[i][0];
        link2[1] = edges[i][2];
        append_to_intptrarr(&graph_table[edges[i][1]], &(graph_info_rows_length[edges[i][1]]), link2);
    }

    return graph_table;
}


