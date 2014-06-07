#include "gtest/gtest.h"
#include "graph.h"

using namespace std;

TEST(ReadFromFile, 0) {
  Graph g;
  g.ReadFromFile("simple.txt");
  EXPECT_EQ(g.nodeList.size(), 3);
  cout << g.ToString();
  Graph reversed = g.Reverse();
  reversed.DFS_Loop();
  cout << reversed.ToString();
  Graph finished = reversed.FinishTimeToKey();
  cout << finished.ToString();
  Graph lastOne = finished.Reverse();
  lastOne.DFS_Loop();
  cout << lastOne.ToString();

  Graph g2;
  g2.ReadFromFile("simple.txt");
  cout << SSC(g2).ToString();

  cout << endl << endl;

  Graph g3;
  g3.ReadFromFile("test.txt");
  cout << SSC(g3).ToString();



  //Graph g4;
  //g4.ReadFromFile("SCC.txt");
  //g4.Reverse().DFS_Loop();
  //SSC(g4);
}

// TEST(MyMain, Hahaha) {
//   Graph graph = ReadFile("kargerMinCut.txt");
//   vector<int> result;
//   for(int i = 0; i < 10; ++i) {
//     Graph beginGraph = graph;
//     Graph finalGraph = CollapseToTwo(beginGraph);
//     cout << "Min cut = " << finalGraph.begin()->second.size() << endl;
//     result.push_back(finalGraph.begin()->second.size());
//   }
//   sort(result.begin(), result.end());
//   cout << "Min of Min Cut = " << result[0] << endl;

// }
