#include "result.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

Result* result_create(int n) {
    int i;
    Result *r = (Result*)malloc(sizeof(Result));
    if (!r) return NULL;

    r->n = n;
    r->dist = (int**)malloc(n * sizeof(int*));
    if (!r->dist) {
        free(r);
        return NULL;
    }

    r->next = (int**)malloc(n * sizeof(int*));
    if (!r->next) {
        free(r->dist);
        free(r);
        return NULL;
    }

    for (i = 0; i < n; i++) {
        r->dist[i] = NULL;
        r->next[i] = NULL;
    }

    for (i = 0; i < n; i++) {
        r->dist[i] = (int*)malloc(n * sizeof(int));
        if (!r->dist[i]) {
            result_destroy(r);
            return NULL;
        }

        r->next[i] = (int*)malloc(n * sizeof(int));
        if (!r->next[i]) {
            result_destroy(r);
            return NULL;
        }
    }
    return r;
}

void result_destroy(Result *r) {
    int i;
    if (!r) return;
    for (i = 0; i < r->n; i++) {
        free(r->dist[i]);
        free(r->next[i]);
    }
    free(r->dist);
    free(r->next);
    free(r);
}

void result_print_distances(const Result *r) {
    int i, j;
    printf("Shortest distances:\n");
    printf("     ");
    for (j = 0; j < r->n; j++) printf("%6d", j);
    printf("\n");

    for (i = 0; i < r->n; i++) {
        printf("%3d |", i);
        for (j = 0; j < r->n; j++) {
            if (r->dist[i][j] >= INF) printf("%6s", "INF");
            else printf("%6d", r->dist[i][j]);
        }
        printf("\n");
    }
}

void result_print_path(const Result *r, int u, int v) {
    if (r->dist[u][v] >= INF) {
        printf("%d -> %d: not found\n", u, v);
        return;
    }
    printf("%d -> %d, length = %d: %d", u, v, r->dist[u][v], u);
    while (u != v) {
        u = r->next[u][v];
        printf(" -> %d", u);
    }
    printf("\n");
}

void result_save_to_file(const Result *r, const char *filename) {
    FILE *f = fopen(filename, "w");
    int i, j;
    if (!f) return;
    fprintf(f, "%d\n", r->n);
    for (i = 0; i < r->n; i++) {
        for (j = 0; j < r->n; j++) {
            if (r->dist[i][j] >= INF) fprintf(f, "INF ");
            else fprintf(f, "%d ", r->dist[i][j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

int result_has_negative_cycle(const Result *r) {
    int i;
    for (i = 0; i < r->n; i++)
        if (r->dist[i][i] < 0) return 1;
    return 0;
}
