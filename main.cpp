#include <iostream>
#include "graph.hpp"

using namespace std;

int main()
{
  cout<<"Starting Program"<<endl;

  cout<<"Creating Nodes"<<endl;
  Node node1(0);
  Node node2(0);

  cout<<"Creating Link"<<endl;
  Link link1(1);

  cout<<"Adding nodes to link"<<endl;
  link1.addNodeToEdge(&node1,0);
  cout<<"Finished adding Node : "<<node1.getId()<<endl;
  link1.addNodeToEdge(&node1,1);
  cout<<"Finished adding Node : "<<node1.getId()<<endl;

  cout<<"About to display Graph"<<endl;
  displayGraph(&node1);

  cout<<"I just created 2 nodes and a link"<<endl;
  return 0;
}
