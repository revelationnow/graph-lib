#include <iostream>
#include "graph.hpp"

using namespace std;

int Link::total_links = 0;

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

int Link::nodeIDAttachedToEdge(int edge)
{
  if(edge == 0 || edge == 1)
  {
    if(NULL != node_[edge])
    {
      return node_[edge]->getId();
    }
    else
    {
      cout<<"Link ID : "<<link_id_<<" has no node at Edge : "<<edge<<endl;
      return -1;
    }
  }
  else
  {
    cout<<"ERR : Link ID : "<<link_id_<<" index out of range in parameter passed to nodeIDAttachedToEdge(int edge) edge = "<<edge<<" should be either 0 or 1"<<endl;
    return -1;
  }
}

Node* Link::getNodeAtEdge(int edge)
{
  if(edge != 0 && edge != 1)
  {
    cout<<"ERR : Link ID : "<<link_id_<<" trying to get node at unsupported Edge : "<<edge<<endl;
  }
  else
  {
    return node_[edge];
  }
}

int Link::addNodeToEdge(Node* node, int edge)
{
  if(node == NULL)
  {
    cout<<"ERR : Link ID "<<link_id_<<" Counldn't add Node, Node was NULL"<<endl;
    return -1;
  }
  else
  {
    if(node_[edge] == NULL)
    {
      node_[edge] = node;
      cout<<"Link ID : "<<link_id_<<" found free Edge : "<<edge<<" adding Node : "<<node->getId()<<endl;
      node->addLinkEdge(this,edge);
      return 0;
    }
    else if(node->getId() == node_[edge]->getId())
    {
      cout<<"Link ID : "<<link_id_<<" already attached to Node ID : "<<node->getId()<<" at Edge : "<<edge<<endl;
    }
    else
    {
      cout<<"ERR : Link ID "<<link_id_<<" Link is full can't add Node ID " << node->getId()<<endl;
      return -2;
    }
  }
}
