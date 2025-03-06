#include "CommandLine.h" 
#include "FileManager.h"
#include "BinaryTree.h"

#include <Windows.h>

int main(int argc, char* argv[]) {
    std::string inputFile;
    std::string outputFile;
    BoostCommand CommandLineTry;

    if (CommandLineTry.parse(argc, argv, inputFile, outputFile) != 0) {
        return -1; 
    }

    FileManager FM;
    FM.SetFiles(inputFile, outputFile);
    FM.CheckforErrors();
    FM.readFile();

    return 0;
}