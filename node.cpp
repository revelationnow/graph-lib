#include <iostream>
#include <vector>
#include "graph.hpp"
#include "errHandler.hpp"

using namespace std;

int Node::total_nodes = 0;

int Node::total_node_ids = 0;

Node::Node(int value)
{
  value_ = value;
  node_id_ = total_node_ids;
  total_nodes++;
  total_node_ids++;
}

int Node::getDegree()
{
  return links_.size();
}

int Node::getValue()
{
  return value_;
}

int Node::getId()
{
  return node_id_;
}

void Node::setValue(int value)
{
  value_ = value;
}

boolean Node::linkAttachedToNode(Link* link)
{
  for(list<Link*>::iterator link_iterator = links_.begin();link_iterator != links_.end();++link_iterator)
  {
    if((*link_iterator)->getId() == link->getId())
    {
      return TRUE;
    }
  }
  return FALSE;
}

int Node::removeLink(Link* link)
{
  for(list<Link*>::iterator link_iterator = links_.begin();link_iterator != links_.end(); ++link_iterator)
  {
    if((*link_iterator)->getId() == link->getId())
    {
      links_.erase(link_iterator);
      return 0;
    }
  }
  return -1;
}

