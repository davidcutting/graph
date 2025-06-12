#include <benchmark/benchmark.h>
#include <graph/graph.hpp>

// static void BM_AddEdges(benchmark::State& state) {
//     for (auto _ : state) {
//         graph::DirectedGraph g;
//         for (graph::NodeID i = 0; i < state.range(0); ++i)
//             g.add_edge(i, (i + 1) % state.range(0));
//         benchmark::DoNotOptimize(g);
//     }
// }
// BENCHMARK(BM_AddEdges)->Range(8, 1 << 15);

static void BM_CompileGraph(benchmark::State& state) {
    graph::DirectedGraph g;
    for (graph::NodeID i = 0; i < state.range(0); ++i)
        g.add_edge(i, (i + 1) % state.range(0));
    for (auto _ : state) {
        auto compiled = g.compile();
        benchmark::DoNotOptimize(compiled);
    }
}
BENCHMARK(BM_CompileGraph)->Range(8, 1 << 15);

BENCHMARK_MAIN();