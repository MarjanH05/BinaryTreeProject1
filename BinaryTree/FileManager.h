#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "BinaryTree.h"
#include "DllLoader.h"

class IFileReader {
public:
    virtual void readFile() = 0;
};

class IFileWriter {
public:
    virtual void writeFile(std::string line, double result) = 0;
};

class FileManager : public IFileWriter, IFileReader {
public:
    void SetFiles(const std::string& input, const std::string& output);
    void CheckforErrors();
    void readFile() override;
    void writeFile(std::string line, double result) override;

private:
    std::ifstream inputFile;
    std::ofstream outputFile;
};