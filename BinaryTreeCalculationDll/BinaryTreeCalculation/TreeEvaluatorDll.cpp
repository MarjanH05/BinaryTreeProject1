#include "pch.h"

#include "TreeEvaluatorDll.h"
#include "..\BinaryTree\SanityCheck.h"

EvaluateTree::EvaluateTree() {
    operations["+"] = std::plus<double>();
    operations["-"] = std::minus<double>();
    operations["*"] = std::multiplies<double>();
    operations["/"] = std::divides<double>();
    operations["^"] = [](double base, double exponent) { return std::pow(base, exponent); };
}

double EvaluateTree::Evaluate(std::shared_ptr<TreeNode> node) {
    SanityCheck S;
    if (!node) return 0;

    if (isdigit(node->value[0]) || (node->value[0] == '-' && isdigit(node->value[1]))) {
        return std::stod(node->value);
    }

    double lNode = Evaluate(node->left);
    double rNode = Evaluate(node->right);

    return operations[node->value](lNode, rNode);
}
