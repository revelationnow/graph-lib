#include <iostream>
#include "graph.hpp"

using namespace std;

int Link::total_links = 0;
int Link::total_link_ids = 0;

Link::Link(int weight)
{
	weight_ = weight;
  link_id_ = total_links;
  total_links++;
  node_[0] = NULL;
  node_[1] = NULL;
}

int Link::getId()
{
  return link_id_;
}


Node* Link::getNodeAtEdge(int edge)
{
  if(edge != 0 && edge != 1)
  {
    cout<<"ERR : Link ID : "<<link_id_<<" trying to get node at unsupported Edge : "<<edge<<endl;
  }
  else
  {
    if(NULL != node_[edge])
    {
      return node_[edge];
    }
    else
    {
      cout<<"ERR : Link ID : "<<link_id_<<" has no node at Edge : "<<edge<<endl;
    }
  }
}

