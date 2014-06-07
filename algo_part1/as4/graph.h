#include <vector>
#include <map>
#include <string>

struct Node {
  typedef std::vector<int> AdjacentList;

Node() : visited(false), leader(NULL), finishTime(0) {}
Node(int key) : key(key), visited(false), leader(NULL), finishTime(0) {}
  std::string ToString();

  int key;
  AdjacentList adjacentList;
  bool visited;
  Node* leader;
  int finishTime;
};

struct Graph {
  typedef std::vector<Node> NodeList;
  NodeList nodeList;
  int finishTime;
  Node* leader;

  Graph() : finishTime(0), leader(NULL) {}
  void ReadFromFile(const std::string& fname);
  std::string ToString();
  void AddEdge(int tail, int head);
  Graph Reverse();
  Graph FinishTimeToKey();
  void DFS_Loop();
  void DFS(Node& node);
};

Graph SSC(Graph& g);
