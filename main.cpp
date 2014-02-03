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

  Node node[5];
  Link link[10];

  int k = 0;
  /** \code{.cpp} Code block to generate the initial graph */
  for(int i = 0;i<5;i++)
  {
    for(int j = i+1;j<5;j++)
    {
      addLinkEdgeToNode(&node[i], &link[k], 0);
      addLinkEdgeToNode(&node[j], &link[k], 1);
      k++;
    }
  }
  /** \endcode */

  /** Display the generated graph */
  displayGraph(&node[0]);
  OUTPUT_MSG(INFO,"I just created 2 nodes and a link");
  return 0;
}
