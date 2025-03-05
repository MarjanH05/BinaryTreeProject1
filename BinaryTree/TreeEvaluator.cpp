//#include "TreeEvaluator.h"
//#include "SanityCheck.h"
//
//double EvaluateTree::Evaluate(std::shared_ptr<TreeNode> node) {
//    SanityCheck S;
//    if (!node) return 0;
//
//    if (isdigit(node->value[0]) || (node->value[0] == '-' && isdigit(node->value[1]))) {
//        return std::stod(node->value);
//    }
//
//    double lNode = Evaluate(node->left);
//    double rNode = Evaluate(node->right);
//
//    return operations[node->value](lNode, rNode);
//}
//
//
