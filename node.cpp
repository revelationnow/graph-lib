#include <iostream>
#include <vector>
#include "graph.hpp"

using namespace std;

int Node::total_nodes = 0;

Node::Node(int value)
{
  value_ = value;
  node_id_ = total_nodes;
  total_nodes++;
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

int Node::addLinkEdge(Link* link, int edge)
{
  int nodeIdAttachedToLinkEdge = -1;
  if(NULL == link)
  {
    cout<<"ERR : Node ID "<< node_id_<<" Couldn't Add Link, link was NULL"<<endl;
    return -1;
  }
  else
  {
    nodeIdAttachedToLinkEdge = link->nodeIDAttachedToEdge(edge);
    if(nodeIdAttachedToLinkEdge >= 0)
    {
      if(FALSE == linkAttachedToNode(link))
      {
        links_.push_front(link);
      }
      else
      {
        cout<<"Node ID : "<<node_id_<<" list of links already has Link ID : "<<link->getId()<<endl;
      }
    }
    if(node_id_ == nodeIdAttachedToLinkEdge)
    {
      cout<<"Node ID "<<node_id_<<" already attached to Link ID "<<link->getId()<<" at edge "<<edge<<endl;
    }
    else if( 0 == link->addNodeToEdge(this, edge))
    {
      cout<<"Node ID : "<<node_id_<<" attaching to Link ID : "<<link->getId()<<" at Edge : "<<edge<<endl;
    }
    else
    {
      cout<<"ERR : Node ID : "<<node_id_<<" Couldn't attach to Link ID : "<<link->getId()<<endl; 
      return -2;
    }
    return 0;
  }
}


int Node::removeLinkEdge(Link* link, int edge)
{
  for(list<Link*>::iterator link_iterator = links_.begin(); link_iterator != link_.end(); link_iterator++)
   {
     if((*link_iterator)->getId() == link->getId())
     {
       if((*link_iterator)->nodeIDAttachedToEdge(edge) == link->nodeIDAttachedToEdge(edge))
       {
         /* Don't delete link if node on the other edge of the link is the same node */
         if(node_id_ != link->nodeIDAttachedToEdge( (edge + 1)&0x1))
         {
           links_.erase(link_iterator);
         }
         //TODO : LEFT OF HERE : Delete this and replace with friend functions for attach/detach
         link->removeNodeFromEdge(edge);
         return 0;
       }
     }
   }
   return -1;
  
}
