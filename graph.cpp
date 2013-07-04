#include <iostream>
#include "graph.hpp"

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
    cout<<"Node : "<<t_node->getId()<<endl;
    visited[t_node->getId()] = TRUE;
    total_visited++;
    for(list<Link*>::iterator link_iterator = t_node->links_.begin();link_iterator != t_node->links_.end(); ++link_iterator)
    {
      cout<<"\tLink : "<<(*link_iterator)->getId()<<endl;
      l_node[0] = (*link_iterator)->node_[0];
      l_node[1] = (*link_iterator)->node_[1];

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
    cout<<"ERR : Can't remove Link from null Node"<<endl;
  }
  else if(link == NULL)
  {
    cout<<"ERR : Can't remove Node from null Link"<<endl;
  }
  else if(edge != 0 && edge != 1)
  {
    cout<<"ERR : Can't remove Node from Link at invalid Edge : "<<edge<<endl;
  }
  else
  {
    Node* t_node = link->getNodeAtEdge(edge);
    if(t_node != NULL)
    {
      if(t_node->getId() == node->getId())
      {
        link->node_[edge] = NULL;
        node->removeLink(link);
      }
    }
  }
}

int addLinkEdgeToNode(Node* node, Link* link, int edge)
{
  if(node == NULL)
  {
    cout<<"ERR : Can't attach Link to null Node"<<endl;
  }
  else if(link == NULL)
  {
    cout<<"ERR : Can't attach Node to null Link"<<endl;
  }
  else if(edge != 0 && edge != 1)
  {
    cout<<"ERR : Can't attach Node to Link at invalid Edge : "<<edge<<endl;
  }
  else
  {
    if(link->node_[edge] != NULL)
    {
      cout<<"ERR : Can't add Node : "<<node->getId()<<" to Link : "<<link->getId()<<" at Edge : "<<edge<<" as another node already exists there"<<endl;
    }
    else
    {
      link->node_[edge] = node;
      node->links_.push_back(link);
      cout<<"Added Link : "<<link->getId()<<" to Node : "<<node->getId()<<" at Edge : "<<edge<<endl;
    }
  }
}
