/* CLASS FOR CREATING THE PHYLOGENETIC TREE */

#ifndef PHYLONODE_H
#define PHYLONODE_H

#include <string>

class PhyloNode
{
    private:
        float height;
        PhyloNode* left;
        PhyloNode* right;
        std::string name;

    public:
        PhyloNode(float height, PhyloNode *left, PhyloNode *right, const std::string &name);
        float getHeight() const;
        void setHeight(float height);
        PhyloNode* getLeft() const;
        void setLeft(PhyloNode* above);
        PhyloNode* getRight() const;
        void setRight(PhyloNode* below);
        const std::string &getName() const;
        void setName(const std::string &nameRight);
};

#endif
