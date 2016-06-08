/// \file node.hpp
#ifndef __NODE_HPP_
#define __NODE_HPP_

#include <vector>
#include <mutex>

#include "errHandler.hpp"
#include "common.hpp"
using namespace std;
template <class Tlink,class Tnode>
class Link;

//TODO : Remove this from here, why is this required?
template <class Tnode,class Tlink>
class Graph;

//! Node class
/*!
  This class represents each of the nodes of the graph.
  Each node has a list of links that it shares with other nodes
  A node is attached to another node by the link that it shares
  with the other node.
  Each node has an integer as its data
TODO: Why does it inherit Node_base, which is empty? Remove this
*/
template <class Tnode,class Tnodelink>
class Node : public Node_base
{
  protected:
    //! The list of links that a particular node shares with the other nodes in the graph
    vector<Link<Tnodelink,Tnode>*> links_;
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
    //! Member function to return the total nodes
    static int getTotalNodes();
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
    //! Member function to add a link to the node. The link needs to be updated by the caller to manager the edge
    void addLink(Link<Tnodelink, Tnode>* link);
    //! Get Node at the other edge of a given node and link
    Node<Tnode,Tnodelink>* getNodeAtOtherEdgeOfLink(Link<Tnodelink, Tnode>* link);
    //! Get the number of links attached to this node
    int getLinksSize()
    {
      return links_.size();
    }
    //! Return link at a certain index in the vector of links 
    Link<Tnodelink, Tnode>* getLinkAtIndex(int index)
    {
      if(index >=0 && index <= links_.size())
      {
        return links_[index];
      }
      else
      {
        OUTPUT_MSG(ERR_LEVEL_ERR,"index : "<<index<<" is out of range for Node ID : "<<this->getId()<<" number of links is : "<<links_.size());
        return NULL;
      }
    }


};

//! Link Class
/*!
  The Link class represents the link between two nodes.
  Each link has two edges, and the link itself has an
  integral weight.
  Two static integers are used to keep track of the number
  of links created and the link indices in use
TODO: Why does it inherit class Link_base which is empty?
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
    //! A mutex to protect node_[]
    mutex node_mutex_;
    //! A mutex to protect total_link_ids
    static mutex total_link_ids_mutex;
    //! A mutex to protect total_links
    static mutex total_links_mutex;
  public:
    enum Consts {
     FIRST_EDGE  = 0, SECOND_EDGE = 1, TOTAL_EDGES = 2
    };
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
    //! Member function to attach the node at the given edge. The caller must ensure that the node is updadted with the link information.
    void attachNodeAtEdge(Node<Tnode, Tlink>* node, int edge);
    //! Member function that returns the Node object at the given edge
    Node<Tnode,Tlink>* getNodeAtEdge(int edge);
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
    links_.pop_back();
  }
  links_mutex_.unlock();
  total_nodes_mutex.lock();
  total_nodes--;
  total_nodes_mutex.unlock();
}


/** \fn Node::getTotalNodes()
 * @brief This function returns the total number of nodes so far
 */
template<class Tnode, class Tlink>
int Node<Tnode,Tlink>::getTotalNodes()
{
  return total_nodes;
}

/** \fn Node::getDegree()
 * @brief Returns the degree of a node by counting the number of links it is attached to
 */
template<class Tnode,class Tlink>
int Node<Tnode,Tlink>::getDegree()
{
  int retVal = 0;
  links_mutex_.lock();
  retVal = links_.size();
  links_mutex_.unlock();
  return retVal;
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
  for(typename vector<Link<Tlink,Tnode>*>::iterator link_iterator = links_.begin();link_iterator != links_.end();++link_iterator)
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
  for(typename vector<Link<Tlink,Tnode>*>::iterator link_iterator = links_.begin();link_iterator != links_.end();++link_iterator)
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


/** \fn Node::addLink(Link* link)
 * @brief This function adds the link passed to the Node. 
 * It is the duty of the caller to ensure that the link is update with the node at it's edge
 */
template <class Tnode, class Tlink>
void Node<Tnode, Tlink>::addLink(Link<Tlink, Tnode>* link)
{
  links_mutex_.lock();
  links_.push_back(link);
  links_mutex_.unlock();
}

/** \fn Node::getNodeAtOtherEdgeOfLink(Link* link)
 * @brief This function returns the node which is at the other end of the passed link
 */
template<class Tnode, class Tlink>
Node<Tnode, Tlink>*  Node<Tnode, Tlink>::getNodeAtOtherEdgeOfLink(Link<Tlink, Tnode>* link )
{
  Node<Tnode, Tlink>* node = NULL;
  if(NULL == link)
  {
    node = NULL;
  }
  else if(this != link->getNodeAtEdge(Link<Tlink, Tnode>::FIRST_EDGE) && this != link->getNodeAtEdge(Link<Tlink, Tnode>::SECOND_EDGE))
  {
    OUTPUT_MSG(ERR_LEVEL_ERR, "Link : "<<link->getId()<<" is not attached to Node : "<<this->getId()<<". Cannot return NodeAtOtherEdge");
  }
  else
  {    
    if(this == link->getNodeAtEdge(Link<Tlink, Tnode>::FIRST_EDGE))
    {
      node = link->getNodeAtEdge(Link<Tlink, Tnode>::SECOND_EDGE);
    }
    else
    {
      node = link->getNodeAtEdge(Link<Tlink, Tnode>::FIRST_EDGE);
    }
    if(node != NULL)
    {
//      OUTPUT_MSG(ERR_LEVEL_INFO, "Found Node : "<<node->getId()<<" attached to Link : "<<link->getId());
    }
  }
  return node;
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
  //TODO: Shouldn't this be protected by mutex?
  node_mutex_.lock();
  node_[Link<Tlink,Tnode>::FIRST_EDGE] = NULL;
  node_[Link<Tlink,Tnode>::SECOND_EDGE] = NULL;
  node_mutex_.unlock();
}


/** \fn Link::~Link()
 * @brief Destructor
 */
template<class Tlink, class Tnode>
Link<Tlink, Tnode>::~Link()
{
  total_links_mutex.lock();
  total_links--;
  total_links_mutex.unlock();
}


/** \fn Link::Link(weight)
 * @brief Constructor, updates weight of the link and total links and total link ids.
 */
template <class Tlink,class Tnode>
Link<Tlink,Tnode>::Link(Tlink weight)
{
  weight_mutex_.lock();
  weight_ = weight;
  weight_mutex_.unlock();
  
  total_links_mutex.lock();
  link_id_mutex_.lock();
  link_id_ = total_links;
  link_id_mutex_.unlock();
  total_links++;
  total_links_mutex.unlock();
  
  node_mutex_.lock();
  node_[Link<Tlink,Tnode>::FIRST_EDGE] = NULL;
  node_[Link<Tlink,Tnode>::SECOND_EDGE] = NULL;
  node_mutex_.unlock();
}

/** \fn Link::getId()
 * @brief Retruns the ID of the link
 */
template <class Tlink,class Tnode>
int Link<Tlink,Tnode>::getId()
{
  int retVal = 0;
  link_id_mutex_.lock();
  retVal = link_id_;
  link_id_mutex_.unlock();
  return retVal;
}

/** \fn Link::getNodeAtEdge(int edge)
 * @brief returns the node attached to the link at the given edge. If no node is attached, it returns NULL.
 */
template <class Tlink,class Tnode>
Node<Tnode,Tlink>* Link<Tlink,Tnode>::getNodeAtEdge(int edge)
{
  Node<Tnode, Tlink>* retVal = NULL;
  node_mutex_.lock();
  if(edge != 0 && edge != 1)
  {
    OUTPUT_MSG(ERR_LEVEL_ERR, "Link ID : "<<link_id_<<" trying to get node at unsupported Edge : "<<edge);
    retVal = NULL;
  }
  else
  {
    retVal = node_[edge];
  }
  node_mutex_.unlock();
  return retVal;
}

/** \fn Link::detachNodeByEdge(int Edge)
 * @brief Detaches the node attached to the given edge, prints an error if no node is attached at the given edge.
 */
template <class Tlink,class Tnode>
void Link<Tlink,Tnode>::detachNodeByEdge(int edge)
{

  if((0==edge) || (1==edge))
  {
    node_mutex_.lock();
    node_[edge] = NULL;
    node_mutex_.unlock();
  }
  else
  {
    OUTPUT_MSG(ERR_LEVEL_ERR, "Link ID : "<<link_id_<<" trying to detach node at unsupported Edge : "<<edge);
  }
}


/** \fn Link::attachNodeAtEdge(Node *node, int Edge)
 * @brief This function attaches a node to the link at the given Edge. 
 * It is the caller's duty to update the node with this link
 */
template <class Tlink, class Tnode>
void Link<Tlink, Tnode>::attachNodeAtEdge(Node<Tnode, Tlink>* node, int edge)
{
  if((Link<Tlink, Tnode>::FIRST_EDGE != edge) && (Link<Tlink, Tnode>::SECOND_EDGE != edge))
  {
    OUTPUT_MSG(ERR_LEVEL_ERR, "Edge : "<<edge<<" is out of boundos");
    //TODO : Throw an exception here
  }
  else if(NULL != this->getNodeAtEdge(edge))
  {
    OUTPUT_MSG(ERR_LEVEL_ERR, "Link ID : "<<this->getId()<<" already has another Node : "<<(this->getNodeAtEdge(edge))->getId()<<" at Edge : "<<edge);
    //TODO : Throu exception here
  }
  else
  {
    this->node_[edge] = node;
  }
}
#endif 
