#pragma once

#include <string>
#include <boost/program_options.hpp>

class ICommandParser {
private:
    virtual int parse(int argc, char* argv[], std::string& inputFile, std::string& outputFile) = 0;
};

class BoostCommand : public ICommandParser {
public:
    int parse(int argc, char* argv[], std::string& inputFile, std::string& outputFile);
};
 