#include "graph.h"
#include "shortest_path.h"
//Included myself
#include "heap.hpp"
#include <limits.h>

//Path shortestPath(const Graph& g, int source, int dest) {
//    vector<int> path;
//    vector<int> distance(g.num_vertices(), 99999999); // Initialize distances to infinity
//    distance[source] = 0;
//    vector<bool> visited(g.num_vertices(), false); // Vector to track visited vertexes
//    vector<int> parent(g.num_vertices(), -1); // Vector to track parent vertex
//
//    // Initialise heap
//    Heap<GraphEdge> extract;
//    extract.insert(GraphEdge(source, 0));
//
//
//    while (!extract.empty()) {
//        GraphEdge current = extract.extractMax();
//        int current_vertex = current.dest();
//        int current_distance = current.weight();
//
//        if (current_vertex == dest) {
//            int shortest_distance = distance[dest];
//            int vertex = dest;
//            while (vertex != -1) {
//                path.push_back(vertex);
//                vertex = parent[vertex];
//            }
//            reverse(path.begin(), path.end());
// 
//            return Path(shortest_distance, path);
//        }
//
//        visited[current_vertex] = true;
//
//        // Relax edges
//        forward_list<GraphEdge> edges = g.edges_from(current_vertex);
//        for (const GraphEdge& edge : edges) {
//            int destination = edge.dest();
//            int new_distance = edge.weight() + current_distance;
//            if (new_distance < distance[destination] && !visited[destination]) {
//                parent[destination] = current_vertex;
//                distance[destination] = new_distance;
//                extract.insert(GraphEdge(destination, new_distance));
//            }
//        }
//    }
//    // No shortest distance
//    throw std::out_of_range("Shortest path does not exist!");
//   /* return Path(0, path);*/
//}



Path shortestPath(const Graph& g, int source, int dest) {
    g.print();
    vector<int> path;
    vector<int> distance(g.num_vertices(), 99999999); // Initialize distances to infinity
    distance[source] = 0;
    vector<int> parent(g.num_vertices(), -1); // Vector to track parent vertex

    // Initialize max heap
    Heap<GraphEdge> extract;
    extract.insert(GraphEdge(source, 0));

    while (!extract.empty()) {
        GraphEdge current = extract.extractMax();
        int current_vertex = current.dest();
        int current_distance = current.weight();

        if (current_vertex == dest) {
            int shortest_distance = distance[dest];
            int vertex = dest;
            while (vertex != -1) {
                path.push_back(vertex);
                vertex = parent[vertex];
            }
            reverse(path.begin(), path.end());

            return Path(shortest_distance, path);
        }

        // Relax edges
        forward_list<GraphEdge> edges = g.edges_from(current_vertex);
        for (const GraphEdge& edge : edges) {
            int destination = edge.dest();
            int new_distance = edge.weight() + current_distance;
            if (new_distance < distance[destination]) {
                parent[destination] = current_vertex;
                distance[destination] = new_distance;
                extract.insert(GraphEdge(destination, new_distance));
            }
        }
    }
    // No shortest distance
    throw std::out_of_range("Shortest path does not exist!");
}



