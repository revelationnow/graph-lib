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
    LEFT_LINK  = 0,  RIGHT_LINK = 1,  PARENT_LINK = 2, NUM_LINKS  = 3
    };
    //! Constructor
    Tree();
    //! Destructor
    ~Tree();
    //! Constructor
    Tree(Tnode val) : Node<Tnode, int>(val)
    {
      Link<int, Tnode> *temp = new Link<int, Tnode>;
      this->addLink(temp);
      temp->attachNodeAtEdge(this, Link<int, Tnode>::FIRST_EDGE);
      temp = new Link<int, Tnode>;
      this->addLink(temp);
      temp->attachNodeAtEdge(this, Link<int, Tnode>::FIRST_EDGE);
    }
   
    //! Traversal : Different orders of traversal
    void traverseInOrder();
    void traversePreOrder();
    void traversePostOrder();
    //! Create a node and add it to the tree on the left side
    int createAndAddNodeOnLeft(Tnode val);
    //! Create a node and add it to the tree on the right side
    int createAndAddNodeOnRight(Tnode val);
    //! Get the Left child of the node
    Tree<Tnode>* getLeftChild();
    //! Get the right child of the node
    Tree<Tnode>* getRightChild();
    //! Delete the left child of the node, it will delete all the children of the children also
    void deleteLeftChild();
    //! Delete the right child of the node, it will delete all the children of the children also
    void deleteRightChild();


};

template<class Tnode>
Tree<Tnode> :: Tree()
{
  Link<int, Tnode> *temp = new Link<int, Tnode>;
  this->addLink(temp);
  temp->attachNodeAtEdge(this, Link<int, Tnode>::FIRST_EDGE);
  temp = new Link<int, Tnode>;
  this->addLink(temp);
  temp->attachNodeAtEdge(this, Link<int, Tnode>::FIRST_EDGE);
}

template<class Tnode>
Tree<Tnode> :: ~Tree()
{
  this->deleteRightChild();
  this->deleteLeftChild();
}

template<class Tnode>
void Tree<Tnode> :: deleteLeftChild()
{
  Tree<Tnode> *temp = (Tree<Tnode>*)this->getNodeAtOtherEdgeOfLink(this->links_[Tree<Tnode>::LEFT_LINK]);
  delete this->links_[Tree<Tnode>::LEFT_LINK];
  this->links_.pop_back();  
  if(temp != NULL)
  {
    delete temp;
  }
}

template<class Tnode>
void Tree<Tnode> :: deleteRightChild()
{
  Tree<Tnode> *temp = (Tree<Tnode>*)this->getNodeAtOtherEdgeOfLink(this->links_[Tree<Tnode>::RIGHT_LINK]);
  delete this->links_[Tree<Tnode>::RIGHT_LINK];
  this->links_.pop_back();  
  if(temp != NULL)
  {
    delete temp;
  }

}


template<class Tnode>
int Tree<Tnode> :: createAndAddNodeOnLeft(Tnode val)
{
  // Keep going left till free location is found : This is naive
  
  //Check if there is a node at the other edge of the left link
  //Then if there is no node, add this value at that position
  if(this->getNodeAtOtherEdgeOfLink(this->links_[Tree<Tnode>::LEFT_LINK]) == NULL)
  {
    Tree<Tnode>* temp= new Tree<Tnode>(val);
    
    temp->addLink(this->links_[Tree<Tnode>::LEFT_LINK]);
    this->links_[Tree<Tnode>::LEFT_LINK]->attachNodeAtEdge(temp, Link<int, Tnode>::SECOND_EDGE);
    OUTPUT_MSG(ERR_LEVEL_INFO, "Added new Node Id : "<<temp->getId());

  }
  //Else call the same function but with the left child being the caller
  else
  {
    ((Tree<Tnode>*)(this->getNodeAtOtherEdgeOfLink(this->links_[Tree<Tnode>::LEFT_LINK])))->createAndAddNodeOnLeft(val);
  }
  
  return 0;
}

template<class Tnode>
int Tree<Tnode> :: createAndAddNodeOnRight(Tnode val)
{
  // Keep going left till free location is found : This is naive
  
  //Check if there is a node at the other edge of the left link
  //Then if there is no node, add this value at that position
  if(this->getNodeAtOtherEdgeOfLink(this->links_[Tree<Tnode>::RIGHT_LINK]) == NULL)
  {
    Tree<Tnode>* temp= new Tree<Tnode>(val);
    
    temp->addLink(this->links_[Tree<Tnode>::RIGHT_LINK]);
    this->links_[Tree<Tnode>::LEFT_LINK]->attachNodeAtEdge(temp, Link<int, Tnode>::SECOND_EDGE);
    OUTPUT_MSG(ERR_LEVEL_INFO, "Added new Node Id : "<<temp->getId());

  }
  //Else call the same function but with the left child being the caller
  else
  {
    ((Tree<Tnode>*)(this->getNodeAtOtherEdgeOfLink(this->links_[Tree<Tnode>::RIGHT_LINK])))->createAndAddNodeOnLeft(val);
  }
  
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
