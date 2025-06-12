#pragma once

#include <graph/graph.hpp>
#include <sstream>

namespace graph
{

template <DirectedGraphLike G>
std::string to_dot(const G& g, std::string_view graph_name = "G") {
    std::ostringstream out;
    out << "digraph " << graph_name << " {\n";

    for (NodeID node : g.nodes()) {
        out << "    " << node << ";\n";
    }

    for (NodeID from : g.nodes()) {
        for (NodeID to : g.successors(from)) {
            out << "    " << from << " -> " << to << ";\n";
        }
    }

    out << "}\n";
    return out.str();
}

}