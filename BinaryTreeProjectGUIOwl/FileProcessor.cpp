#include "FileProcessor.h"
#include "../BinaryTree/FileManager.h"
#include <sstream>
#include <iomanip>

std::vector<std::pair<std::string, double>> ProcessFiles(const std::string& inputFile, const std::string& outputFile) {
    FileManager fm;
    fm.SetFiles(inputFile, outputFile);
    fm.CheckForErrors();
    fm.readFile();
    return fm.GetResults();
}

std::string FormatResult(double value) {
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(4) << value;
    std::string formattedResult = stream.str();
    formattedResult.erase(formattedResult.find_last_not_of('0') + 1, std::string::npos);
    if (!formattedResult.empty() && formattedResult.back() == '.')
        formattedResult.pop_back();
    return formattedResult;
}