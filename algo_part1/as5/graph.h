#include <vector>
#include <string>
#include <limits.h>

#define INF std::numeric_limits<int>::max()

struct Node;

struct Edge {
  int key;
  int dist;
Edge(int key, int dist) : key(key), dist(dist) {}
};

struct Node {
  typedef std::vector<Edge> AdjacentList;

Node(int key) : key(key), shortestDist(INF) {}
  std::string ToString();
  int key;
  int shortestDist;
  AdjacentList edges;
};

struct DSPathVect {
  std::vector<Node> nodes;

  void ReadFromFile(const std::string& fname);
  void computeDist(const int s);
  std::string ToString();
};
