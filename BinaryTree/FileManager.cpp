#include "FileManager.h"
#include <iostream>

void FileManager::readFile() {
    EvaluatorLoader loader = LoadCalculationDll();
    if (!loader.isValid()) {
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        Tree tree;
        tree.buildTree(line);

        IEvaluator* evaluator = loader.create();
        if (!evaluator) {
            std::cerr << "Failed to create evaluator" << std::endl;
            return;
        }

        double result = evaluator->Evaluate(tree.root);
        writeFile(line, result);

        loader.destroy(evaluator);
    }

    std::cout << "Successfully added to the file" << std::endl;
}

void FileManager::writeFile(std::string line, double result) {
    outputFile << line << " = " << result << std::endl;
    std::cout << line << " = " << result << std::endl;
}

void FileManager::SetFiles(const std::string& input, const std::string& output) {
    inputFile.open(input);
    if (!inputFile.is_open()) {
        std::cerr << "Input file could not be opened" << std::endl;
        throw std::runtime_error("Failed to open input file: " + input);
    }
    outputFile.open(output, std::ios::app);
    if (!outputFile.is_open()) {
        std::cerr << "Output file could not be opened" << std::endl;
        throw std::runtime_error("Failed to open output file: " + output);
    }
}

void FileManager::CheckforErrors() {
    if (!inputFile.is_open()) {
        std::cerr << "Input file could not be opened" << std::endl;
        throw std::runtime_error("Input file is not open.");
    }
    if (!outputFile.is_open()) {
        std::cerr << "Output file could not be opened" << std::endl;
        throw std::runtime_error("Output file is not open.");
    }
}