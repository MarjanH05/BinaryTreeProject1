#pragma once

#include <map>
#include <functional>

#include "../../BinaryTree/TreeNode.h"
#include "../../BinaryTree/SanityCheck.h" 

#ifdef BINARYTREECALCULATION_EXPORTS  
#define BINARYTREECALCULATION_API __declspec(dllexport) 
#else
#define BINARYTREECALCULATION_API __declspec(dllimport)  
#endif

class BINARYTREECALCULATION_API EvaluateTree : public IEvaluator {
public:
    EvaluateTree();
    double Evaluate(std::shared_ptr<TreeNode> node) override;

private:
    std::map<std::string, std::function<double(double, double)>> operations;
};

extern "C" BINARYTREECALCULATION_API IEvaluator* CreateEvaluator();

extern "C" BINARYTREECALCULATION_API void DestroyEvaluator(IEvaluator* evaluator);
