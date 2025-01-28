#pragma once
#include <string>

struct TreeNode {
    std::string value;
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;

    TreeNode(const std::string& val) : value(val), left(nullptr), right(nullptr) {}
};

