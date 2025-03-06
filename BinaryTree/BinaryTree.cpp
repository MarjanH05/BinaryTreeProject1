#include <algorithm>
#include <stdexcept>

#include "BinaryTree.h"
#include "BinaryTreeUtils.h"

void Tree::buildTree(const std::string& expression) {
    auto tokens = BinaryTreeUtils::tokenize(expression);
    std::stack<std::shared_ptr<TreeNode>> values;
    std::stack<std::shared_ptr<TreeNode>> operators;

    for (size_t i = 0; i < tokens.size(); ++i) {
        const auto& token = tokens[i];

        if (std::any_of(token.begin(), token.end(), ::isdigit)) {
            values.push(std::make_shared<TreeNode>(token));
        }
        else if (BinaryTreeUtils::isNegativeNumber(tokens, i)) {
                std::string negativeNumber = token + tokens[i + 1];
                values.push(std::make_shared<TreeNode>(negativeNumber));
                ++i;
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^") {
            while (!operators.empty() && BinaryTreeUtils::precedence(operators.top()->value) >= BinaryTreeUtils::precedence(token)) {
                BinaryTreeUtils::processOperator(values, operators);
            }
            operators.push(std::make_shared<TreeNode>(token));
        }
        else if (token == "(") {
            operators.push(std::make_shared<TreeNode>(token));
        }
        else if (token == ")") {
            while (!operators.empty() && operators.top()->value != "(") {
                BinaryTreeUtils::processOperator(values, operators);
            }
            operators.pop();
        }
    }

    while (!operators.empty()) {
        BinaryTreeUtils::processOperator(values, operators);
    }

    root = values.top();
}


