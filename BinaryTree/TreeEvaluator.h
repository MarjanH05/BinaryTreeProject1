//#pragma once
//#include <memory>
//#include <string>
//#include <map> 
//#include <functional>
//#include <cmath>
//
//#include "TreeNode.h"
//#include "TreeEvaluator.h"
//
//class EvaluateTree : public IEvaluator {
//public:
//    EvaluateTree() {
//        operations["+"] = std::plus<double>();
//        operations["-"] = std::minus<double>();
//        operations["*"] = std::multiplies<double>();
//        operations["/"] = std::divides<double>();
//        operations["^"] = [](double base, double exponent) { return std::pow(base, exponent); };
//    }
//
//    double Evaluate(std::shared_ptr<TreeNode> node) override;
//
//private:
//    std::map<std::string, std::function<double(double, double)>> operations;
//};
