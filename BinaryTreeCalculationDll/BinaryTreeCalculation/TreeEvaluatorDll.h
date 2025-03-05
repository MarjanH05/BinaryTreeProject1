#pragma once

#include <memory>
#include <string>
#include <map> 
#include <functional>
#include <cmath>

#include "..\BinaryTree\TreeNode.h"

#ifdef BINARYTREECALCULATION_EXPORTS
#define TREEEVALUATORDLL_API __declspec(dllexport)
#else
#define TREEEVALUATORDLL_API __declspec(dllimport)
#endif


class IEvaluator {
public:
    virtual double Evaluate(std::shared_ptr<TreeNode> node) = 0;
};

class TREEEVALUATORDLL_API EvaluateTree : public IEvaluator {
public:
    EvaluateTree();
    double Evaluate(std::shared_ptr<TreeNode> node) override;

private:
    std::map<std::string, std::function<double(double, double)>> operations;
};
