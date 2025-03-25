#pragma once 
#include <memory>
#include <string>
#include <map> 
#include <functional>
#include <cmath>
#include "TreeNode.h"

class ITreeBuilder {
public:
    virtual void buildTree(std::string& expression) = 0;
};

class Tree : public ITreeBuilder{
public:
    std::shared_ptr<TreeNode> root;
    void buildTree(std::string& expression) override;

};
