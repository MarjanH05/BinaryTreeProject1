#pragma once
#include <windows.h>
#include <functional>
#include <memory> // Added for std::unique_ptr

#include "TreeNode.h" 

enum class LoaderStatus {
    Succeeded,
    DllNotFound,
    FunctionsNotFound
};

class EvaluatorLoader {
public:
    EvaluatorLoader();
    ~EvaluatorLoader();
    IEvaluator* create() const; 
    void destroy(IEvaluator* evaluator) const;
    LoaderStatus getStatus() const;
private:
    HMODULE hDll = nullptr;
    std::function<IEvaluator* ()> createEvaluator;
    std::function<void(IEvaluator*)> destroyEvaluator;
    LoaderStatus status = LoaderStatus::DllNotFound;
};

EvaluatorLoader LoadCalculationDll();