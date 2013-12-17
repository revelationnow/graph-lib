/// \file node.hpp
#ifndef __NODE_HPP_
#define __NODE_HPP_

#include <list>

#include "graph.hpp"

using namespace std;
//! Node class
/*!
  This class represents each of the nodes of the graph.
  Each node has a list of links that it shares with other nodes
  A node is attached to another node by the link that it shares
  with the other node.
  Each node has an integer as its data
*/
class Node
{
  private:
    //! The list of links that a particular node shares with the other nodes in the graph
    list<Link*> links_;
    //! The data that a paprticular node holds
    int value_;
    //! The unique index of a particular node
    int node_id_;
    //! A static member that keeps track of the total number of active nodes
    static int total_nodes;
    //! A static member that tracks node indices in the graph
    static int total_node_ids;
  public:
    //! Node constructor which initializes the value to 0
    Node(int value = 0);
    //! Member function that returns the cardinality of the node
    int getDegree();
    //! Member function that returns the data in the node
    int getValue();
    //! Member function that returns the unique index of the node
    int getId();
    //! Member fuction that sets the value within the node
    void setValue(int value);
    //! Member function that adds a particular edge of a link to the node
    int addLinkEdge(Link* link,int edge);
    //! Member function that returns whether or not a link is attached to the node
    boolean linkAttachedToNode(Link* link);
    //! Member function to remove a link from the node at a particular edge
    int removeLinkEdge(Link* link,int edge);
    //! Member function to remove a link from the node at any edge
    int removeLink(Link* link);
    //! Friend function to visualize the graph
    friend int displayGraph(Node* start);
    //! Friend function to add a link at a particular edge to the node
    friend int addLinkEdgeToNode(Node *node, Link* link, int edge);
};

#endif 
