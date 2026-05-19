#include "floyd.h"
#include <stdlib.h>

Result* floyd_warshall(const Graph *g) {
    int n = g->n;
    int i, j, k;
    Result *r = result_create(n);
    if (!r) return NULL;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            r->dist[i][j] = g->matrix[i][j];
            if (g->matrix[i][j] < INF && i != j)
                r->next[i][j] = j;
            else if (i == j)
                r->next[i][j] = i;
            else
                r->next[i][j] = -1;
        }
    }

    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (r->dist[i][k] < INF && r->dist[k][j] < INF) {
                    if (r->dist[i][k] + r->dist[k][j] < r->dist[i][j]) {
                        r->dist[i][j] = r->dist[i][k] + r->dist[k][j];
                        r->next[i][j] = r->next[i][k];
                    }
                }
            }
        }
    }

    return r;
}
