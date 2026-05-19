#ifndef RESULT_H
#define RESULT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int n;
    int **dist;
    int **next;
} Result;

Result* result_create(int n);

void result_destroy(Result *r);

void result_print_distances(const Result *r);

void result_print_path(const Result *r, int u, int v);

void result_save_to_file(const Result *r, const char *filename);

int result_has_negative_cycle(const Result *r);

#ifdef __cplusplus
}
#endif

#endif
