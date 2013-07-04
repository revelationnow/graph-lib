#include <iostream>
#include "graph.hpp"

using namespace std;

int main()
{
  cout<<"Starting Program"<<endl;


  Node node[5];
  Link link[10];

  int k = 0;
  for(int i = 0;i<5;i++)
  {
    for(int j = i+1;j<5;j++)
    {
      addLinkEdgeToNode(&node[i], &link[k], 0);
      addLinkEdgeToNode(&node[j], &link[k], 1);
      k++;
    }
  }
  displayGraph(&node[0]);

  cout<<"I just created 2 nodes and a link"<<endl;
  return 0;
}
