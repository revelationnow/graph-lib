/// \file graph.cpp
#include <iostream>
#include "graph.hpp"
#include "errHandler.hpp"

using namespace std;
/** \fn displayGraph()
    @brief This function prints out the graph of which start is a member. It uses Djikstra's Graph search algorithm.
    @param start a variable of type Node*, can be any node within the graph
*/
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
    OUTPUT_MSG(INFO,"Node : "<<t_node->getId());
    visited[t_node->getId()] = TRUE;
    total_visited++;
    for(list<Link*>::iterator link_iterator = t_node->links_.begin();link_iterator != t_node->links_.end(); ++link_iterator)
    {
      OUTPUT_MSG(INFO,"\tLink : "<<(*link_iterator)->getId());
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

/** \fn removeLinkEdgeFromNode()
    @brief This function detaches a Link from a Node at a given Edge
    @param node a variable of type Node*
    @param link a variable of type Link*
    @param edge a variable of type int
*/
int removeLinkEdgeFromNode(Node *node, Link* link, int edge)
{
  
  if(node == NULL)
  {
    OUTPUT_MSG(ERR, "Can't remove Link from null Node");
  }
  else if(link == NULL)
  {
    OUTPUT_MSG(ERR, "Can't remove Node from null Link");
  }
  else if(edge != 0 && edge != 1)
  {
    OUTPUT_MSG(ERR, "Can't remove Node from Link at invalid Edge : "<<edge);
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

/** \fn addLinkEdgeToNode()
    @brief This function adds a Link to a Node at a given Edge.
    @param node a variable of type Node*
    @param link a variable of type Link*
    @param edge a variable of type int
*/
int addLinkEdgeToNode(Node* node, Link* link, int edge)
{
  if(node == NULL)
  {
    OUTPUT_MSG(ERR, "Can't attach Link to null Node");
  }
  else if(link == NULL)
  {
    OUTPUT_MSG(ERR, "Can't attach Node to null Link");
  }
  else if(edge != 0 && edge != 1)
  {
    OUTPUT_MSG(ERR, "Can't attach Node to Link at invalid Edge : "<<edge);
  }
  else
  {
    if(link->getNodeAtEdge(edge) != NULL)
    {
      OUTPUT_MSG(ERR, "Can't add Node : "<<node->getId()<<" to Link : "<<link->getId()<<" at Edge : "<<edge<<" as another node already exists there");
    }
    else
    {
      link->node_[edge] = node;
      node->links_.push_back(link);
      OUTPUT_MSG(INFO, "Added Link : "<<link->getId()<<" to Node : "<<node->getId()<<" at Edge : "<<edge);
    }
  }
}
int Graph::total_graphs = 0;
int Graph::total_graph_ids = 0;

Graph::Graph()
{
  graph_id_ = total_graph_ids;
  total_graphs++;
  total_graph_ids++;
  
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
    OUTPUT_MSG(INFO, "Node : "<<t_node->getId());
    visited[t_node->getId()] = TRUE;
    total_visited++;
    for(list<Link*>::iterator link_iterator = t_node->links_.begin();link_iterator != t_node->links_.end(); ++link_iterator)
    {
      OUTPUT_MSG(INFO, "\tLink : "<<(*link_iterator)->getId());
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
    OUTPUT_MSG(ERR, "Can't find Node ID : "<<nid<<" in Graph : "<<graph_id_);
    return -1;
  }
  else if(NULL == link)
  {
    OUTPUT_MSG(ERR, "Can't find Link ID : "<<lid<<" in Graph : "<<graph_id_);
    return -1;
  }
  
  if((0 != edge) && (1 != edge))
  {
    OUTPUT_MSG(ERR, "Edge : "<<edge<<" is out of bounds");
    return -1;
  }
  
  if(NULL != link->getNodeAtEdge(edge))
  {
    OUTPUT_MSG(ERR, "Link ID : "<<lid<<" already has another Node : "<<(link->getNodeAtEdge(edge))->getId()<<" at Edge : "<<edge);
    return -2;
  }
  else
  {
    link->node_[edge] = node;
    node->links_.push_back(link);
    OUTPUT_MSG(INFO, "Added Link : "<<link->getId()<<" to Node : "<<node->getId()<<" at Edge : "<<edge);
    return 0;
  }
}

int Graph::detachLinkFromNodeAtEdge(int lid, int nid, int edge)
{

  Node* node = getNodeById(nid);
  Link* link = getLinkById(lid);
  if(NULL == node)
  {
    OUTPUT_MSG(ERR, "Can't find Node ID : "<<nid<<" in Graph : "<<graph_id_);
    return -1;
  }
  else if(NULL == link)
  {
    OUTPUT_MSG(ERR, "Can't find Link ID : "<<lid<<" in Graph : "<<graph_id_);
    return -1;
  }

  if((0 != edge) && (1 != edge))
  {
    OUTPUT_MSG(ERR, "Edge : "<<edge<<" is out of bounds");
    return -1;
  }
  if(link->node_[edge] != node)
  {
    OUTPUT_MSG(ERR,"Can't find Node ID "<<nid<<" at Edge : "<<edge<<" of Link ID : "<<lid);
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

int Graph::addLinkToGraph(Link* link)
{
  if(link != NULL)
  {
    links_.push_front(link);
    return 0;
  }
  else
  {
    OUTPUT_MSG(ERR,"Can't add NULL link to Graph ID : "<<graph_id_);
    return -1;
  }
}


int Graph::addNodeToGraph(Node* node)
{
  if(node != NULL)
  {
    nodes_.push_front(node);
    return 0;
  }
  else
  {
    OUTPUT_MSG(ERR,"Can't add NULL node to Graph ID : "<<graph_id_);
    return -1;
  }
}
