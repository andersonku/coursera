#include "gtest/gtest.h"
#include "graph.h"

using namespace std;

TEST(ReadFromFile, 1) {
  Heap h(100);
  EXPECT_EQ(h.toString(), "");
  h.insert(100);
  EXPECT_EQ(h.toString(), "100 ");
  h.insert(20);
  EXPECT_EQ(h.toString(), "20 100 ");
  h.insert(10);
  EXPECT_EQ(h.toString(), "10 20 100 ");
  h.insert(5);
  EXPECT_EQ(h.toString(), "5 10 20 100 ");
}
