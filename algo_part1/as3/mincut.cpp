#include <iostream>
#include <iterator>
#include <fstream>
#include <algorithm> // for std::copy
#include <sstream>
#include <string>
#include "mincut.h"
#include <cstdlib>

using namespace std;

void Graph::ReadFile(char* fname) {
   string line;
   std::ifstream is(fname);
   while (std::getline(is, line)) {
      std::istringstream iss(line);
      int node;
      iss >> node;
      std::istream_iterator<int> start(iss), end;
      vector<int> connectedTo(start, end);
      _nodes[node] = connectedTo;
   }
}

void RemoveThenErase(Graph::AdjacentList& list, int value) {
   list.erase(remove(list.begin(), list.end(), value), list.end());
}

void Graph::CollpseBigIntoSmall(int from, int to) {
   Collapse(max(from, to), min(from, to));
}

// Collpse two node into one
void Graph::Collapse(int from, int to) {
   if (_nodes.size() < 2)
      return;   // Cannot be collapsed anymore

   AdjacentList& fromAdjacentList = _nodes.find(from)->second;
   AdjacentList& toAdjacentList = _nodes.find(to)->second;

   // Remove edges between the nodes
   RemoveThenErase(fromAdjacentList, to);
   RemoveThenErase(toAdjacentList, from);

   // Merge two adjacency list and remove the from node
   toAdjacentList.insert(toAdjacentList.end(), fromAdjacentList.begin(), fromAdjacentList.end());
   _nodes.erase(from);

   // Update the adjacency list of everyone else
   for (auto &node : _nodes) {
      replace(node.second.begin(), node.second.end(), from, to);
   }
}

int RandOutOf(int n) {
   return rand() % n;
}

void Graph::CollapseToTwo()
{
   if (_nodes.size() < 3)
      return;

   auto myEntry = _nodes.begin();
   advance(myEntry, RandOutOf(_nodes.size()));
   int seed = RandOutOf(myEntry->second.size());
   CollpseBigIntoSmall(myEntry->first, myEntry->second[seed]);
   CollapseToTwo();
}
