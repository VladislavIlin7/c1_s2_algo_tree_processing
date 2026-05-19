#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

Graph* graph_create(int n) {
    int i, j;
    Graph *g = (Graph*)malloc(sizeof(Graph));
    if (!g) return NULL;

    g->n = n;
    g->matrix = (int**)malloc(n * sizeof(int*));
    if (!g->matrix) {
        free(g);
        return NULL;
    }

    for (i = 0; i < n; i++) {
        g->matrix[i] = (int*)malloc(n * sizeof(int));
        if (!g->matrix[i]) {
            while (i > 0) {
                i--;
                free(g->matrix[i]);
            }
            free(g->matrix);
            free(g);
            return NULL;
        }

        for (j = 0; j < n; j++) {
            g->matrix[i][j] = (i == j) ? 0 : INF;
        }
    }
    return g;
}

void graph_destroy(Graph *g) {
    int i;
    if (!g) return;
    for (i = 0; i < g->n; i++)
        free(g->matrix[i]);
    free(g->matrix);
    free(g);
}

void graph_add_edge(Graph *g, int u, int v, int w) {
    if (u < 0 || u >= g->n || v < 0 || v >= g->n) return;
    g->matrix[u][v] = w;
}

Graph* graph_read_from_file(const char *filename) {
    FILE *f = fopen(filename, "r");
    Graph *g;
    int n, m, i, u, v, w;

    if (!f) {
        fprintf(stderr, "%s - not found\n", filename);
        return NULL;
    }

    if (fscanf(f, "%d %d", &n, &m) != 2) {
        fclose(f);
        return NULL;
    }

    g = graph_create(n);
    if (!g) {
        fclose(f);
        return NULL;
    }

    for (i = 0; i < m; i++) {
        if (fscanf(f, "%d %d %d", &u, &v, &w) != 3) {
            graph_destroy(g);
            fclose(f);
            return NULL;
        }
        graph_add_edge(g, u, v, w);
    }

    fclose(f);
    return g;
}

void graph_print(const Graph *g) {
    int i, j;
    printf("Matrix (%d x %d):\n", g->n, g->n);
    for (i = 0; i < g->n; i++) {
        for (j = 0; j < g->n; j++) {
            if (g->matrix[i][j] >= INF)
                printf("%6s", "INF");
            else
                printf("%6d", g->matrix[i][j]);
        }
        printf("\n");
    }
}
