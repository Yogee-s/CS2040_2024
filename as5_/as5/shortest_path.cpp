#include "graph.h"
#include "shortest_path.h"
//Included myself
#include "heap.hpp"


Path shortestPath(const Graph& g, int source, int dest) {
    vector<int> path;
    vector<int> distance(g.num_vertices(), 99999999); // Initialize distances to infinity
    distance[source] = 0;
    vector<int> parent(g.num_vertices(), -1); // Vector to track parent vertex

    // Initialize max heap
    Heap<GraphEdge> extract;
    extract.insert(GraphEdge(source, 0));

    //If destination does not exist
    if (dest < 0 || dest >= g.num_vertices()) {
        throw std::out_of_range("Destination doesn't exist!");
    }

    while (!extract.empty()) {
        GraphEdge current = extract.extractMax();
        int current_vertex = current.dest();

        forward_list<GraphEdge> edges = g.edges_from(current_vertex);
        for (const GraphEdge& edge : edges) {
            int destination = edge.dest();
            int new_distance = edge.weight() + distance[current_vertex];
            // Update distance and heap if a shorter path is found
            if (new_distance < distance[destination]) {
                parent[destination] = current_vertex;
                distance[destination] = new_distance;
                // Insert only if the new distance is less than the current distance stored in the distance array
                extract.insert(GraphEdge(destination, new_distance));
            }
        }
    }

    // Constructing the path
    int path_vertex = dest;
    while (path_vertex != -1) {
        path.push_back(path_vertex);
        path_vertex = parent[path_vertex];
    }
    reverse(path.begin(), path.end());


    //No shortest distance
    if (distance[dest] == 99999999) {
        throw std::out_of_range("Shortest path does not exist!");
    }

    return Path(distance[dest], path);
}