#include <vector>
#include <string>
#include <stack>

struct Node {
  typedef std::vector<Node*> AdjacentList;

Node() : visited(false), leader(NULL), finishTime(0) {}
Node(int key) : key(key), visited(false), leader(NULL), finishTime(0) {}
  std::string ToString();

  int key;
  AdjacentList adjacentList;
  bool visited;
  Node* leader;
  int finishTime;
};

bool sortByFinishTime(Node& a, Node& b);

struct Graph {
  typedef std::vector<Node> NodeList;
  NodeList nodes;
  int finishTime;
  Node* leader;

  Graph() : finishTime(0), leader(NULL) {}
  void ReadFromFile(const std::string& fname);
  void CreateNodes(const std::string& fname);
  std::string ToString();
  Graph Reverse();
  Graph FinishTimeToKey();
  std::vector<Node*> DFS_Loop();
  void DFS(Node& node, std::vector<Node*>& order);
  void DFS_Loop2(std::vector<Node*>& order);
  std::vector<int> GetTopFive();
};

Graph SCC(Graph& g);
