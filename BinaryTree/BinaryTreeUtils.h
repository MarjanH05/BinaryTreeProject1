#pragma once
#include <string>
#include <vector>
#include <stack>
#include <memory>
#include "TreeNode.h"

namespace BinaryTreeUtils {

    int precedence(const std::string& op);

    std::vector<std::string> tokenize(const std::string& expression);

    void processOperator(std::stack<std::shared_ptr<TreeNode>>& values,
        std::stack<std::shared_ptr<TreeNode>>& operators);

    bool isNegativeNumber(const std::vector<std::string>& tokens, size_t index);

}  // namespace BinaryTreeUtils
