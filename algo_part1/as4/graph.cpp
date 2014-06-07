#include <iostream>
#include <iterator>
#include <fstream>
#include <algorithm> // for std::copy
#include <sstream>
#include "graph.h"
#include <cstdlib>

using namespace std;

Graph SSC(Graph& g){
  Graph pass1 = g.Reverse();
  pass1.DFS_Loop();
  Graph pass2 = pass1.FinishTimeToKey().Reverse();
  pass2.DFS_Loop();
  return pass2;
}

std::string Node::ToString() {
  ostringstream oss;
  oss << "[" << key << "][" << visited << "][" << finishTime << "][l" << (leader ? leader->key : -1) << "][";
  for (AdjacentList::iterator it = adjacentList.begin(); it != adjacentList.end(); ++it) {
    oss << *it << " ";
  }
  oss << "]" << endl;
  return oss.str();
}

void Graph::DFS_Loop() {
  finishTime = 0;
  leader = NULL;

  for (NodeList::reverse_iterator it = nodeList.rbegin(); it != nodeList.rend(); ++it) {
    if (!it->second.visited) {
      leader = &(it->second);
      DFS(it->second);
    }
  }
}

void Graph::DFS(Node& node) {
  node.visited = true;
  node.leader = leader;
  for (Node::AdjacentList::iterator it = node.adjacentList.begin(); it != node.adjacentList.end(); ++it) {
    Node& next = nodeList[*it];
    if(!next.visited) {
      DFS(next);
    }
  }
  ++finishTime;
  node.finishTime = finishTime;
}

Graph Graph::FinishTimeToKey() {
  Graph g;
  for (NodeList::iterator it = nodeList.begin(); it != nodeList.end(); ++it) {
    g.nodeList.insert(make_pair(it->second.finishTime, it->second));
    g.nodeList[it->second.finishTime].visited = false;
    g.nodeList[it->second.finishTime].key = it->second.finishTime;
  }
  return g;
}

Graph Graph::Reverse() {
  Graph g;
  for( NodeList::iterator it = nodeList.begin(); it != nodeList.end(); ++it) {
    int key = it->first;
    Node::AdjacentList& list = it->second.adjacentList;
    for( Node::AdjacentList::iterator it2 = list.begin(); it2 != list.end(); ++it2) {
      g.AddEdge(*it2,key);
    }
  }
  return g;
}

void Graph::AddEdge(int tail, int head) {
  if (nodeList.find(tail) == nodeList.end()) {
    nodeList.insert(make_pair(tail, Node(tail)));
  }
  nodeList[tail].adjacentList.push_back(head);
}

void Graph::ReadFromFile(const string& fname) {
  string line;
  std::ifstream is(fname.c_str());
  while (std::getline(is, line)) {
    std::istringstream iss(line);
    int tail, head;
    iss >> tail;
    iss >> head;
    AddEdge(tail, head);
  }
}

std::string Graph::ToString() {
  ostringstream oss;
  for (NodeList::iterator it = nodeList.begin(); it != nodeList.end(); ++it) {
    oss << it->second.ToString();
  }
  return oss.str();
}
