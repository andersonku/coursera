#include "gtest/gtest.h"
#include "mincut.h"
using namespace std;

TEST(Collapse, 0) {
  Graph input;
  Graph output = Collapse(input, 0, 0);
  EXPECT_EQ(input.size(), output.size());
  EXPECT_EQ(output.size(), 0);
}

TEST(Collapse, 1) {
  Graph input;
  input[0] = std::vector<int>();
  Graph output = Collapse(input, 0, 0);
  EXPECT_EQ(input.size(), output.size());
  EXPECT_EQ(output.size(), 1);
}

TEST(Collapse, 2) {
  Graph input;
  AdjacentList list0;
  list0.push_back(1);
  input[0] = list0;
  AdjacentList list1;
  list1.push_back(0);
  input[1] = list1;
  Graph output = Collapse(input, 0, 1);
  EXPECT_EQ(output.size(), 1);
  EXPECT_EQ(output[0].size(), 0);
}

TEST(Collapse, 3_1) {
  Graph input;
  AdjacentList list0;
  list0.push_back(1);
  input[0] = list0;
  AdjacentList list1;
  list1.push_back(0);
  list1.push_back(2);
  input[1] = list1;
  AdjacentList list2;
  list2.push_back(1);
  input[2] = list2;

  Graph output = Collapse(input, 0, 1);
  ASSERT_EQ(output.size(), 2);
  EXPECT_EQ(output[0].size(), 1);
  EXPECT_EQ(output[0][0], 2);
  EXPECT_EQ(output[2].size(), 1);
  EXPECT_EQ(output[2][0], 0);
}

TEST(Collapse, 3_2) {
  Graph input;
  AdjacentList list0;
  list0.push_back(1);
  list0.push_back(2);
  input[0] = list0;
  AdjacentList list1;
  list1.push_back(0);
  list1.push_back(2);
  input[1] = list1;
  AdjacentList list2;
  list2.push_back(0);
  list2.push_back(1);
  input[2] = list2;

  Graph output = Collapse(input, 0, 1);
  ASSERT_EQ(output.size(), 2);
  EXPECT_EQ(output[0].size(), 2);
  EXPECT_EQ(output[0][0], 2);
  EXPECT_EQ(output[0][1], 2);
  EXPECT_EQ(output[2].size(), 2);
  EXPECT_EQ(output[2][0], 0);
  EXPECT_EQ(output[2][1], 0);
}

TEST(MyMain, Hahaha) {
  Graph graph = ReadFile("kargerMinCut.txt");
  vector<int> result;
  for(int i = 0; i < 10; ++i) {
    Graph beginGraph = graph;
    Graph finalGraph = CollapseToTwo(beginGraph);
    cout << "Min cut = " << finalGraph.begin()->second.size() << endl;
    result.push_back(finalGraph.begin()->second.size());
  }
  sort(result.begin(), result.end());
  cout << "Min of Min Cut = " << result[0] << endl;

}
