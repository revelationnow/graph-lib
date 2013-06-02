#ifndef __LINK_HPP_
#define __LINK_HPP_

#include "graph.hpp"
using namespace std;
class Link
{
	private:
		int weight_;
		Node* node_[2];
    int link_id_;
    static int total_links;
	public:
		Link(int weight=0);
    int getId();
    int addNodeToEdge(Node* node,int edge);
    int nodeIDAttachedToEdge(int edge);
    Node* getNodeAtEdge(int edge);
};

#endif
