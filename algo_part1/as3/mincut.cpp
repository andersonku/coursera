#include <iostream>
#include <iterator>
#include <fstream>
#include <algorithm> // for std::copy
#include <sstream>
#include <string>
#include "mincut.h"
#include <cstdlib>

using namespace std;

Graph ReadFile(char* fname) {
  Graph graph;
  string line;
  std::ifstream is(fname);
  while (std::getline(is, line)) {
    std::istringstream iss(line);
    int node;
    iss >> node;
    std::istream_iterator<int> start(iss), end;
    vector<int> connectedTo(start, end);
    graph[node] = connectedTo;
  }
  return graph;
}

void PrintGraph(const Graph& g) {
  for (Graph::const_iterator it = g.begin(); it != g.end(); ++it) {
    cout << it->first << endl;
    for (vector<int>::const_iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
      cout << "   " << *it2 << endl;
    }
  }
}

Graph Collapse(Graph& g, Node from, Node to) {
  if(g.size() < 2) {
    return g;
  }

  Node maxNode = max(from, to);
  Node minNode = min(from, to);
  Graph::iterator maxEntry = g.find(max(from, to));
  Graph::iterator minEntry = g.find(min(from, to));
  AdjacentList& maxList = maxEntry->second;
  AdjacentList& minList = minEntry->second;

  maxList.erase(remove(maxList.begin(), maxList.end(), minNode), maxList.end());
  minList.erase(remove(minList.begin(), minList.end(), maxNode), minList.end());
  minList.insert(minList.end(), maxList.begin(), maxList.end());

  g.erase(maxNode);
  for (Graph::iterator it = g.begin(); it != g.end(); ++it) {
    replace(it->second.begin(), it->second.end(), maxNode, minNode);
  }
  return g;
}

Graph CollapseToTwo (Graph g)
{
  if (g.size() < 3)
    return g;
  int seed = rand() % g.size();
  Graph::iterator myEntry = g.begin();
  advance(myEntry, seed);
  seed = rand() % myEntry->second.size();
  return CollapseToTwo(Collapse(g, myEntry->first, myEntry->second[seed]));
}


//int bmain(int, char** argv) {
  //Graph* finalGraph = CollapseToTwo(input);
  //cout << "Min cut = " << finalGraph.second.size() << endl;
  /* std::ifstream is(argv[1]);
  std::istream_iterator<int> start(is), end;
  std::vector<int> numbers(start, end);
  std::cout << "Read " << numbers.size() << " numbers" << std::endl;
  Graph graph = ReadFile(argv[1]);
  PrintGraph(graph);
  // std::cout << "numbers read in:\n";
  // std::copy(numbers.begin(), numbers.end(),
  //           std::ostream_iterator<int>(std::cout, " "));
  // std::cout << std::endl;

  // cout << "Count = " << count << endl;*/
//}
