#include <algorithm>
#include <stdexcept>

#include "BinaryTree.h"
#include "BinaryTreeUtils.h"

void Tree::buildTree(const std::string& expression) {
    auto tokens = tokenize(expression);
    std::stack<std::shared_ptr<TreeNode>> values;
    std::stack<std::shared_ptr<TreeNode>> operators;

    for (size_t i = 0; i < tokens.size(); ++i) {
        const auto& token = tokens[i];

        if (std::any_of(token.begin(), token.end(), ::isdigit)) {
            values.push(std::make_shared<TreeNode>(token));
        }
        else if (isNegativeNumber(tokens, i)) {
                std::string negativeNumber = token + tokens[i + 1];
                values.push(std::make_shared<TreeNode>(negativeNumber));
                ++i;
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^") {
            while (!operators.empty() && precedence(operators.top()->value) >= precedence(token)) {
                processOperator(values, operators);
            }
            operators.push(std::make_shared<TreeNode>(token));
        }
        else if (token == "(") {
            operators.push(std::make_shared<TreeNode>(token));
        }
        else if (token == ")") {
            while (!operators.empty() && operators.top()->value != "(") {
                processOperator(values, operators);
            }
            operators.pop(); // Pop the "("
        }
    }

    while (!operators.empty()) {
        processOperator(values, operators);
    }

    root = values.top();
}

//double EvaluateTree::Evaluate(std::shared_ptr<TreeNode> node, int depth) {
//    SanityCheck S; 
//    if (!node) return 0;
//
//    if (isdigit(node->value[0]) || (node->value[0] == '-' && isdigit(node->value[1]))) {
//        return std::stod(node->value);
//    }
//
//    double lNode = Evaluate(node->left, depth + 1);
//    double rNode = Evaluate(node->right, depth + 1);
//
//    return operations[node->value](lNode, rNode);
//}
