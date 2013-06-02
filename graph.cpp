#include <iostream>
#include "graph.hpp"

using namespace std;
int displayGraph(Node *start)
{
  cout<<"Node : "<<start->getId()<<endl;
  cout<<"\tLink : "<<start->links_.front()->getId()<<endl;
}
