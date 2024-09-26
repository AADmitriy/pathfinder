#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "pathfinder.h"
#include "../libmx/inc/libmx.h"

bool is_alphabetical(char c) {
    return ((c >='A' && c <= 'Z') || (c >= 'a' && c<='z'));
}

bool is_valid_str(char* str) {
    bool is_empty = true;
    while (*str != '\0') {
        is_empty = false;
        if(!is_alphabetical(*str)) {
            return false;
        }
        str++;
    }
    return !is_empty;
}


void append_edge(int*** edges, int* edges_size, int node1, int node2, int weight) {
    *edges = (int**)mx_realloc(*edges, (*edges_size + 1) * sizeof(int*));
    int* edge = (int*)malloc(3 * sizeof(int));
    edge[0] = node1;
    edge[1] = node2;
    edge[2] = weight;
    (*edges)[*edges_size] = edge;
    *edges_size = *edges_size + 1;
}

bool is_same_edges(int* edge1, int* edge2) {
    if ((edge1[0] == edge2[0] && edge1[1] == edge2[1])
        ||
        (edge1[1] == edge2[0] && edge1[0] == edge2[1])) {
        return true;
    }
    return false;
}

bool has_duplicate_edges(int** edges, int edges_count) {
    for (int i = 0; i < edges_count - 1; i++) {
        for (int j = i + 1; j < edges_count; j++) {
            if (is_same_edges(edges[i], edges[j])) {
                return true;
            }
        }
    }
    return false;
}

bool sum_of_bridges_too_long(int** edges, int edges_count) {
    int sum = edges[0][2];
    for (int i = 1; i < edges_count; i++) {
        if (INT_MAX - edges[i][2] < sum) {
            return true;
        }
    }
    return false;
}

int** get_edges(char* filename, int* edges_size, char*** islands_ptr, int* node_count) {
    int fd = open(filename, O_RDONLY);

    if (fd < 0) { raise_not_existing_file_error(filename); }

    char* nodes_num_str;
    int bytes_to_read = mx_read_line(&nodes_num_str, 64, '\n', fd, false);

    if (bytes_to_read == -1) {
        mx_read_line(NULL, 0, '\n', 0, true);
        raise_empty_file_error(filename);
    }
    if (bytes_to_read == 0) {
        mx_read_line(NULL, 0, '\n', 0, true);
        raise_invalid_line_error(1);
    }
    
    int input_nodes_num = strict_atoi(nodes_num_str);

    free(nodes_num_str);

    if (input_nodes_num == -1) { 
        mx_read_line(NULL, 0, '\n', 0, true);
        raise_invalid_line_error(1); 
    }

    char** islands = (char**)malloc(0);
    int real_nodes_num = 0;
    int** edges = (int**)malloc(0);
    int edges_count = 0;
    char* island1;
    char* island2;
    char* edge_weight;
    int island1_id, island2_id, weight;
    int line = 2;
    
    bytes_to_read = mx_read_line(&island1, 64, '-', fd, false);
    

    while (bytes_to_read != -1) {
        if (bytes_to_read == 0 || !is_valid_str(island1)) {
            
            mx_read_line(NULL, 0, '\n', 0, true);
            if (bytes_to_read != 0) { free(island1); }
            del_intarr(&edges, edges_count);
            del_strarr(&islands, real_nodes_num);
            raise_invalid_line_error(line);
        }

        island1_id = get_str_index(islands, real_nodes_num, island1);
        if (island1_id  == -1) {
            island1_id  = real_nodes_num;
            append_to_strarr(&islands, &real_nodes_num, island1);
        }
        else {
            free(island1);
        }

        bytes_to_read = mx_read_line(&island2, 64, ',', fd, false);
        
        if (bytes_to_read == 0 || !is_valid_str(island2)) {
            mx_read_line(NULL, 0, '\n', 0, true);
            if (bytes_to_read != 0) { free(island2); }
            del_intarr(&edges, edges_count);
            del_strarr(&islands, real_nodes_num);
            raise_invalid_line_error(line);
        }

        island2_id = get_str_index(islands, real_nodes_num, island2);
        if (island2_id  == -1) {
            island2_id = real_nodes_num;
            append_to_strarr(&islands, &real_nodes_num, island2);
            
        }
        else {
            free(island2);
        }

        bytes_to_read = mx_read_line(&edge_weight, 64, '\n', fd, false);
        if (bytes_to_read == 0) {
            mx_read_line(NULL, 0, '\n', 0, true);
            del_intarr(&edges, edges_count);
            del_strarr(&islands, real_nodes_num);
            raise_invalid_line_error(line);
        }
        
        weight = strict_atoi(edge_weight);
        mx_strdel(&edge_weight);

        if (weight == -1) {
            mx_read_line(NULL, 0, '\n', 0, true);
            del_intarr(&edges, edges_count);
            del_strarr(&islands, real_nodes_num);
            raise_invalid_line_error(line);
        }
        if (island1_id == island2_id) {
            mx_read_line(NULL, 0, '\n', 0, true);
            del_intarr(&edges, edges_count);
            del_strarr(&islands, real_nodes_num);
            raise_invalid_line_error(line);
        }
        append_edge(&edges, &edges_count, island1_id, island2_id, weight);


        bytes_to_read = mx_read_line(&island1, 64, '-', fd, false);
        line++;
    }
    close(fd);


    if (input_nodes_num != real_nodes_num) {
        del_intarr(&edges, edges_count);
        del_strarr(&islands, real_nodes_num);
        raise_invalid_nodes_num_error();
    }

    if (has_duplicate_edges(edges, edges_count)) {
        del_intarr(&edges, edges_count);
        del_strarr(&islands, real_nodes_num);
        raise_duplicate_bridges_error();
    }
    
    if (sum_of_bridges_too_long(edges, edges_count)) {
        del_intarr(&edges, edges_count);
        del_strarr(&islands, real_nodes_num);
        raise_too_long_bridges_error();
    }
    

    *edges_size = edges_count;
    *islands_ptr = islands;
    *node_count = real_nodes_num;

    return edges;
}



