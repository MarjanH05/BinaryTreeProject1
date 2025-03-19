#pragma once
#include <vector>
#include <string>

std::vector<std::pair<std::string, double>> ProcessFiles(const std::string& inputFile, const std::string& outputFile);
std::string FormatResult(double value); 