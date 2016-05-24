///\file tree.hpp
#ifndef __TREE_HPP_
#define __TREE_HPP_
#include "graph.hpp"

using namespace std;
//! Tree class
/*!
 * This class is for a binary tree data structure.
 * It derives from the node class and maintains at most two children per node.
 * It can be extended to also implement a parent pointer in the child nodes.
 */

template<class Tnode>
class Tree:public Node<Tnode, int>
{
  protected:
    
  public:
    enum Consts {
    LEFT_LINK  = 0,  RIGHT_LINK = 1,  NUM_LINKS  = 2
    };
    //! Constructor
    Tree();
    //! Constructor
    Tree(Tnode val) : Node<Tnode, int>(val)
    {

    }
   
    //! Traversal : Different orders of traversal
    void traverseInOrder();
    void traversePreOrder();
    void traversePostOrder();
    //! Create a node and add it to the tree
    int createAndAddNode(Tnode val);
    //! Get the Left child of the node
    Tree<Tnode>* getLeftChild();
    //! Get the right child of the node
    Tree<Tnode>* getRightChild();


};

template<class Tnode>
Tree<Tnode> :: Tree()
{

}


template<class Tnode>
int Tree<Tnode> :: createAndAddNode(Tnode val)
{
  Tree<Tnode> *temp = new Tree<Tnode>(val);
  Tree<Tnode> *trav = this;
  Tree<Tnode> *next = this;
  OUTPUT_MSG(ERR_LEVEL_INFO, "Looking for location to add node");
  // Keep going left till free location is found : This is naive
  while(Tree::NUM_LINKS == trav->getLinksSize())
  {
    next = (Tree<Tnode>*)trav->getNodeAtOtherEdgeOfLink(trav->getLinkAtIndex(Tree<Tnode>::LEFT_LINK));
    if(next == NULL)
    {
      break;
    }
    trav = next;
  }
  OUTPUT_MSG(ERR_LEVEL_INFO, "Found location to add, Creating link and adding new node");

  //Create a link to attach the new node to the tree
  Link<int, Tnode> *link = new Link<int, Tnode>(1);

  link->attachNodeAtEdge(trav, Link<int,Tnode>::FIRST_EDGE);
  trav->addLink(link);
  link->attachNodeAtEdge(temp, Link<int,Tnode>::SECOND_EDGE);
  temp->addLink(link);

  OUTPUT_MSG(ERR_LEVEL_INFO, "Added new node");
  return 0;
}

template<class Tnode>
Tree<Tnode>* Tree<Tnode> :: getLeftChild()
{
  return (Tree<Tnode>*)this->getNodeAtOtherEdgeOfLink(this->getLinkAtIndex(Tree<Tnode>::LEFT_LINK));
}

  
template<class Tnode>
Tree<Tnode>* Tree<Tnode> :: getRightChild()
{
  return (Tree<Tnode>*)this->getNodeAtOtherEdgeOfLink(this->getLinkAtIndex(Tree<Tnode>::RIGHT_LINK));
}

template<class Tnode>
void Tree<Tnode> :: traversePreOrder()
{
  OUTPUT_MSG(ERR_LEVEL_INFO, this->getValue());
  if(this->getLeftChild() != NULL)
  {
    this->getLeftChild()->traversePreOrder();
  }

  if(this->getRightChild() != NULL)
  {
    this->getRightChild()->traversePreOrder();
  }

}

  
template<class Tnode>
void Tree<Tnode> :: traverseInOrder()
{
  if(this->getLeftChild() != NULL)
  {
    this->getLeftChild()->traverseInOrder();
  }

  OUTPUT_MSG(ERR_LEVEL_INFO, this->getValue());

  if(this->getRightChild() != NULL)
  {
    this->getRightChild()->traverseInOrder();
  }

}


template<class Tnode>
void Tree<Tnode> :: traversePostOrder()
{
  if(this->getLeftChild() != NULL)
  {
    this->getLeftChild()->traversePostOrder();
  }

  if(this->getRightChild() != NULL)
  {
    this->getRightChild()->traversePostOrder();
  }
  OUTPUT_MSG(ERR_LEVEL_INFO, this->getValue());

}
#endif
