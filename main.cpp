///\file main.cpp
#include <iostream>
#include "graph.hpp"
#include "errHandler.hpp"

using namespace std;
/** \fn main()
    @brief The main function where the program starts
*/
int main(int argc, char* argv[])
{
  OUTPUT_MSG(INFO,"Starting Program");

  const int num_nodes = 10;
  const int num_links = (num_nodes * (num_nodes - 1))/2;
  Graph<int,int> *graph = new Graph<int,int>();
  int node_ids[num_nodes];
  int link_ids[num_links];
  for(int i=0;i<num_nodes;i++)
  {
    node_ids[i] = graph->createNode(0);
  }
  for(int i=0;i < num_links; i++)
  {
    link_ids[i] = graph->createLink(1);
  }

  int k = 0;
  /** \code{.cpp} Code block to generate the initial graph */
  for(int i = 0;i<num_nodes;i++)
  {
    for(int j = i+1;j<num_nodes;j++)
    {
      graph->attachLinkToNodeAtEdge(link_ids[k],node_ids[i], 0);
      graph->attachLinkToNodeAtEdge(link_ids[k],node_ids[j], 1);
      k++;
    }
  }
  /** \endcode */

  /** Display the generated graph */
  graph->displayGraph();
  OUTPUT_MSG(INFO,"I just created "<<num_nodes<<" nodes and "<<num_links<<" links");
  delete graph;
  return 0;
}
