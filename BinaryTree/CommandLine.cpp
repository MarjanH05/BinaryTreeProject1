#pragma once
#include <iostream>

#include "CommandLine.h"

int BoostCommand::parse(int argc, char* argv[], std::string& inputFile, std::string& outputFile) {
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "Show help message")
        ("source,s", boost::program_options::value<std::string>(&inputFile)->required(), "Input source file")
        ("result,r", boost::program_options::value<std::string>(&outputFile)->required(), "Output result file");

    boost::program_options::variables_map vm;
    try {
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
  
        if (vm.count("help")) {
            std::cout << desc << std::endl;
            return 0;
        }

        boost::program_options::notify(vm);
        return 0;
    }
    catch (const boost::program_options::required_option& ex) {
        std::cerr << "Error: Missing required option. " << ex.what() << std::endl;
        return 1;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 2;
    }
    catch (...) {
        std::cerr << "An unknown error occurred!" << std::endl;
        return 3;
    }
}
