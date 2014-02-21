///\file main.cpp
#include <iostream>
#include "graph.hpp"
#include "errHandler.hpp"

using namespace std;
/** \fn main()
    @brief The main function where the program starts
*/
int main()
{
  OUTPUT_MSG(INFO,"Starting Program");

  const int num_nodes = 2;
  const int num_links = 4;
  Node<int,int>* node[num_nodes];
  Link<int,int>* link[num_links];
  Graph<int,int> graph;
  for(int i = 0;i<num_nodes;i++)
  {
    node[i] = new Node<int,int>(1);
    graph.addNodeToGraph(node[i]);
  }
  for(int i=0;i<num_links;i++)
  {
    link[i] = new Link<int,int>(1);
    graph.addLinkToGraph(&link[i]);
    OUTPUT_MSG(LOW,"Node 0 at link id : "<<link[0]->getId()<<" is : "<<link[0]->getNodeAtEdge(0));
  }

  int k = 0;
  /** \code{.cpp} Code block to generate the initial graph */
  for(int i = 0;i<2;i++)
  {
    for(int j = i+1;j<2;j++)
    {
      OUTPUT_MSG(LOW,"Node 0 at link id : "<<link[0]->getId()<<" is : "<<link[0]->getNodeAtEdge(0));
      OUTPUT_MSG(LOW,"Attaching Link : "<<link[k]->getId()<<" to Node : "<<node[i]->getId()<<" and Node : "<<node[j]->getId());
      OUTPUT_MSG(LOW,"Node 0 at link id : "<<link[0]->getId()<<" is : "<<link[0]->getNodeAtEdge(0));
      graph.attachLinkToNodeAtEdge(link[k]->getId(),node[i]->getId(), 0);
      OUTPUT_MSG(LOW,"Node 0 at link id : "<<link[0]->getId()<<" is : "<<link[0]->getNodeAtEdge(0));
      graph.attachLinkToNodeAtEdge(link[k]->getId(),node[j]->getId(), 1);
      k++;
    }
  }
  /** \endcode */

  /** Display the generated graph */
  graph.displayGraph();
  OUTPUT_MSG(INFO,"I just created 2 nodes and a link");
  for(int i = 0;i<num_nodes;i++)
  {
    delete node[i];
  }
  for(int i = 0;i<num_links;i++)
  {
    delete link[i];
  }
  return 0;
}
