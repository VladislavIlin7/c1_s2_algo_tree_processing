#include <gtest/gtest.h>

#include "floyd.h"
#include "graph.h"
#include "result.h"

TEST(GraphTest, CreateInitializesMatrix) {
    Graph *g = graph_create(3);

    ASSERT_NE(g, nullptr);
    EXPECT_EQ(g->n, 3);
    EXPECT_EQ(g->matrix[0][0], 0);
    EXPECT_EQ(g->matrix[1][1], 0);
    EXPECT_EQ(g->matrix[2][2], 0);
    EXPECT_EQ(g->matrix[0][1], INF);
    EXPECT_EQ(g->matrix[1][2], INF);

    graph_destroy(g);
}

TEST(GraphTest, AddEdgeStoresDirectedWeight) {
    Graph *g = graph_create(3);
    ASSERT_NE(g, nullptr);

    graph_add_edge(g, 0, 2, 7);

    EXPECT_EQ(g->matrix[0][2], 7);
    EXPECT_EQ(g->matrix[2][0], INF);

    graph_destroy(g);
}

TEST(FloydWarshallTest, ComputesShortestDistances) {
    Graph *g = graph_create(5);
    ASSERT_NE(g, nullptr);

    graph_add_edge(g, 0, 1, 4);
    graph_add_edge(g, 0, 2, 1);
    graph_add_edge(g, 2, 1, 2);
    graph_add_edge(g, 1, 3, 1);
    graph_add_edge(g, 2, 3, 5);
    graph_add_edge(g, 3, 4, 3);
    graph_add_edge(g, 0, 4, 10);
    graph_add_edge(g, 4, 3, 2);

    Result *r = floyd_warshall(g);

    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->dist[0][1], 3);
    EXPECT_EQ(r->dist[0][3], 4);
    EXPECT_EQ(r->dist[0][4], 7);
    EXPECT_EQ(r->dist[2][4], 6);

    result_destroy(r);
    graph_destroy(g);
}

TEST(FloydWarshallTest, KeepsUnreachableVerticesAsInfinity) {
    Graph *g = graph_create(4);
    ASSERT_NE(g, nullptr);

    graph_add_edge(g, 0, 1, 5);
    graph_add_edge(g, 1, 2, 6);

    Result *r = floyd_warshall(g);

    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->dist[0][2], 11);
    EXPECT_EQ(r->dist[2][0], INF);
    EXPECT_EQ(r->dist[3][0], INF);

    result_destroy(r);
    graph_destroy(g);
}

TEST(FloydWarshallTest, DetectsNegativeCycle) {
    Graph *g = graph_create(3);
    ASSERT_NE(g, nullptr);

    graph_add_edge(g, 0, 1, 1);
    graph_add_edge(g, 1, 2, -3);
    graph_add_edge(g, 2, 0, 1);

    Result *r = floyd_warshall(g);

    ASSERT_NE(r, nullptr);
    EXPECT_TRUE(result_has_negative_cycle(r));

    result_destroy(r);
    graph_destroy(g);
}
