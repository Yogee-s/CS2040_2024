#include "graph.h"

#include <fstream>

using std::endl;

std::ostream& operator<<(std::ostream& os, GraphEdge const& e) {
  return os << " (d:" << e.dest() << " w:" << e.weight() << ")";
}

ostream& operator<<(ostream& os, const Graph& g) {
  for (int i = 0; i < g.num_vertices(); ++i) {
    os << "Vertex " << i << ": ";
    for (auto e : g.edges_from(i)) {
      os << e;
    }
    os << endl;
  }
  return os;
}

void Graph::addEdge(int source, int dest, int weight) {
  // Assumes that an edge doesn't already exist!
  _vertices[source].emplace_front(dest, weight);
}


// Implementation of print function
void Graph::print() const {
    std::cout << "Number of vertices: "<< num_vertices()<< "\n";
    for (int i = 0; i < num_vertices(); ++i) {
        std::cout << "Vertex " << i ;
        for (const auto& edge : _vertices[i]) {
            std::cout << " -> (" <<"d: " << edge.dest() << ", " << "w: " << edge.weight() << ")";
        }
        std::cout << std::endl;
    }
}