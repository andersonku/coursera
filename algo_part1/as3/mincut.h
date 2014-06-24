#include <vector>
#include <unordered_map>

struct Graph {
   typedef std::vector<int> AdjacentList;

   std::unordered_map<int, AdjacentList> _nodes;

   void CollapseBigIntoSmall(int from, int to);
   void Collapse(int from, int to);
   void CollapseToTwo();
   void ReadFile(char* fname);
};
