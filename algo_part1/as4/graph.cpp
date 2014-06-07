#include <iostream>
#include <iterator>
#include <fstream>
#include <algorithm> // for std::copy
#include <sstream>
#include "graph.h"
#include <cstdlib>
#include <map>

using namespace std;

Graph SCC(Graph& g){
  Graph pass1 = g.Reverse();
  vector<Node*> order = pass1.DFS_Loop();
  Graph pass2 = pass1.Reverse();
  pass2.DFS_Loop2(order);

  vector<int> result = pass2.GetTopFive();
  for(int i = 1; i <= 5 && i <= result.size(); ++i) {
    cout << result[result.size() - i ] << endl;
  }
  return pass2;
}

vector<int> Graph::GetTopFive() {
  map<Node*,int> scc;
  for (NodeList::iterator it = nodes.begin(); it != nodes.end(); ++it) {
    if(scc.find(it->leader) == scc.end()) {
      scc[it->leader] = 1;
    } else {
      ++scc[it->leader];
    }
  }

  vector<int> result;
  for (map<Node*,int>::iterator it = scc.begin(); it != scc.end(); ++it) {
    result.push_back(it->second);
  }
  sort(result.begin(), result.end());
  //  upper_bound(result.begin(), result.end(), 5);
  return result;
}

bool sortByFinishTime(Node& a, Node& b){
  return a.finishTime > b.finishTime;
}

std::string Node::ToString() {
  ostringstream oss;
  oss << "[" << key << "][" << visited << "][" << finishTime << "][l" << (leader ? leader->key : -1) << "][";
  for (AdjacentList::iterator it = adjacentList.begin(); it != adjacentList.end(); ++it) {
    oss << (*it)->key << " ";
  }
  oss << "]" << endl;
  return oss.str();
}

void Graph::DFS_Loop2(vector<Node*>& order) {
  finishTime = 0;
  leader = NULL;
  vector<Node*> order_ignored;

  for (vector<Node*>::reverse_iterator it = order.rbegin(); it != order.rend(); ++it) {
    Node& node = nodes[(*it)->key - 1];
    if (!node.visited) {
      leader = &node;
      DFS(node, order_ignored);
    }
  }
}

vector<Node*> Graph::DFS_Loop() {
  finishTime = 0;
  leader = NULL;
  vector<Node*> order;

  for (NodeList::iterator it = nodes.begin(); it != nodes.end(); ++it) {
    if (!it->visited) {
      leader = &(*it);
      DFS(*it, order);
    }
  }
  return order;
}

void Graph::DFS(Node& node, vector<Node*>& order) {
  node.visited = true;
  node.leader = leader;
  for (Node::AdjacentList::iterator it = node.adjacentList.begin(); it != node.adjacentList.end(); ++it) {
    Node& next = **it;
    if(!next.visited) {
      DFS(next, order);
    }
  }
  ++finishTime;
  order.push_back(&node);
  node.finishTime = finishTime;
}

// Graph Graph::FinishTimeToKey() {
//   Graph g;
//   for (NodeList::iterator it = nodeList.begin(); it != nodeList.end(); ++it) {
//     g.nodeList.insert(make_pair(it->second.finishTime, it->second));
//     g.nodeList[it->second.finishTime].visited = false;
//     g.nodeList[it->second.finishTime].key = it->second.finishTime;
//   }
//   return g;
// }

Graph Graph::Reverse() {
  Graph g;
  g.nodes.reserve(nodes.size());
  for(size_t i = 1; i <= nodes.size(); ++i) {
    g.nodes.push_back(Node(i));
  }

  for( NodeList::iterator it = nodes.begin(); it != nodes.end(); ++it) {
    int tail = it->key;
    Node::AdjacentList& list = it->adjacentList;
    for( Node::AdjacentList::iterator it2 = list.begin(); it2 != list.end(); ++it2) {
      int head = (*it2)->key;
      g.nodes[head-1].adjacentList.push_back(&g.nodes[tail-1]);
    }
  }
  return g;
}

void Graph::CreateNodes(const string& fname) {
  string line;
  int size = 0;
  std::ifstream is(fname.c_str());
  while (std::getline(is, line)) {
    std::istringstream iss(line);
    int tail;
    iss >> tail;
    size = max(size, tail);
  }
  nodes.reserve(size);
  for(int i = 1; i <= size; ++i) {
    nodes.push_back(Node(i));
  }
}

void Graph::ReadFromFile(const string& fname) {
  CreateNodes(fname);

  // Adding Edges
  string line;
  std::ifstream is(fname.c_str());
  while (std::getline(is, line)) {
    std::istringstream iss(line);
    int tail, head;
    iss >> tail;
    iss >> head;
    nodes[tail-1].adjacentList.push_back(&nodes[head-1]);
  }
}

std::string Graph::ToString() {
  ostringstream oss;
  for (NodeList::iterator it = nodes.begin(); it != nodes.end(); ++it) {
    oss << it->ToString();
  }
  return oss.str();
}
