#include <algorithm>
#include "gtest/gtest.h"
#include "mincut.h"
using namespace std;

TEST(Collapse, 0) {
   Graph graph;
   graph.CollapseBigIntoSmall(0, 0);
   EXPECT_EQ(graph._nodes.size(), 0);
}

TEST(Collapse, 1) {
   Graph graph;
   graph._nodes[0] = std::vector<int>();
   graph.CollapseBigIntoSmall(0, 0);
   EXPECT_EQ(graph._nodes.size(), 1);
}

TEST(Collapse, 2) {
   Graph graph;
   Graph::AdjacentList list0;
   list0.push_back(1);
   graph._nodes[0] = list0;
   Graph::AdjacentList list1;
   list1.push_back(0);
   graph._nodes[1] = list1;
   graph.CollapseBigIntoSmall(0, 1);
   EXPECT_EQ(graph._nodes.size(), 1);
   EXPECT_EQ(graph._nodes[0].size(), 0);
}

TEST(Collapse, 3_1) {
   Graph graph;
   Graph::AdjacentList list0;
   list0.push_back(1);
   graph._nodes[0] = list0;
   Graph::AdjacentList list1;
   list1.push_back(0);
   list1.push_back(2);
   graph._nodes[1] = list1;
   Graph::AdjacentList list2;
   list2.push_back(1);
   graph._nodes[2] = list2;

   graph.CollapseBigIntoSmall(0, 1);
   ASSERT_EQ(graph._nodes.size(), 2);
   EXPECT_EQ(graph._nodes[0].size(), 1);
   EXPECT_EQ(graph._nodes[0][0], 2);
   EXPECT_EQ(graph._nodes[2].size(), 1);
   EXPECT_EQ(graph._nodes[2][0], 0);
}

TEST(Collapse, 3_2) {
   Graph graph;
   Graph::AdjacentList list0;
   list0.push_back(1);
   list0.push_back(2);
   graph._nodes[0] = list0;
   Graph::AdjacentList list1;
   list1.push_back(0);
   list1.push_back(2);
   graph._nodes[1] = list1;
   Graph::AdjacentList list2;
   list2.push_back(0);
   list2.push_back(1);
   graph._nodes[2] = list2;

   graph.CollapseBigIntoSmall(0, 1);
   ASSERT_EQ(graph._nodes.size(), 2);
   EXPECT_EQ(graph._nodes[0].size(), 2);
   EXPECT_EQ(graph._nodes[0][0], 2);
   EXPECT_EQ(graph._nodes[0][1], 2);
   EXPECT_EQ(graph._nodes[2].size(), 2);
   EXPECT_EQ(graph._nodes[2][0], 0);
   EXPECT_EQ(graph._nodes[2][1], 0);
}

TEST(MyMain, Hahaha) {
   Graph graph;
   graph.ReadFile("kargerMinCut.txt");
   vector<int> result;
   for (int i = 0; i < 10; ++i) {
      Graph beginGraph = graph;
      beginGraph.CollapseToTwo();
      result.push_back(beginGraph._nodes.begin()->second.size());
   }
   sort(result.begin(), result.end());
   EXPECT_EQ(result[0], 17);
   cout << "Min of Min Cut = " << result[0] << endl;
}
