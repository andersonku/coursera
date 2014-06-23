#include <vector>
#include <map>

struct Graph {
   typedef std::vector<int> AdjacentList;

   std::map<int, AdjacentList> _nodes;

   void CollpseBigIntoSmall(int from, int to);
   void Collapse(int from, int to);
   void CollapseToTwo();
   //void PrintGraph(const Graph& g);
   void ReadFile(char* fname);
};
