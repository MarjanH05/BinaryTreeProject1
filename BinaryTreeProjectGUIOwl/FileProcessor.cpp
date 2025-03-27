#include "FileProcessor.h"
#include "../BinaryTree/FileManager.h"
#include <sstream>
#include <iomanip>

std::string UIUtils::FormatResult(double value, int precision)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << value;
    std::string formattedResult = oss.str();

    formattedResult.erase(formattedResult.find_last_not_of('0') + 1, std::string::npos);
    if (formattedResult.back() == '.')
        formattedResult.pop_back();
    return formattedResult;
}

std::vector<std::pair<std::string, double>> UIUtils::ProcessFiles(const std::string& inputFile, const std::string& outputFile)
{
    FileManager fm;
    fm.SetFiles(inputFile, outputFile);
    fm.readFile();
    return fm.GetResults();
}