#include <gtest/gtest.h>

#include <algorithm>
#include <graph/graph.hpp>
#include <ranges>
#include <vector>

class DirectedGraphTest : public ::testing::Test {
protected:
    void SetUp() override {
        graph.add_edge(0, 1);
        graph.add_edge(1, 2);
        graph.add_edge(0, 2);
        // Self-looping for funzies?
        graph.add_edge(3, 3);
    }

    graph::DirectedGraph graph;
};

TEST_F(DirectedGraphTest, HasEdges)
{
    EXPECT_EQ(graph.node_count(), 4);
    EXPECT_EQ(graph.edge_count(), 4);

    EXPECT_TRUE(graph.has_edge(0, 1));
    EXPECT_TRUE(graph.has_edge(1, 2));
    EXPECT_TRUE(graph.has_edge(0, 2));
    EXPECT_TRUE(graph.has_edge(3, 3));
    EXPECT_FALSE(graph.has_edge(2, 0));
    EXPECT_FALSE(graph.has_edge(1, 0));
}

TEST_F(DirectedGraphTest, Successors)
{
    auto successors_0 = graph.successors(0);
    std::vector<graph::NodeID> succ_0_vec(successors_0.begin(), successors_0.end());

    std::ranges::sort(succ_0_vec);

    EXPECT_EQ(succ_0_vec, std::vector<graph::NodeID>({1, 2}));

    auto successors_1 = graph.successors(1);
    std::vector<graph::NodeID> succ_1_vec(successors_1.begin(), successors_1.end());

    EXPECT_EQ(succ_1_vec, std::vector<graph::NodeID>({2}));
}

TEST_F(DirectedGraphTest, RemoveEdge)
{
    graph.remove_edge(0, 2);
    EXPECT_FALSE(graph.has_edge(0, 2));
    EXPECT_EQ(graph.edge_count(), 3);
}

TEST_F(DirectedGraphTest, View)
{
    auto nodes = graph.nodes();
    std::vector<graph::NodeID> nodes_vec(nodes.begin(), nodes.end());

    std::ranges::sort(nodes_vec);

    EXPECT_EQ(nodes_vec, std::vector<graph::NodeID>({0, 1, 2, 3}));
}

// TEST_F(DirectedGraphTest, CompiledGraphAndViews) {
//     // Compile the graph
//     auto compiled = graph.compile();

//     // Test compiled graph properties
//     EXPECT_EQ(compiled.node_count(), 4);
//     EXPECT_EQ(compiled.edge_count(), 4);

//     // Test compiled graph edge existence
//     EXPECT_TRUE(compiled.has_edge(0, 1));
//     EXPECT_TRUE(compiled.has_edge(1, 2));
//     EXPECT_TRUE(compiled.has_edge(0, 2));
//     EXPECT_TRUE(compiled.has_edge(3, 3));
//     EXPECT_FALSE(compiled.has_edge(2, 0));

//     // Test compiled successors (should be sorted)
//     auto compiled_successors_0 = compiled.successors(0);
//     std::vector<graph::NodeID> comp_succ_0_vec(compiled_successors_0.begin(), compiled_successors_0.end());
//     EXPECT_EQ(comp_succ_0_vec, std::vector<graph::NodeID>({1, 2}));  // Already sorted

//     // Test out_degree
//     EXPECT_EQ(compiled.out_degree(0), 2);
//     EXPECT_EQ(compiled.out_degree(1), 1);
//     EXPECT_EQ(compiled.out_degree(2), 0);
//     EXPECT_EQ(compiled.out_degree(3), 1);

//     // Test DFS traversal view
//     std::vector<graph::NodeID> dfs_traversal = compiled | graph::view::dfs_view(0);
//     std::vector<graph::NodeID> dfs_vec(dfs_traversal.begin(), dfs_traversal.end());
//     // DFS from 0 should visit 0, then either 1 or 2, then the remaining reachable
//     // node
//     EXPECT_EQ(dfs_vec.size(), 3);  // Should visit 0, 1, 2
//     EXPECT_EQ(dfs_vec[0], 0);      // Should start with 0
//     EXPECT_TRUE(std::ranges::find(dfs_vec, 1) != dfs_vec.end());
//     EXPECT_TRUE(std::ranges::find(dfs_vec, 2) != dfs_vec.end());

//     // Test BFS traversal view
//     auto bfs_traversal = compiled | graph::view::bfs_view(0);
//     std::vector<graph::NodeID> bfs_vec(bfs_traversal.begin(), bfs_traversal.end());
//     EXPECT_EQ(bfs_vec.size(), 3);  // Should visit 0, 1, 2
//     EXPECT_EQ(bfs_vec[0], 0);      // Should start with 0

//     // Test topological sort
//     auto topo_sort = compiled | graph::view::topological_view(compiled);
//     EXPECT_TRUE(topo_sort.is_valid());  // Should be valid (no cycles except self-loop)

//     std::vector<graph::NodeID> topo_vec(topo_sort.begin(), topo_sort.end());
//     // In a valid topological order, 0 should come before 1, and 1 should come
//     // before 2
//     auto pos_0 = std::ranges::find(topo_vec, 0) - topo_vec.begin();
//     auto pos_1 = std::ranges::find(topo_vec, 1) - topo_vec.begin();
//     auto pos_2 = std::ranges::find(topo_vec, 2) - topo_vec.begin();

//     EXPECT_LT(pos_0, pos_1);  // 0 should come before 1
//     EXPECT_LT(pos_1, pos_2);  // 1 should come before 2

//     // Test pipe operator syntax
//     auto topo_pipe = compiled | graph::view::topological_view;
//     std::vector<graph::NodeID> topo_pipe_vec(topo_pipe.begin(), topo_pipe.end());
//     EXPECT_EQ(topo_vec, topo_pipe_vec);  // Should be the same result

//     // Test edges view
//     auto edges = compiled.edges();
//     std::vector<graph::Edge> edges_vec(edges.begin(), edges.end());
//     EXPECT_EQ(edges_vec.size(), 4);

//     // Verify specific edges exist
//     EXPECT_TRUE(std::ranges::any_of(edges_vec, [](const graph::Edge &e) { return e.from == 0 && e.to == 1; }));
//     EXPECT_TRUE(std::ranges::any_of(edges_vec, [](const graph::Edge &e) { return e.from == 1 && e.to == 2; }));
//     EXPECT_TRUE(std::ranges::any_of(edges_vec, [](const graph::Edge &e) { return e.from == 0 && e.to == 2; }));
//     EXPECT_TRUE(std::ranges::any_of(edges_vec, [](const graph::Edge &e) { return e.from == 3 && e.to == 3; }));
// }