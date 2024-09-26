#include "pathfinder.h"
#include "../libmx/inc/libmx.h"

void raise_usage_error(void) {
    mx_printerr("usage: ./pathfinder [filename]\n");
    exit(1);
}

void raise_not_existing_file_error(char* filename) {
    mx_printerr("error: file ");
    mx_printerr(filename);
    mx_printerr(" does not exist\n");
    exit(2);
}

void raise_empty_file_error(char* filename) {
    mx_printerr("error: file ");
    mx_printerr(filename);
    mx_printerr(" is empty\n");
    exit(3);
}

void raise_invalid_line_error(int line) {
    mx_printerr("error: line ");
    mx_printint_err(line);
    mx_printerr(" is not valid\n");
    exit(4);
}

void raise_invalid_nodes_num_error(void) {
    mx_printerr("error: invalid number of islands\n");
    exit(5);
}

void raise_duplicate_bridges_error(void) {
    mx_printerr("error: duplicate bridges\n");
    exit(6);
}

void raise_too_long_bridges_error(void) {
    mx_printerr("error: sum of bridges lengths is too big\n");
    exit(7);
}


