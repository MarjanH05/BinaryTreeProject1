#include "CommandLine.h" 
#include "FileManager.h"
#include "BinaryTree.h"

int main(int argc, char* argv[]) {
    std::string inputFile;
    std::string outputFile;

    BoostCommand CommandLineTry;
    if (CommandLineTry.parse(argc, argv, inputFile, outputFile) != 0) {
        return -1; // If there was an error in BoostCommand this should exit
    }

    FileManager FM;
    FM.SetFiles(inputFile, outputFile);
    FM.CheckforErrors();

    return 0;
}
