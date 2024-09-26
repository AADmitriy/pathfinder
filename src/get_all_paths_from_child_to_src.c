#include "pathfinder.h"
#include "../libmx/inc/libmx.h"


void get_all_paths_from_child_to_src(int*** path_to_src, int** paths_length, int* paths_count,
                                     int** parent, int* parent_count,
                                     int* current_path, int current_path_length, int src, int child) {
    if (child == src) {
        int length = *paths_count;
        append_to_intarr(&current_path, &current_path_length, src);
        append_to_intarr(paths_length, &length, current_path_length);
        append_to_intptrarr(path_to_src, paths_count, current_path);
        return;
    }

    for (int i = 0; i < parent_count[child]; i++) {
        int* updated_path = (int*)malloc((current_path_length + 1) * sizeof(int));
        cpy_intarr(&updated_path, current_path, current_path_length);
        updated_path[current_path_length] = child;
        get_all_paths_from_child_to_src(path_to_src, paths_length, paths_count,
            parent, parent_count,
            updated_path, current_path_length + 1, src, parent[child][i]);
    }
    free(current_path);
}


