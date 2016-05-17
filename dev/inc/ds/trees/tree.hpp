///\file tree.hpp
#ifndef __TREE_HPP_
#define __TREE_HPP_
#include "graph.hpp"

using namespace std;
//! Tree class
/*!
 * This class is for a binary tree data structure.
 * It derives from the graph class and maintains at most two children per node.
 * It can be extended to also implement a parent pointer in the child nodes.
 */

template<class Tnode, class Tlink>
class Tree::public Graph<Tnode, Tlink>
{
  private:
    const int num_children_ = 2;
    
  public:
}


#endif
