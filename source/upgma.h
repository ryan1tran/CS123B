/* HEADER FILE FOR CREATING A PHYLOGENETIC TREE USING UPGMA */

#ifndef UPGMA_H
#define UPGMA_H

#include "PhyloNode.h"
#include <limits>
#include <vector>
#include <iostream>

PhyloNode* upgma(std::string** matrix);
PhyloNode* createTree(std::string** matrix, int rows, int columns, float min, int index, PhyloNode* root);
std::string** simplifyMatrix(std::string** matrix, int rows, int columns, int index);

#endif
