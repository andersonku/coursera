#include "gtest/gtest.h"
#include "graph.h"

using namespace std;

TEST(ReadFromFile, 1) {
  DSPathVect simple;
  simple.ReadFromFile("test1.txt");
  simple.computeDist(1);
  cout << simple.ToString() << endl;
}

TEST(ReadFromFile, Big) {
  DSPathVect simple;
  simple.ReadFromFile("dijkstraData.txt");
  simple.computeDist(1);
  //cout << simple.ToString() << endl;
  vector<int> vs = {7,37,59,82,99,115,133,165,188,197};
  for (auto i : vs) {
    cout << simple.nodes[i-1].shortestDist << ",";
  }
  cout << endl;
  //EXPECT_EQ(simple.nodes.size(), 3);


}
