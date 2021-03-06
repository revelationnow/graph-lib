#include <iostream>
#include "tree.hpp"

using namespace std;

int main(int argc, char **argv)
{
  Tree<int> root;
  OUTPUT_MSG(ERR_LEVEL_INFO, "Starting Tree test");
  OUTPUT_MSG(ERR_LEVEL_INFO, "Adding 15 to tree");
  root.setValue(15);
  OUTPUT_MSG(ERR_LEVEL_INFO, "Adding 55 to tree");
  root.createAndAddNodeOnLeft(55);
  OUTPUT_MSG(ERR_LEVEL_INFO, "Adding 25 to tree");
  root.createAndAddNodeOnLeft(25);
  OUTPUT_MSG(ERR_LEVEL_INFO, "Adding 65 to tree");
  root.createAndAddNodeOnLeft(65);
  OUTPUT_MSG(ERR_LEVEL_INFO, "Adding 75 to tree");
  root.createAndAddNodeOnLeft(75);
  OUTPUT_MSG(ERR_LEVEL_INFO, "Going to perform preorder traversal");
  root.traversePreOrder();

  return 0;
}
