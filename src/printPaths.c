#include "pathfinder.h"
#include "../libmx/inc/libmx.h"


void sort_parents(int*** parents, int* parent_count, int nodes_count) {
    for (int i = 0; i < nodes_count; i++) {
        if (parent_count[i] == 1) { continue; }
        mx_quicksort(&((*parents)[i]), 0, parent_count[i] - 1);
    }
}

void print_single_path_info(int* path_from_dst, int path_length, int* dist, int dst, int src, char** islands) {
    mx_printstr("========================================\n");
    mx_printstr("Path: ");
    mx_printstr(islands[src]);
    mx_printstr(" -> ");
    mx_printstr(islands[dst]);
    mx_printstr("\n");
    
    mx_printstr("Route: ");
    for (int j = path_length - 1; j >= 0; j--) {
        if (j == 0) {
            mx_printstr(islands[path_from_dst[j]]);
            continue;
        }
        mx_printstr(islands[path_from_dst[j]]);
        mx_printstr(" -> ");
    }
    mx_printstr("\nDistance: ");
    if (path_length < 3) {
        mx_printint(dist[path_from_dst[0]]);
    }
    else {
        for (int j = path_length - 1; j >= 0; j--) {
            if (j == 0) {
                mx_printint(dist[path_from_dst[j]]);
                continue;
            }
            if (j == 1) {
                mx_printint(dist[path_from_dst[j - 1]] - dist[path_from_dst[j]]);
                mx_printstr(" = ");
                continue;
            }
            mx_printint(dist[path_from_dst[j - 1]] - dist[path_from_dst[j]]);
            mx_printstr(" + ");
        }
    }
    mx_printstr("\n========================================\n");
}

void printPaths(int** parent, int* parent_count, int* dist, char** islands, int src, int nodes_count, int* processed_nodes, int processed_nodes_count) {
    sort_parents(&parent, parent_count, nodes_count);

    for (int child = 0; child < nodes_count; child++) {
        if (child == src || num_inarray(processed_nodes, processed_nodes_count, child)) { continue; }

        int** paths_to_src = (int**)malloc(0);
        int* paths_length = (int*)malloc(0);
        int paths_count = 0;
        int* current_path = (int*)malloc(0);

        get_all_paths_from_child_to_src(&paths_to_src, &paths_length, &paths_count, parent, parent_count, current_path, 0, src, child);

        for (int i = 0; i < paths_count; i++) {
            int path_length = paths_length[i];
            print_single_path_info(paths_to_src[i], path_length, dist, child, src, islands);
        }

        del_intarr(&paths_to_src, paths_count);
        free(paths_length);
    }
}


