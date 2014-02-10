/// \file graph.hpp
#ifndef __GRAPH_HPP_
#define __GRAPH_HPP_
#include "common.hpp"
#include "node.hpp"
#include "link.hpp"

using namespace std;
int displayGraph(Node *start);
int removeLinkEdgeFromNode(Node *node, Link* link, int edge);
int addLinkEdgeToNode(Node* node, Link* link, int edge);

class Graph
{
  private:
    list<Node*> nodes_;
    list<Link*> links_;
    int graph_id_;
    static int total_graphs;
    static int total_graph_ids;
  public:
    Graph();
    Graph(list<Node*>, list<Link*>);
    int displayGraph();
    int createLink();
    int createNode();
    int destroyLink(int lid);
    int destroyNode(int nid);
    Node* getNodeById(int nid);
    Link* getLinkById(int lid);
    int addLinkToGraph(Link *link);
    int addNodeToGraph(Node *node);
    int attachLinkToNodeAtEdge(int lid,int nid, int edge);
    int detachLinkFromNodeAtEdge(int lid,int nid, int edge);
};
#endif
