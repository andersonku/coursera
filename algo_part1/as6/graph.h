#include <vector>
#include <string>
#include <limits.h>

#define INF std::numeric_limits<int>::max()

struct Heap {
  Heap(int initCapacity) : size(0) {
    capacity = initCapacity;
    items = (int*)malloc(capacity * sizeof(int));
  }

  void insert(const int key);
  int extractMin();
  std::string toString(); // For testing

  int*  items;   // Dynamically allocated
  size_t size;
  size_t capacity;
};

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
