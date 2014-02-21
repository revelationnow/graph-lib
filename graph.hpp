/// \file graph.hpp
#ifndef __GRAPH_HPP_
#define __GRAPH_HPP_
#include "common.hpp"
#include "node.hpp"
#include "link.hpp"

using namespace std;

template<class Tnode, class Tlink>
class Graph
{
  private:
    list<Node<Tnode,Tlink>*> nodes_;
    list<Link<Tlink,Tnode>*> links_;
    int graph_id_;
    static int total_graphs;
    static int total_graph_ids;
  public:
    Graph();
    Graph(list<Node<Tnode,Tlink>*>, list<Link<Tlink,Tnode>*>);
    int displayGraph();
    int createLink();
    int createNode();
    int destroyLink(int lid);
    int destroyNode(int nid);
    Node<Tnode,Tlink>* getNodeById(int nid);
    Link<Tlink,Tnode>* getLinkById(int lid);
    int addLinkToGraph(Link<Tlink,Tnode> * link);
    int addNodeToGraph(Node<Tnode,Tlink> * node);
    int attachLinkToNodeAtEdge(int lid,int nid, int edge);
    int detachLinkFromNodeAtEdge(int lid,int nid, int edge);
};

template<class Tnode,class Tlink>
int Graph<Tnode,Tlink>::total_graphs = 0;

template<class Tnode,class Tlink>
int Graph<Tnode,Tlink>::total_graph_ids = 0;

template<class Tnode,class Tlink>
Graph<Tnode,Tlink>::Graph()
{
  graph_id_ = total_graph_ids;
  total_graphs++;
  total_graph_ids++;
  
}

template<class Tnode,class Tlink>
int Graph<Tnode,Tlink>::displayGraph()
{
  boolean* visited = new boolean[nodes_.size()];
  int total_visited = 0;
  list<Node<Tnode,Tlink>*> t_nodes;
  Node<Tnode,Tlink>* t_node;
  Node<Tnode,Tlink>* l_node[2];
  t_nodes.push_back((nodes_.back()));

  while(total_visited < Node<Tnode,Tlink>::total_nodes)
  {
    Node<Tnode,Tlink>* t_node = t_nodes.front();
    if(t_node == NULL)
    {
      break;
    }
    t_nodes.pop_front();
    OUTPUT_MSG(INFO, "Node : "<<t_node->getId());
    visited[t_node->getId()] = TRUE;
    total_visited++;
    for(typename list<Link<Tlink,Tnode>*>::iterator link_iterator = t_node->links_.begin();link_iterator != t_node->links_.end(); ++link_iterator)
    {
      OUTPUT_MSG(INFO, "\t|| "<<((*link_iterator)->getNodeAtEdge(0))->getId()<<" ||----------<"<<(*link_iterator)->getId()<<">----------|| "<<((*link_iterator)->getNodeAtEdge(1))->getId()<<" ||");
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

template<class Tnode,class Tlink>
int Graph<Tnode,Tlink>::attachLinkToNodeAtEdge(int lid, int nid, int edge)
{
  Node<Tnode,Tlink>* node = getNodeById(nid);
  Link<Tlink,Tnode>* link = getLinkById(lid);

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
    OUTPUT_MSG(INFO, "Attached Link : "<<link->getId()<<" to Node : "<<node->getId()<<" at Edge : "<<edge);
    return 0;
  }
}

template<class Tnode,class Tlink>
int Graph<Tnode,Tlink>::detachLinkFromNodeAtEdge(int lid, int nid, int edge)
{

  Node<Tnode,Tlink>* node = getNodeById(nid);
  Link<Tlink,Tnode>* link = getLinkById(lid);
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


template<class Tnode,class Tlink>
Node<Tnode,Tlink>* Graph<Tnode,Tlink>::getNodeById(int nid)
{
  for(typename list<Node<Tnode,Tlink>*>::iterator node_iterator = nodes_.begin(); node_iterator != nodes_.end(); ++node_iterator)
  {
    if((*node_iterator)->getId() == nid)
    {
      return (*node_iterator);
    }
  }
  return NULL;
}


template<class Tnode,class Tlink>
Link<Tlink,Tnode>* Graph<Tnode,Tlink>::getLinkById(int lid)
{
  for(typename list<Link<Tlink,Tnode>*>::iterator link_iterator = links_.begin(); link_iterator != links_.end(); ++link_iterator)
  {
    if((*link_iterator)->getId() == lid)
    {
      return (*link_iterator);
    }
  }
  return NULL;
}

template<class Tnode,class Tlink>
int Graph<Tnode,Tlink>::addLinkToGraph(Link<Tlink,Tnode>* link)
{
  if(link != NULL)
  {
    links_.push_front((link));
    return 0;
  }
  else
  {
    OUTPUT_MSG(ERR,"Can't add NULL link to Graph ID : "<<graph_id_);
    return -1;
  }
}


template<class Tnode,class Tlink>
int Graph<Tnode,Tlink>::addNodeToGraph(Node<Tnode,Tlink>* node)
{
  if(node != NULL)
  {
    nodes_.push_front(node);
    Node<Tnode,Tlink> *temp = nodes_.front();
    return 0;
  }
  else
  {
    OUTPUT_MSG(ERR,"Can't add NULL node to Graph ID : "<<graph_id_);
    return -1;
  }
}
#endif
