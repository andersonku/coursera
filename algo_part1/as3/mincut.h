#include <vector>
#include <map>

typedef int Node;
typedef int FirstNode;
typedef std::vector<Node> AdjacentList;
typedef std::map<FirstNode, AdjacentList> Graph;


Graph Collapse(Graph& g, int from, int to);
Graph CollapseToTwo(Graph g);
void PrintGraph(const Graph& g);
Graph ReadFile(char* fname);
