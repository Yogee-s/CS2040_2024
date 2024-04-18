#include <gtest/gtest.h>

#include <utility>

#include "graph.h"
#include "shortest_path.h"
#include <gtest/gtest.h>

#include <utility>

#include "graph.h"
#include "shortest_path.h"

using namespace std;

Graph createSimpleGraph() {
  Graph g(4);
  g.addEdge(0, 1, 1);
  g.addEdge(0, 2, 2);
  g.addEdge(1, 3, 5);
  g.addEdge(2, 3, 1);
  return g;
}

Graph createComplexGraph() {
  Graph g(8);
  g.addEdge(0, 1, 5);
  g.addEdge(0, 7, 8);
  g.addEdge(0, 4, 9);
  g.addEdge(1, 3, 15);
  g.addEdge(1, 2, 12);
  g.addEdge(1, 7, 4);
  g.addEdge(3, 6, 9);
  g.addEdge(2, 3, 3);
  g.addEdge(2, 6, 11);
  g.addEdge(4, 7, 5);
  g.addEdge(4, 5, 4);
  g.addEdge(4, 6, 20);
  g.addEdge(5, 2, 1);
  g.addEdge(5, 6, 13);
  g.addEdge(7, 5, 6);
  g.addEdge(7, 2, 7);
  return g;
}

Graph createtrainGraph() {
    Graph g(10);
    g.addEdge(0, 2, 173);
    g.addEdge(0, 4, 170);
    g.addEdge(0, 5, 108);
    g.addEdge(0, 9, 46);
    g.addEdge(1, 4, 58);
    g.addEdge(1, 6, 97);
    g.addEdge(2, 0, 67);
    g.addEdge(2, 1, 62);
    g.addEdge(2, 7, 135);
    g.addEdge(3, 8, 199);
    g.addEdge(4, 1, 63);
    g.addEdge(4, 7, 62);
    g.addEdge(4, 8, 62);
    g.addEdge(5, 4, 105);
    g.addEdge(5, 6, 45);
    g.addEdge(5, 7, 152);
    g.addEdge(5, 9, 170);
    g.addEdge(6, 0, 112);
    g.addEdge(6, 4, 193);
    g.addEdge(6, 9, 26);
    g.addEdge(7, 2, 80);
    g.addEdge(9, 1, 75);
    g.addEdge(9, 2, 25);
    g.addEdge(9, 3, 195);
    g.addEdge(9, 5, 192);
    return g;
}

class ShortestPathParamTest
    : public testing::TestWithParam<tuple<Graph, int, int, int, vector<int>>> {
};

TEST_P(ShortestPathParamTest, test_public_shortest_path_example) {
  Graph g(0);
  int src, dest, expected_distance;
  vector<int> expected_path;
  tie(g, src, dest, expected_distance, expected_path) = GetParam();
  Path p = shortestPath(g, src, dest);

  //Print path
  for (int i = 0; i < p.path().size(); i++) {
      std::cout << "Path is: " << p.path()[i] << "\n";

  }

  EXPECT_EQ(p.total_distance(), expected_distance);
  ASSERT_EQ(p.path().size(), expected_path.size());
  for (int i = 0; i < p.path().size(); i++) {
    EXPECT_EQ(p.path()[i], expected_path[i]);
  }
}

INSTANTIATE_TEST_CASE_P(
    PublicTestValues, ShortestPathParamTest,
    testing::Values(make_tuple(createSimpleGraph(), 0, 1, 1, vector<int>{0, 1}),
                    make_tuple(createSimpleGraph(), 0, 2, 2, vector<int>{0, 2}),
                    make_tuple(createSimpleGraph(), 0, 3, 3,
                               vector<int>{0, 2, 3}),
                    make_tuple(createSimpleGraph(), 1, 3, 5, vector<int>{1, 3}),
                    make_tuple(createComplexGraph(), 0, 6, 25,
                               vector<int>{0, 4, 5, 2, 6}),

                    make_tuple(createtrainGraph(), 5, 3, 0,
                        vector<int>{0})));


                    
