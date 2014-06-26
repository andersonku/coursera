#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <stack>
#include <algorithm>
#include "graph.h"

using namespace std;

vector<int> SCC(Graph& g) {
   auto pass1 = g.Reverse();
   vector<Node*> order = pass1->DFS_Loop(pass1->nodes.begin(), pass1->nodes.end());
   auto pass2 = pass1->Reverse();
   pass2->DFS_Loop2(order);
   return pass2->GetTopFive();
}

std::string Node::ToString() {
   ostringstream oss;
   oss << "[" << key << "][" << visited << "][l" << (leader ? leader->key : -1) << "][";
   for (AdjacentList::iterator it = adjacentList.begin(); it != adjacentList.end(); ++it) {
      oss << (*it)->key << " ";
   }
   oss << "]" << endl;
   return oss.str();
}

vector<int> Graph::GetTopFive() {
   // Count the leaders in the graph
   map<Node*, int> leaderCounts;
   for (auto &node : nodes) {
      if (leaderCounts.count(node.leader) == 0) {
         leaderCounts[node.leader] = 0;
      }
      ++leaderCounts[node.leader];
   }

   // Get the leader counts sorted
   vector<int> result;
   transform(leaderCounts.begin(), leaderCounts.end(), back_inserter(result), [](decltype(*begin(leaderCounts)) &pair) {return pair.second;});
   sort(result.begin(), result.end());

   vector<int> top5;
   vector<int>::reverse_iterator it = result.rbegin();
   for (int i = 0; i < 5; ++i) {
      if (it != result.rend()) {
         top5.push_back(*it++);
      } else {
         top5.push_back(0);
      }
      cout << top5.back() << " ";
   }

   return top5;
}

void Graph::DFS_Loop2(vector<Node*>& order) {
   leader = NULL;
   vector<Node*> order_ignored;

   for (vector<Node*>::reverse_iterator it = order.rbegin(); it != order.rend(); ++it) {
      Node& node = nodes[(*it)->key - 1];
      if (!node.visited) {
         leader = &node;
         DFS_Iterative(node, order_ignored);
      }
   }
}

vector<Node*> Graph::DFS_Loop(const NodeList::iterator& begin, const NodeList::iterator& end) {
   leader = NULL;
   vector<Node*> order;

   for (NodeList::iterator it = begin; it != end; ++it) {
      if (!it->visited) {
         leader = &(*it);
         DFS_Iterative(*it, order);
      }
   }
   return order;
}

void Graph::DFS_Iterative(Node& startNode, vector<Node*>& order)
{
   stack<Node*> s;                     // Use stack to replace recursion
   s.push(&startNode);
   while (!s.empty()) {
      Node& node = *s.top();
      if (!node.visited) {             // First time here
         node.visited = true;
         node.leader = leader;
         for (auto &nodePtr : node.adjacentList) {
            if (!nodePtr->visited) {
               s.push(nodePtr);
            }
         }
      } else {                         // Finished trying all the edges
         order.push_back(&node);
         s.pop();
      }
   }
}

shared_ptr<Graph> Graph::Reverse() {
   auto dest = make_shared<Graph>();
   dest->nodes.reserve(nodes.size());
   for (size_t i = 1; i <= nodes.size(); ++i) {
      dest->nodes.push_back(Node(i));
   }

   // Reverse the edges
   for (auto &tailNode : nodes) {
      for (auto & headNodePtr : tailNode.adjacentList) {
         dest->nodes[headNodePtr->key - 1].adjacentList.push_back(&dest->nodes[tailNode.key - 1]);
      }
   }
   return dest;
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
   for (int i = 1; i <= size; ++i) {
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
      nodes[tail - 1].adjacentList.push_back(&nodes[head - 1]);
   }
}

std::string Graph::ToString() {
   ostringstream oss;
   for (NodeList::iterator it = nodes.begin(); it != nodes.end(); ++it) {
      oss << it->ToString();
   }
   return oss.str();
}
