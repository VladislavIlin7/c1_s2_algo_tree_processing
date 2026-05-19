#ifndef GRAPH_H
#define GRAPH_H

#define INF 1000000000

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int n;
    int **matrix;
} Graph;

Graph *graph_create(int n);

void graph_destroy(Graph *g);

void graph_add_edge(Graph *g, int u, int v, int w);

Graph *graph_read_from_file(const char *filename);

void graph_print(const Graph *g);

#ifdef __cplusplus
}
#endif

#endif
