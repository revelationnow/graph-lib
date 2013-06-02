#ifndef __NODE_HPP_
#define __NODE_HPP_

#include <list>

#include "graph.hpp"

using namespace std;
class Node
{
  private:
    list<Link*> links_;
    int value_;
    int node_id_;
    static int total_nodes;
  public:
    Node(int value = 0);
    int getDegree();
    int getValue();
    int getId();
    void setValue(int value);
    int addLinkEdge(Link* link,int edge);
    boolean linkAttachedToNode(Link* link);
    int removeLinkEdge(Link* link,int edge);
    friend int displayGraph(Node* start);
};

#endif 
