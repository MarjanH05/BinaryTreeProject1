#include <iostream>

#include "FileManager.h"
#include "TreeEvaluator.h"

void FileManager::writeFile(std::string line, double result) {
    outputFile << line << " = " << result << std::endl;
    std::cout << line << " = " << result << std::endl;
}

void FileManager::readFile()
{
    std::string line;
    while (std::getline(inputFile, line)) {
        Tree tree;
        tree.buildTree(line);

        EvaluateTree evaluator;
        double result = evaluator.Evaluate(tree.root);
        writeFile(line, result); 
    }
    std::cout << "Successfully added to the file" << std::endl;
}

void FileManager::SetFiles(const std::string& input, const std::string& output) {
    inputFile.open(input);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Failed to open input file: " + input);
    }
    outputFile.open(output, std::ios::app);
    if (!outputFile.is_open()) {
        throw std::runtime_error("Failed to open output file: " + output);
    }
}

void FileManager::CheckforErrors() {
    if (!inputFile.is_open()) {
        throw std::runtime_error("Input file is not open.");
    }

    if (!outputFile.is_open()) {
        throw std::runtime_error("Output file is not open.");
    }
    FileManager::readFile();
}

