/// \file link.hpp
#ifndef __LINK_HPP_
#define __LINK_HPP_

#include "graph.hpp"
using namespace std;

//! Link Class
/*!
  The Link class represents the link between two nodes.
  Each link has two edges, and the link itself has an
  integral weight.
  Two static integers are used to keep track of the number
  of links created and the link indices in use
*/
class Link
{
  private:
    //! Weight of the link, can be an integer. A higher weight implies a stronger link
    int weight_;
    //! The two nodes connected to either edge of the link
    Node* node_[2];
    //! The unique ID assigned to a particular link
    int link_id_;
    //! A static member used to keep track of the total number of available links
    static int total_links;
    //! A static member used to keep track of assigned indices
    static int total_link_ids;
  public:
    //! Constructor which initializes the weight to 1
    Link(int weight=1);
    //! Member function which returns the unique index of the link
    int getId();
    //! Member function used to add a Node to one of the edges of the link
    int addNodeToEdge(Node* node,int edge);
    //! Member function that returns the node ID of the node attached to the specified edge
    int nodeIDAttachedToEdge(int edge);
    //! Member function to detach the node attached to an edge of the link
    void detachNodeByEdge(int edge);
    //! Member function that returns the Node object at the given edge
    Node* getNodeAtEdge(int edge);
    //! Friend function to attach nodes to edges
    friend int addLinkEdgeToNode(Node *node, Link* link, int edge);
};

#endif
