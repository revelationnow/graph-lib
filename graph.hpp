#ifndef __GRAPH_HPP_
#define __GRAPH_HPP_
#include "common.hpp"
#include "node.hpp"
#include "link.hpp"

using namespace std;
int displayGraph(Node *start);
int removeLinkEdgeFromNode(Node *node, Link* link, int edge);
int addLinkEdgeToNode(Node* node, Link* link, int edge);

#endif
