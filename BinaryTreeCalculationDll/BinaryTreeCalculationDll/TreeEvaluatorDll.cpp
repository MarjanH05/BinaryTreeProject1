#include "TreeEvaluatorDll.h"
#include <cmath>

EvaluateTree::EvaluateTree() {
    SanityCheck S;
    operations["+"] = std::plus<double>();
    operations["-"] = std::minus<double>();
    operations["*"] = std::multiplies<double>();
    operations["/"] = std::divides<double>();
    operations["^"] = [](double base, double exponent) { return std::pow(base, exponent); };
}

double EvaluateTree::Evaluate(std::shared_ptr<TreeNode> node) {
    if (!node) return 0;

    if (isdigit(node->value[0]) || (node->value[0] == '-' && isdigit(node->value[1]))) {
        return std::stod(node->value);
    }

    double lNode = Evaluate(node->left);
    double rNode = Evaluate(node->right);

    return operations[node->value](lNode, rNode);
}

extern "C" BINARYTREECALCULATION_API IEvaluator* CreateEvaluator() {
    return new EvaluateTree();
}

extern "C" BINARYTREECALCULATION_API void DestroyEvaluator(IEvaluator* evaluator) {
    delete evaluator;
}
