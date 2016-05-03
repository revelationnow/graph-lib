/// \file node.hpp
#ifndef __NODE_HPP_
#define __NODE_HPP_

#include <list>
#include <mutex>

#include "errHandler.hpp"
#include "common.hpp"
using namespace std;
template <class Tlink,class Tnode>
class Link;

template <class Tnode,class Tlink>
class Graph;

//! Node class
/*!
  This class represents each of the nodes of the graph.
  Each node has a list of links that it shares with other nodes
  A node is attached to another node by the link that it shares
  with the other node.
  Each node has an integer as its data
*/
template <class Tnode,class Tnodelink>
class Node : public Node_base
{
  private:
    //! The list of links that a particular node shares with the other nodes in the graph
    list<Link<Tnodelink,Tnode>*> links_;
    //! The data that a paprticular node holds
    Tnode value_;
    //! The unique index of a particular node
    int node_id_;
    //! A static member that keeps track of the total number of active nodes
    static int total_nodes;
    //! A static member that tracks node indices in the graph
    static int total_node_ids;
    //! A mutex to protect access to the list of links from this node
    mutex links_mutex_;
    //! A mutex to protect the value in the node
    mutex value_mutex_;
    //! A mutex to protect node_id_
    mutex node_id_mutex_;
    //! A mutex to protect total_nodes
    static mutex total_nodes_mutex;
    //! A mutex to protect total_node_ids
    static mutex total_node_ids_mutex;
  public:
    //! Node constructor which initializes the value to 0
    Node();
    //! Node constructor which initializes the value to 0
    Node(Tnode value );
    //! Destructor which handles total_nodes
    ~Node();
    //! Member function that returns the cardinality of the node
    int getDegree();
    //! Member function that returns the data in the node
    Tnode getValue();
    //! Member function that returns the unique index of the node
    int getId();
    //! Member fuction that sets the value within the node
    void setValue(Tnode value);
    //! Member function that adds a particular edge of a link to the node
    int addLinkEdge(Link<Tnodelink,Tnode>* link,int edge);
    //! Member function that returns whether or not a link is attached to the node
    boolean linkAttachedToNode(Link<Tnodelink,Tnode>* link);
    //! Member function to remove a link from the node at a particular edge
    int removeLinkEdge(Link<Tnodelink,Tnode>* link,int edge);
    //! Member function to remove a link from the node at any edge
    int removeLink(Link<Tnodelink,Tnode>* link);
    //! Fried class Graph
    friend class Graph<Tnode,Tnodelink>;
};

//! Link Class
/*!
  The Link class represents the link between two nodes.
  Each link has two edges, and the link itself has an
  integral weight.
  Two static integers are used to keep track of the number
  of links created and the link indices in use
*/
template<class Tlink,class Tnode>
class Link : public Link_base
{
  private:
    //! Weight of the link, can be an integer. A higher weight implies a stronger link
    Tlink weight_;
    //! The two nodes connected to either edge of the link
    Node<Tnode,Tlink>* node_[2];
    //! The unique ID assigned to a particular link
    int link_id_;
    //! A static member used to keep track of the total number of available links
    static int total_links;
    //! A static member used to keep track of assigned indices
    static int total_link_ids;
    //! A mutex to protect weight_
    mutex weight_mutex_;
    //! A mutex to protect link_id_
    mutex link_id_mutex_;
    //! A mutex to protect total_link_ids
    static mutex total_link_ids_mutex;
    //! A mutex to protect total_links
    static mutex total_links_mutex;
  public:
    //! Default Constructor
    Link();
    //! Constructor which initializes the weight to 1
    Link(Tlink weight);
    //! Destructor which handles total_links
    ~Link();
    //! Member function which returns the unique index of the link
    int getId();
    //! Member function used to add a Node to one of the edges of the link
    int addNodeToEdge(Node<Tnode,Tlink>* node,int edge);
    //! Member function that returns the node ID of the node attached to the specified edge
    int nodeIDAttachedToEdge(int edge);
    //! Member function to detach the node attached to an edge of the link
    void detachNodeByEdge(int edge);
    //! Member function that returns the Node object at the given edge
    Node<Tnode,Tlink>* getNodeAtEdge(int edge);
    //! Fried class Graph to manipulate the link
    friend class Graph<Tnode,Tlink>;
};

/*!
  The Definitions for the Node class are below
 */

//! Initialize the number of total nodes to 0
template<class Tnode,class Tlink>
int Node<Tnode,Tlink>::total_nodes = 0;

template<class Tnode,class Tlink>
mutex Node<Tnode, Tlink>::total_nodes_mutex;

//! Initialize the number of total node IDs to 0
template<class Tnode,class Tlink>
int Node<Tnode,Tlink>::total_node_ids = 0;

template<class Tnode,class Tlink>
mutex Node<Tnode, Tlink>::total_node_ids_mutex;

/** \fn Node::Node()
 * @brief Default constructor : Just set the node_id_ and update the tota nodes and total node ids.
 */
template <class Tnode,class Tlink>
Node<Tnode,Tlink>::Node()
{
  total_node_ids_mutex.lock();
  node_id_mutex_.lock();
  node_id_ = total_node_ids;
  node_id_mutex_.unlock();
  total_node_ids++;
  total_node_ids_mutex.unlock();

  total_nodes_mutex.lock();
  total_nodes++;
  total_nodes_mutex.unlock();

}

/** \fn Node::Node(Tnode value) 
 * @brief Constructor to set the value and node_id_. Also update the total nodes and total node ids.
 */
template <class Tnode,class Tlink>
Node<Tnode,Tlink>::Node(Tnode value)
{
  value_mutex_.lock();
  value_ = value;
  value_mutex_.unlock();
  total_node_ids_mutex.lock();
  node_id_mutex_.lock();
  node_id_ = total_node_ids;
  node_id_mutex_.unlock();
  total_node_ids++;
  total_node_ids_mutex.unlock();

  total_nodes_mutex.lock();
  total_nodes++;
  total_nodes_mutex.unlock();
}


/** \fn Node::~Node()
 * @brief Destructor
 */
template<class Tnode, class Tlink>
Node<Tnode, Tlink>::~Node()
{
  Link<Tlink,Tnode> *t_link;
  links_mutex_.lock();
  for(int i = 0;i<links_.size();i++)
  {
    links_.pop_front();
  }
  links_mutex_.unlock();
  total_nodes_mutex.lock();
  total_nodes--;
  total_nodes_mutex.unlock();
}


/** \fn Node::getDegree()
 * @brief Returns the degree of a node by counting the number of links it is attached to
 */
template<class Tnode,class Tlink>
int Node<Tnode,Tlink>::getDegree()
{
  links_mutex_.lock();
  return links_.size();
  links_mutex_().unlock();
}

/** \fn Node::getValue() 
 * @brief Returns the value saved in the node
 */
template <class Tnode,class Tlink>
Tnode Node<Tnode,Tlink>::getValue()
{
  Tnode retVal;
  value_mutex_.lock();
  retVal = value_;
  value_mutex_.unlock();
  return retVal;
}
 
/** \fn Node::getId()
 * @brief Returns the node_id_
 */
template<class Tnode,class Tlink>
int Node<Tnode,Tlink>::getId()
{
  int retVal;
  node_id_mutex_.lock();
  retVal = node_id_;
  node_id_mutex_.unlock();
  return retVal;
}

/** \fn Node::setValue
 * @brief Sets the value of the node
 */
template<class Tnode,class Tlink>
void Node<Tnode,Tlink>::setValue(Tnode value)
{
  value_mutex_.lock();
  value_ = value;
  value_mutex_.unlock();
}

/** \fn Node::linkAttachedToNode(Link* link)
 * @brief returns TRUE if passed link is attached to the node, else returns FALSE.
 */
template<class Tnode,class Tlink>
boolean Node<Tnode,Tlink>::linkAttachedToNode(Link<Tlink,Tnode>* link)
{
  boolean return_value = FALSE;
  links_mutex_.lock();
  for(list<Link_base*>::iterator link_iterator = links_.begin();link_iterator != links_.end();++link_iterator)
  {
    if((*(Link<Tlink,Tnode>*)link_iterator)->getId() == link->getId())
    {
      return_value = TRUE;
    }
  }
  links_mutex_.unlock();
  return return_value;
}

/** \fn Node::removeLink(Link* link)
 * @brief Removes the passed link from the Node and returns 0 on success, if link is not found, returns -1
 */
template<class Tnode,class Tlink>
int Node<Tnode,Tlink>::removeLink(Link<Tlink,Tnode>* link)
{
  int return_value = -1;
  links_mutex_.lock();
  for(list<Link_base*>::iterator link_iterator = links_.begin();link_iterator != links_.end(); ++link_iterator)
  {
    if((*(Link<Tlink,Tnode>)link_iterator)->getId() == link->getId())
    {
      links_.erase(link_iterator);
      return_value = 0;
    }
  }
  links_mutex_.unlock();
  return return_value;
}


/*!
  The Definitions for the Link class are below
 */

template <class Tlink,class Tnode>
int Link<Tlink,Tnode>::total_links = 0;
template <class Tlink, class Tnode>
mutex Link<Tlink,Tnode>::total_links_mutex;
template <class Tlink,class Tnode> 
int Link<Tlink,Tnode>::total_link_ids = 0;
template <class Tlink, class Tnode>
mutex Link<Tlink,Tnode>::total_link_ids_mutex;

/** \fn Link::Link()
 * @brief Deafult constructor, updates total links and total link ids.
 */
template <class Tlink,class Tnode>
Link<Tlink,Tnode>::Link()
{
  total_links_mutex.lock();
  link_id_mutex_.lock();
  link_id_ = total_links;
  link_id_mutex_.unlock();
  total_links++;
  total_links_mutex.unlock();
  node_[0] = NULL;
  node_[1] = NULL;
}


/** \fn Link::~Link()
 * @brief Destructor
 */
template<class Tlink, class Tnode>
Link<Tlink, Tnode>::~Link()
{
  total_links--;
}


/** \fn Link::Link(weight)
 * @brief Constructor, updates weight of the link and total links and total link ids.
 */
template <class Tlink,class Tnode>
Link<Tlink,Tnode>::Link(Tlink weight)
{
  weight_ = weight;
  link_id_ = total_links;
  total_links++;
  node_[0] = NULL;
  node_[1] = NULL;
}

/** \fn Link::getId()
 * @brief Retruns the ID of the link
 */
template <class Tlink,class Tnode>
int Link<Tlink,Tnode>::getId()
{
  return link_id_;
}

/** \fn Link::getNodeAtEdge(int edge)
 * @brief returns the node attached to the link at the given edge. If no node is attached, it returns NULL.
 */
template <class Tlink,class Tnode>
Node<Tnode,Tlink>* Link<Tlink,Tnode>::getNodeAtEdge(int edge)
{
  if(edge != 0 && edge != 1)
  {
    OUTPUT_MSG(ERR, "Link ID : "<<link_id_<<" trying to get node at unsupported Edge : "<<edge);
    return NULL;
  }
  else
  {
    if(NULL != node_[edge])
    {
      return node_[edge];
    }
    else
    {
      return node_[edge];
    }
  }
}

/** \fn Link::detachNodeByEdge(int Edge)
 * @brief Detaches the node attached to the given edge, prints an error if no node is attached at the given edge.
 */
template <class Tlink,class Tnode>
void Link<Tlink,Tnode>::detachNodeByEdge(int edge)
{
  if((0==edge) || (1==edge))
  {
    node_[edge] = NULL;
  }
  else
  {
    OUTPUT_MSG(ERR, "Link ID : "<<link_id_<<" trying to detach node at unsupported Edge : "<<edge);
  }
}
#endif 
