#pragma once
#include <string>
#include <memory>

struct TreeNode {
    std::string value;
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;

    TreeNode(const std::string& val) : value(val), left(nullptr), right(nullptr) {}
};

class IEvaluator {
public:
    virtual double Evaluate(std::shared_ptr<TreeNode> node) = 0;
    virtual ~IEvaluator() = default;
};