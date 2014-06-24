#include <vector>
#include <string>
#include <memory>

struct Node {
   typedef std::vector<Node*> AdjacentList;

   Node() : visited(false), leader(NULL), adjacentList() {}
   Node(int key) : key(key), visited(false), leader(NULL), adjacentList() {}
   std::string ToString();

   int key;
   AdjacentList adjacentList;
   bool visited;
   Node* leader;
};

struct Graph {
   typedef std::vector<Node> NodeList;
   NodeList nodes;
   Node* leader;

   Graph() : leader(NULL) {}
   void ReadFromFile(const std::string& fname);
   void CreateNodes(const std::string& fname);
   std::string ToString();
   std::shared_ptr<Graph> Reverse();
   std::vector<Node*> DFS_Loop(const NodeList::iterator& begin, const NodeList::iterator& end);
   void DFS_Iterative(Node& node, std::vector<Node*>& order);
   void DFS_Loop2(std::vector<Node*>& order);
   std::vector<int> GetTopFive();
};

std::vector<int> SCC(Graph& g);
