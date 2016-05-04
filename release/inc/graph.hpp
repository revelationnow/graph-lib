/// \file graph.hpp
#ifndef __GRAPH_HPP_
#define __GRAPH_HPP_
#include "common.hpp"
#include "node.hpp"
#include "link.hpp"

using namespace std;
/*! \mainpage Graphlib
 *  \section Objective
 *  The purpose of this library is to provide a easy to use framework for various data structures and also to get some practise in writing code for different data structures and using different synchronization primitives
 *  \section Status
 *  Currently there is a long way to go for the code, the basic framework is in place and athough the progress has been slow due to real life commitments, changes are being made intermittently.
 */



//! Graph class
/*!
 * This class represents the overall graph.
 * All the Nodes and Links will be members of this graph, and the interactions
 * between the nodes and links will be handled through this class.
 * This is a sort of external interface for graph-lib, all manipulations of the nodes and
 * links should happen via this class.
 */
template<class Tnode, class Tlink>
class Graph
{
  private:
    //! List of all the nodes in this graph
    list<Node<Tnode,Tlink>*> nodes_;
    //! List of all the links in this graph
    list<Link<Tlink,Tnode>*> links_;
    //! The ID of this graph. This is just one in a unvierse of graphs.
    int graph_id_;
    //! A static member that keeps track of the number of graphs in the universe
    static int total_graphs;
    //! A static member to keep track of graph ids.
    static int total_graph_ids;
    //! Adds the passed link to the graph
    int addLinkToGraph(Link<Tlink,Tnode> * link);
    //! Adds the passed Node to the graph
    int addNodeToGraph(Node<Tnode,Tlink> * node);
  public:
    //! Graph constructor to initialize an empty graph
    Graph();
    //! Graph constructor which will start the graph with a list of unconnected nodes and links
    Graph(list<Node<Tnode,Tlink>*>, list<Link<Tlink,Tnode>*>);
    //! Graph destructor
    ~Graph();
    //! Function to print the graph structure in a graphical format
    int displayGraph();
    //! Function to create a new link and add it to the graph
    int createLink();
    //! Function to create a new link based on the passed weight and add it to the graph
    int createLink(Tlink val);
    //! Function to create a new node and add it to the graph
    int createNode();
    //! Function to create a new node based on the passed value and add it to the graph
    int createNode(Tnode val);
    //! Function to destroy a link and free the memory associated with it. Only applicable to links which are part of this graph.
    int destroyLink(int lid);
    //! Function to destroy a node and free the memory associated with it. Only applicable to nodes which are part of this graph
    int destroyNode(int nid);
    //! Function to get the pointer to the Node whose ID is passed
    Node<Tnode,Tlink>* getNodeById(int nid);
    //! Function to get the pointer to the link whose ID is passed
    Link<Tlink,Tnode>* getLinkById(int lid);
    //! Adds the passed link to the graph
    //int addLinkToGraph(Link<Tlink,Tnode> * link);
    //! Adds the passed Node to the graph
    //int addNodeToGraph(Node<Tnode,Tlink> * node);
    //! Attaches the node and link whose IDs are passed at the given edge of the link
    int attachLinkToNodeAtEdge(int lid,int nid, int edge);
    //! Detaches the node and link at the given edge
    int detachLinkFromNodeAtEdge(int lid,int nid, int edge);
};

//! Initialization of total graphs and total graph ids to 0
template<class Tnode,class Tlink>
int Graph<Tnode,Tlink>::total_graphs = 0;

template<class Tnode,class Tlink>
int Graph<Tnode,Tlink>::total_graph_ids = 0;

/** \fn Graph::Graph()
 * @brief The Default constructor
 */
template<class Tnode,class Tlink>
Graph<Tnode,Tlink>::Graph()
{
  graph_id_ = total_graph_ids;
  total_graphs++;
  total_graph_ids++;
}

/** \fn Graph::~Graph()
 * @brief Destructor for the Graph class. frees all the associated memory for Links and Node
 */
template<class Tnode, class Tlink>
Graph<Tnode, Tlink>::~Graph()
{
  Node<Tnode, Tlink> * t_node;
  int num_nodes = nodes_.size();
  for(int i =0; i < num_nodes; i++)
  {
    t_node = nodes_.front();
    nodes_.pop_front();    
    delete t_node;
  }

  Link<Tlink, Tnode> * t_link;
  int num_links = links_.size();
  for(int i=0; i < num_links; i++)
  {
    t_link = links_.front();
    links_.pop_front();
    delete t_link;
  }
  total_graphs--;
}


/** \fn Graph::displayGraph()
 * @brief Function to traverse the entire graph and print out the structure of the graph.
 * It uses Djikstra's algorithm to traverse the graph starting at the node at the back of the list of nodes.
 */
template<class Tnode,class Tlink>
int Graph<Tnode,Tlink>::displayGraph()
{
  //! \code{.cpp} Initialize the parameters for Djikstra's search 
  boolean* visited = new boolean[nodes_.size()];
  for(int i = 0; i < nodes_.size();i++)
  {
    visited[i] = FALSE;
  }
  int total_visited = 0;
  list<Node<Tnode,Tlink>*> t_nodes;
  Node<Tnode,Tlink>* t_node;
  Node<Tnode,Tlink>* l_node[2];
  t_nodes.push_back((nodes_.back()));

  //! \code{.cpp} Looping over the list of active nodes
  while(total_visited < Node<Tnode,Tlink>::total_nodes)
  {
    Node<Tnode,Tlink>* t_node = t_nodes.front();
    if(t_node == NULL)
    {
      break;
    }
    t_nodes.pop_front();
    OUTPUT_MSG(ERR_LEVEL_INFO, "Node : "<<t_node->getId());
    //! \code{.cpp} Set the visited flag for the current node to TRUE
    visited[t_node->getId()] = TRUE;
    total_visited++;
    //! \code{.cpp} Loop over all the neighbours of this node
    for(typename list<Link<Tlink,Tnode>*>::iterator link_iterator = t_node->links_.begin();link_iterator != t_node->links_.end(); ++link_iterator)
    {
      OUTPUT_MSG(ERR_LEVEL_INFO, "\t|| "<<((*link_iterator)->getNodeAtEdge(0))->getId()<<" ||----------<"<<(*link_iterator)->getId()<<">----------|| "<<((*link_iterator)->getNodeAtEdge(1))->getId()<<" ||");
      l_node[0] = (*link_iterator)->getNodeAtEdge(0);
      l_node[1] = (*link_iterator)->getNodeAtEdge(1);

      //! \code{.cpp} Insert nodes connected to the current node into the list of active nodes
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
  delete[] visited;
}

template<class Tnode, class Tlink>
int Graph<Tnode, Tlink>::createLink(Tlink val)
{
  Link<Tlink, Tnode>* t_link = new Link<Tlink,Tnode>(val);
  addLinkToGraph(t_link);
  return t_link->getId();
}

template<class Tnode, class Tlink>
int Graph<Tnode, Tlink>::createNode(Tnode val)
{
  Node<Tnode, Tlink>* t_node = new Node<Tnode, Tlink>(val);
  addNodeToGraph(t_node);
  return t_node->getId();
}

/** \fn Graph::attachLinkToNodeAtEdge(int lid, int nid, int edge)
 * @brief Function to attach a link to a node at the given edge
 */
template<class Tnode,class Tlink>
int Graph<Tnode,Tlink>::attachLinkToNodeAtEdge(int lid, int nid, int edge)
{
  Node<Tnode,Tlink>* node = getNodeById(nid);
  Link<Tlink,Tnode>* link = getLinkById(lid);

  if(NULL == node)
  {
    OUTPUT_MSG(ERR_LEVEL_ERR, "Can't find Node ID : "<<nid<<" in Graph : "<<graph_id_);
    return -1;
  }
  else if(NULL == link)
  {
    OUTPUT_MSG(ERR_LEVEL_ERR, "Can't find Link ID : "<<lid<<" in Graph : "<<graph_id_);
    return -1;
  }
  
  if((0 != edge) && (1 != edge))
  {
    OUTPUT_MSG(ERR_LEVEL_ERR, "Edge : "<<edge<<" is out of bounds");
    return -1;
  }
  
  if(NULL != link->getNodeAtEdge(edge))
  {
    OUTPUT_MSG(ERR_LEVEL_ERR, "Link ID : "<<lid<<" already has another Node : "<<(link->getNodeAtEdge(edge))->getId()<<" at Edge : "<<edge);
    return -2;
  }
  else
  {
    link->node_[edge] = node;
    node->links_.push_back(link);
    OUTPUT_MSG(ERR_LEVEL_INFO, "Attached Link : "<<link->getId()<<" to Node : "<<node->getId()<<" at Edge : "<<edge);
    return 0;
  }
}

/** \fn Graph::detachLinkFromNodeAtEdge 
 * @brief Function to detach the node and link attached the given edge of the link
 */
template<class Tnode,class Tlink>
int Graph<Tnode,Tlink>::detachLinkFromNodeAtEdge(int lid, int nid, int edge)
{

  Node<Tnode,Tlink>* node = getNodeById(nid);
  Link<Tlink,Tnode>* link = getLinkById(lid);
  if(NULL == node)
  {
    OUTPUT_MSG(ERR_LEVEL_ERR, "Can't find Node ID : "<<nid<<" in Graph : "<<graph_id_);
    return -1;
  }
  else if(NULL == link)
  {
    OUTPUT_MSG(ERR_LEVEL_ERR, "Can't find Link ID : "<<lid<<" in Graph : "<<graph_id_);
    return -1;
  }

  if((0 != edge) && (1 != edge))
  {
    OUTPUT_MSG(ERR_LEVEL_ERR, "Edge : "<<edge<<" is out of bounds");
    return -1;
  }
  if(link->node_[edge] != node)
  {
    OUTPUT_MSG(ERR_LEVEL_ERR,"Can't find Node ID "<<nid<<" at Edge : "<<edge<<" of Link ID : "<<lid);
    return -2;
  }
  else
  {
    link->detachNodeByEdge(edge);
    node->removeLink(link);
    return 0;
  }

}

/** \fn Graph::getNodeById(int nid)
 * @brief Function to return the pointer to the node indicated by the given node id
 */
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

/** \fn Graph::getLinkById(int lid)
 * @brief Function to return the pointer to the link indicated by the given link id
 */
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

/** \fn Graph::addLinkToGraph(Link* link)
 * @brief Function to add the passed link to the graph.
 */
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
    OUTPUT_MSG(ERR_LEVEL_ERR,"Can't add NULL link to Graph ID : "<<graph_id_);
    return -1;
  }
}


/** \fn Graph::addNodeToGraph(Node* node)
 * @brief Function to add the passed node to the graph.
 */
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
    OUTPUT_MSG(ERR_LEVEL_ERR,"Can't add NULL node to Graph ID : "<<graph_id_);
    return -1;
  }
}
#endif
