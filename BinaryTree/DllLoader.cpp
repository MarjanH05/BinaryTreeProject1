#include "DllLoader.h"
#include <iostream>

EvaluatorLoader::EvaluatorLoader() {
    hDll = LoadLibraryA("BinaryTreeCalculationDll.dll");
    if (!hDll) {
        status = LoaderStatus::DllNotFound;
        throw std::runtime_error("Failed to load BinaryTreeCalculationDll.dll");
        return;
    }
    createEvaluator = reinterpret_cast<IEvaluator * (*)()>(GetProcAddress(hDll, "CreateEvaluator"));
    destroyEvaluator = reinterpret_cast<void (*)(IEvaluator*)>(GetProcAddress(hDll, "DestroyEvaluator"));
    if (!createEvaluator || !destroyEvaluator) {
        FreeLibrary(hDll);
        hDll = nullptr;
        status = LoaderStatus::FunctionsNotFound;
        return;
    }
    status = LoaderStatus::Succeeded;
}

EvaluatorLoader::~EvaluatorLoader() {
    if (hDll) {
        FreeLibrary(hDll);
    }
}

IEvaluator* EvaluatorLoader::create() const {
    return createEvaluator ? createEvaluator() : nullptr;
}

void EvaluatorLoader::destroy(IEvaluator* evaluator) const {
    if (destroyEvaluator && evaluator) {
        destroyEvaluator(evaluator);
    }
}

LoaderStatus EvaluatorLoader::getStatus() const {
    return status;
}

EvaluatorLoader LoadCalculationDll() {
    return EvaluatorLoader();
}