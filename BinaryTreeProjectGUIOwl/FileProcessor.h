#pragma once
#include <vector>
#include <string>

namespace UIUtils {
     std::string FormatResult(double value, int precision = 4);

     std::vector<std::pair<std::string, double>> ProcessFiles(const std::string& inputFile, const std::string& outputFile);
};