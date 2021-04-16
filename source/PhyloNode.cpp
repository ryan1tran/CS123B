#include "PhyloNode.h"

// standard constructor
PhyloNode::PhyloNode(float height, PhyloNode *left, PhyloNode *right, const std::string &name) : height(height),
                                                                                                 left(left),
                                                                                                 right(right),
                                                                                                 name(name) {}

/* standard getters and setters below */

float PhyloNode::getHeight() const
{
    return height;
}

void PhyloNode::setHeight(float distance)
{
    PhyloNode::height = height;
}

PhyloNode *PhyloNode::getLeft() const
{
    return left;
}

void PhyloNode::setLeft(PhyloNode* left)
{
    PhyloNode::left = left;
}

PhyloNode *PhyloNode::getRight() const
{
    return right;
}

void PhyloNode::setRight(PhyloNode* right)
{
    PhyloNode::right = right;
}

const std::string &PhyloNode::getName() const
{
    return name;
}

void PhyloNode::setName(const std::string &name)
{
    PhyloNode::name = name;
}
