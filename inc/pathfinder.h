#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>


typedef struct MinHeapNode {
    int id;
    int weight;
}              MinHeapNode;

typedef struct MinHeap {
    int size;     
    int capacity;  
    int *pos;    
    MinHeapNode **array;
}              MinHeap;



int** get_edges(char* filename, int* edges_size, char*** islands_ptr, int* node_count);
int*** create_graph_info(int** edges, int edges_size, int nodes_count, int* graph_info_rows_length);
int** dijkstra_v2(int*** graph_info, int* graph_info_rows_length, int src, int nodes_count, int **dist_ptr, int **parent_counts);
void printPaths(int** parent, int* parent_count, int* dist, char** islands, int src, int nodes_count, int* processed_nodes, int processed_nodes_count);
void get_all_paths_from_child_to_src(int*** path_to_src, int** paths_length, int* paths_count,
                                     int** parent, int* parent_count,
                                     int* current_path, int current_path_length, int src, int child);


// Errors
void raise_usage_error(void);
void raise_not_existing_file_error(char* filename);
void raise_empty_file_error(char* filename);
void raise_invalid_line_error(int line);
void raise_invalid_nodes_num_error(void);
void raise_duplicate_bridges_error(void);
void raise_too_long_bridges_error(void);


// Heap functions
MinHeapNode* newMinHeapNode(int v, int dist);
MinHeap* createMinHeap(int capacity);
void del_minHeap(MinHeap** minHeap);
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b);
void minHeapify(MinHeap* minHeap, int idx);
int isEmpty(MinHeap* minHeap);
MinHeapNode* extractMin(MinHeap* minHeap);
void decreaseKey(MinHeap* minHeap, int v, int dist);
bool isInMinHeap(MinHeap *minHeap, int v);







