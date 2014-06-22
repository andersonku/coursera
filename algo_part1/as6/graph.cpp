#include <iostream>
#include <iterator>
#include <fstream>
#include <algorithm> // for copy
#include <sstream>
#include "graph.h"
#include <cstdlib>
#include <map>

using namespace std;

void Heap::insert(const int key) {
  size_t pos = size;
  items[size++] = key;

  while (pos != 0) {
    int& item   = items[pos];
    int& parent = items[(pos-1)/2];
    if (item > parent)
      return;
    swap(item, parent);
    pos /= 2;
  }
}

string Heap::toString() {
  ostringstream oss;
  for(size_t i = 0; i < size; ++i) {
    oss << items[i] << " ";
  }
  return oss.str();
}


string Node::ToString() {
  ostringstream oss;
  oss << "key[" << key << "] " << shortestDist;
  for (AdjacentList::iterator it = edges.begin(); it != edges.end(); ++it) {
    oss << " (" << it->key << ", " << it->dist << ") ";
  }
  oss << endl;
  return oss.str();
}

void DSPathVect::ReadFromFile(const string& fname) {
  string line;
  ifstream is(fname.c_str());
  while (getline(is, line)) {
    istringstream iss(line);
    int key;
    iss >> key;
    Node myNode(key);
    while (iss)
    {
      string s;
      if(!getline(iss, s, ','))
        break;
      int edgeHead, dist;
      edgeHead = atoi(s.c_str());
      if (edgeHead == 0) break;
      iss >> dist;
      Edge myEdge(edgeHead, dist);
      myNode.edges.push_back(myEdge);
    }
    nodes.push_back(myNode);
  }
}

void DSPathVect::computeDist(const int s) {
  map<int,Node*> processedNodes;
  nodes[s-1].shortestDist = 0;
  processedNodes.insert(make_pair(s, &nodes[s-1]));
  while (processedNodes.size() != nodes.size())
  {
    int minGScore = INF;
    Node* minNode = NULL;
    for (map<int,Node*>::iterator v = processedNodes.begin(); v != processedNodes.end(); ++v) {
      for (Node::AdjacentList::iterator e = v->second->edges.begin(); e != v->second->edges.end(); ++e) {
        if ( processedNodes.find(e->key) == processedNodes.end() ) {
          // compute min
          int gScore = v->second->shortestDist + e->dist;
          if ( gScore < minGScore ) {
            minGScore = gScore;
            minNode = &nodes[e->key - 1];
          }
        }
      }
    }
    processedNodes.insert(make_pair(minNode->key, &nodes[minNode->key - 1]));
    minNode->shortestDist = minGScore;
  }
}

string DSPathVect::ToString() {
  ostringstream oss;
  for ( vector<Node>::iterator it = nodes.begin(); it != nodes.end(); ++it)  {
    oss << it->ToString();
  }
  return oss.str();
}
