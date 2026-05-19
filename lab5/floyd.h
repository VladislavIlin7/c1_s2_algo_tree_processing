#ifndef FLOYD_H
#define FLOYD_H

#include "graph.h"
#include "result.h"

#ifdef __cplusplus
extern "C" {
#endif

Result* floyd_warshall(const Graph *g);

#ifdef __cplusplus
}
#endif

#endif
