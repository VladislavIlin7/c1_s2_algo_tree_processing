#include "graph.h"
#include "floyd.h"
#include "result.h"
#include <stdio.h>

int main(int argc, char **argv) {
    Graph *g;
    Result *r;
    const char *in_file = (argc > 1) ? argv[1] : "input.txt";
    const char *out_file = (argc > 2) ? argv[2] : "output.txt";

    g = graph_read_from_file(in_file);
    if (!g) {
        fprintf(stderr, "Input error\n");
        return 1;
    }

    printf("\nInput:\n");
    graph_print(g);

    r = floyd_warshall(g);
    if (!r) {
        fprintf(stderr, "Memory allocation error\n");
        graph_destroy(g);
        return 1;
    }

    if (result_has_negative_cycle(r)) {
        printf("\nResult:\n");
        printf("Negative cycle found\n");
    } else {
        printf("\nResult:\n");
        result_print_distances(r);
        result_save_to_file(r, out_file);

        printf("\nPath:\n");
        result_print_path(r, 0, g->n - 1);
    }

    graph_destroy(g);
    result_destroy(r);
    return 0;
}
