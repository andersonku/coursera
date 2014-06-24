#include "gtest/gtest.h"
#include "graph.h"

using namespace std;

TEST(ReadFromFile, 0) {
   Graph simple;
   simple.ReadFromFile("simple.txt");
   EXPECT_EQ(simple.nodes.size(), 3);

   vector<int> result = SCC(simple);
   EXPECT_EQ(result.size(), 5);
   EXPECT_EQ(result[0], 3);
   EXPECT_EQ(result[1], 0);
   EXPECT_EQ(result[2], 0);
   EXPECT_EQ(result[3], 0);
   EXPECT_EQ(result[4], 0);

   Graph test;
   test.ReadFromFile("test.txt");
   result = SCC(test);
   EXPECT_EQ(result.size(), 5);
   EXPECT_EQ(result[0], 6);
   EXPECT_EQ(result[1], 3);
   EXPECT_EQ(result[2], 2);
   EXPECT_EQ(result[3], 1);
   EXPECT_EQ(result[4], 0);

   Graph g4;
   g4.ReadFromFile("SCC.txt");
   result = SCC(g4);
   EXPECT_EQ(result.size(), 5);
   EXPECT_EQ(result[0], 434821);
   EXPECT_EQ(result[1], 968);
   EXPECT_EQ(result[2], 459);
   EXPECT_EQ(result[3], 313);
   EXPECT_EQ(result[4], 211);
}
