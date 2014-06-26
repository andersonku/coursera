#include <iostream>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include "mincut.h"

using namespace std;

void Graph::ReadFile(char* fname) {
   string line;
   std::ifstream is(fname);
   while (std::getline(is, line)) {
      std::istringstream iss(line);
      int node;
      iss >> node;
      std::istream_iterator<int> start(iss), end;
      _nodes[node] = vector<int>(start, end);
   }
}

void RemoveThenErase(Graph::AdjacentList& list, int value) {
   list.erase(remove(list.begin(), list.end(), value), list.end());
}

void Graph::CollapseBigIntoSmall(int from, int to) {
   Collapse(max(from, to), min(from, to));
}

// Collpse two node into one
void Graph::Collapse(int from, int to) {
   if (_nodes.size() < 2)
      return;   // Cannot be collapsed anymore

   // Merge two adjacency list and remove the from node
   _nodes[to].insert(_nodes[to].end(), _nodes[from].begin(), _nodes[from].end());
   _nodes.erase(from);

   // Update the adjacency list to point to the merged node
   for (auto &node : _nodes) {
      replace(node.second.begin(), node.second.end(), from, to);
   }

   RemoveThenErase(_nodes[to], to);    // Remove edges pointing to self
}

int RandOutOf(int n) {
   return rand() % n;
}

void Graph::CollapseToTwo() {
   while (_nodes.size() > 2) {
      // Pick th first node to collapse
      auto myEntry = _nodes.begin();
      advance(myEntry, RandOutOf(_nodes.size()));

      // Pick the second node to collapse
      int seed = RandOutOf(myEntry->second.size());
      CollapseBigIntoSmall(myEntry->first, myEntry->second[seed]);
   }
}
