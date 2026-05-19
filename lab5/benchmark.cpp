#include <benchmark/benchmark.h>

#include "floyd.h"
#include "graph.h"
#include "result.h"

static Graph *createBenchmarkGraph(int vertices, int edges) {
    Graph *g = graph_create(vertices);
    if (!g) {
        return nullptr;
    }

    int addedEdges = 0;
    for (int i = 0; i + 1 < vertices && addedEdges < edges; i++) {
        graph_add_edge(g, i, i + 1, 1);
        addedEdges++;
    }

    for (int from = 0; from < vertices && addedEdges < edges; from++) {
        for (int to = 0; to < vertices && addedEdges < edges; to++) {
            if (from != to && g->matrix[from][to] >= INF) {
                int weight = (from * 11 + to * 10) % 100 + 1;
                graph_add_edge(g, from, to, weight);
                addedEdges++;
            }
        }
    }

    return g;
}

static void BM_FloydWarshall(benchmark::State& state) {
    int vertices = static_cast<int>(state.range(0));
    int edges = static_cast<int>(state.range(1));
    Graph *g = createBenchmarkGraph(vertices, edges);

    if (!g) {
        state.SkipWithError("Failed to create graph for benchmark");
        return;
    }

    for (auto _ : state) {
        Result *r = floyd_warshall(g);
        if (!r) {
            state.SkipWithError("Failed to allocate result");
            break;
        }
        benchmark::DoNotOptimize(r->dist);
        result_destroy(r);
    }

    state.SetComplexityN(vertices);
    graph_destroy(g);
}

BENCHMARK(BM_FloydWarshall)
    ->Args({10, 30})
    ->Args({25, 125})
    ->Args({50, 500})
    ->Args({75, 1125})
    ->Args({100, 2500})
    ->Args({150, 5000})
    ->Args({200, 10000})
    ->ArgNames({"vertices", "edges"})
    ->Complexity(benchmark::oNCubed);

BENCHMARK_MAIN();
