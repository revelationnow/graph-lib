/// \file graph.cpp
#include <iostream>
#include "graph.hpp"
#include "errHandler.hpp"

using namespace std;
int displayGraph(Node *start)
{
  boolean* visited = new boolean[Node::total_nodes];
  int total_visited = 0;
  list<Node*> t_nodes;
  Node* t_node;
  Node* l_node[2];
  t_nodes.push_back(start);

  while(total_visited < Node::total_nodes)
  {
    Node* t_node = t_nodes.front();
    t_nodes.pop_front();
    if(t_node == NULL)
    {
      break;
    }
    cout<<PRINT_TAG<<"Node : "<<t_node->getId()<<endl;
    visited[t_node->getId()] = TRUE;
    total_visited++;
    for(list<Link*>::iterator link_iterator = t_node->links_.begin();link_iterator != t_node->links_.end(); ++link_iterator)
    {
      cout<<PRINT_TAG<<"\tLink : "<<(*link_iterator)->getId()<<endl;
      l_node[0] = (*link_iterator)->getNodeAtEdge(0);
      l_node[1] = (*link_iterator)->getNodeAtEdge(1);

      if(l_node[0] != NULL)
      {
        if(visited[l_node[0]->getId()] != TRUE)
        {
          t_nodes.push_back(l_node[0]);
        }
      }

      if(l_node[1] != NULL)
      {
        if(visited[l_node[1]->getId()] != TRUE)
        {
          t_nodes.push_back(l_node[1]);
        }
      }
    }
  }
}

int removeLinkEdgeFromNode(Node *node, Link* link, int edge)
{
  
  if(node == NULL)
  {
    cout<<PRINT_TAG<<"ERR : Can't remove Link from null Node"<<endl;
  }
  else if(link == NULL)
  {
    cout<<PRINT_TAG<<"ERR : Can't remove Node from null Link"<<endl;
  }
  else if(edge != 0 && edge != 1)
  {
    cout<<PRINT_TAG<<"ERR : Can't remove Node from Link at invalid Edge : "<<edge<<endl;
  }
  else
  {
    Node* t_node = link->getNodeAtEdge(edge);
    if(t_node != NULL)
    {
      if(t_node->getId() == node->getId())
      {
        link->detachNodeByEdge(edge);
        node->removeLink(link);
      }
    }
  }
}

int addLinkEdgeToNode(Node* node, Link* link, int edge)
{
  if(node == NULL)
  {
    cout<<PRINT_TAG<<"ERR : Can't attach Link to null Node"<<endl;
  }
  else if(link == NULL)
  {
    cout<<PRINT_TAG<<"ERR : Can't attach Node to null Link"<<endl;
  }
  else if(edge != 0 && edge != 1)
  {
    cout<<PRINT_TAG<<"ERR : Can't attach Node to Link at invalid Edge : "<<edge<<endl;
  }
  else
  {
    if(link->getNodeAtEdge(edge) != NULL)
    {
      cout<<PRINT_TAG<<"ERR : Can't add Node : "<<node->getId()<<" to Link : "<<link->getId()<<" at Edge : "<<edge<<" as another node already exists there"<<endl;
    }
    else
    {
      link->node_[edge] = node;
      node->links_.push_back(link);
      cout<<PRINT_TAG<<"Added Link : "<<link->getId()<<" to Node : "<<node->getId()<<" at Edge : "<<edge<<endl;
    }
  }
}

int Graph::displayGraph()
{
  boolean* visited = new boolean[nodes_.size()];
  int total_visited = 0;
  list<Node*> t_nodes;
  Node* t_node;
  Node* l_node[2];
  t_nodes.push_back((nodes_.front()));

  while(total_visited < Node::total_nodes)
  {
    Node* t_node = t_nodes.front();
    t_nodes.pop_front();
    if(t_node == NULL)
    {
      break;
    }
    cout<<PRINT_TAG<<"Node : "<<t_node->getId()<<endl;
    visited[t_node->getId()] = TRUE;
    total_visited++;
    for(list<Link*>::iterator link_iterator = t_node->links_.begin();link_iterator != t_node->links_.end(); ++link_iterator)
    {
      cout<<PRINT_TAG<<"\tLink : "<<(*link_iterator)->getId()<<endl;
      l_node[0] = (*link_iterator)->getNodeAtEdge(0);
      l_node[1] = (*link_iterator)->getNodeAtEdge(1);

      if(l_node[0] != NULL)
      {
        if(visited[l_node[0]->getId()] != TRUE)
        {
          t_nodes.push_back(l_node[0]);
        }
      }

      if(l_node[1] != NULL)
      {
        if(visited[l_node[1]->getId()] != TRUE)
        {
          t_nodes.push_back(l_node[1]);
        }
      }
    }
  }
}

int Graph::attachLinkToNodeAtEdge(int lid, int nid, int edge)
{
  Node* node = getNodeById(nid);
  Link* link = getLinkById(lid);
  if(NULL == node)
  {
    cout<<PRINT_TAG<<"ERR : Can't find Node ID : "<<nid<<" in Graph : "<<graph_id_<<endl;
    return -1;
  }
  else if(NULL == link)
  {
    cout<<PRINT_TAG<<"ERR : Can't find Link ID : "<<lid<<" in Graph : "<<graph_id_<<endl;
    return -1;
  }
  
  if((0 != edge) && (1 != edge))
  {
    cout<<PRINT_TAG<<"ERR : Edge : "<<edge<<" is out of bounds"<<endl;
    return -1;
  }
  
  if(NULL != link->getNodeAtEdge(edge))
  {
    cout<<PRINT_TAG<<"ERR : Link ID : "<<lid<<" already has another Node : "<<(link->getNodeAtEdge(edge))->getId()<<" at Edge : "<<edge<<endl;
    return -2;
  }
  else
  {
    link->node_[edge] = node;
    node->links_.push_back(link);
    cout<<PRINT_TAG<<"Added Link : "<<link->getId()<<" to Node : "<<node->getId()<<" at Edge : "<<edge<<endl;
    return 0;
  }
}

int Graph::detachLinkFromNodeAtEdge(int lid, int nid, int edge)
{

  Node* node = getNodeById(nid);
  Link* link = getLinkById(lid);
  if(NULL == node)
  {
    cout<<PRINT_TAG<<"ERR : Can't find Node ID : "<<nid<<" in Graph : "<<graph_id_<<endl;
    return -1;
  }
  else if(NULL == link)
  {
    cout<<PRINT_TAG<<"ERR : Can't find Link ID : "<<lid<<" in Graph : "<<graph_id_<<endl;
    return -1;
  }

  if((0 != edge) && (1 != edge))
  {
    cout<<PRINT_TAG<<"ERR : Edge : "<<edge<<" is out of bounds"<<endl;
    return -1;
  }
  if(link->node_[edge] != node)
  {
    cout<<PRINT_TAG<<"ERR : Can't find Node ID "<<nid<<" at Edge : "<<edge<<" of Link ID : "<<lid<<endl;
    return -2;
  }
  else
  {
    link->detachNodeByEdge(edge);
    node->removeLink(link);
    return 0;
  }

}


Node* Graph::getNodeById(int nid)
{
  for(list<Node*>::iterator node_iterator = nodes_.begin(); node_iterator != nodes_.end(); ++node_iterator)
  {
    if((*node_iterator)->getId() == nid)
    {
      return (*node_iterator);
    }
  }
  return NULL;
}


Link* Graph::getLinkById(int lid)
{
  for(list<Link*>::iterator link_iterator = links_.begin(); link_iterator != links_.end(); ++link_iterator)
  {
    if((*link_iterator)->getId() == lid)
    {
      return (*link_iterator);
    }
  }
  return NULL;
}
