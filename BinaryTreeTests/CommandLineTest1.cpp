#pragma once
#include <gtest/gtest.h>
#include <boost/program_options.hpp>
#include "../BinaryTree/CommandLine.h" 

TEST(BoostCommandTest, ValidInput) {
    int argc = 5;
    const char* argv[] = { "program", "--source", "input.txt", "--result", "output.txt" };
    std::string inputFile;
    std::string outputFile;

    BoostCommand command;
    int result = command.parse(argc, const_cast<char**>(argv), inputFile, outputFile);

    EXPECT_EQ(result, 0);
    EXPECT_EQ(inputFile, "input.txt");
    EXPECT_EQ(outputFile, "output.txt");
}

TEST(BoostCommandTest, MissingSourceFile) {
    int argc = 3;
    const char* argv[] = { "program", "--result", "output.txt" };
    std::string inputFile;
    std::string outputFile;

    BoostCommand command;
    int result = command.parse(argc, const_cast<char**>(argv), inputFile, outputFile);

    EXPECT_EQ(result, 1);
}

TEST(BoostCommandTest, MissingResultFile) {
    int argc = 3;
    const char* argv[] = { "program", "--source", "input.txt" };
    std::string inputFile;
    std::string outputFile;

    BoostCommand command;
    int result = command.parse(argc, const_cast<char**>(argv), inputFile, outputFile);

    EXPECT_EQ(result, 1);
}

TEST(BoostCommandTest, InvalidOption) {
    int argc = 4;
    const char* argv[] = { "program", "--unknown", "value", "--result", "output.txt" };
    std::string inputFile;
    std::string outputFile;

    BoostCommand command;
    int result = command.parse(argc, const_cast<char**>(argv), inputFile, outputFile);

    EXPECT_EQ(result, 2);
}

TEST(BoostCommandTest, UnknownError) {
    int argc = 3;
    const char* argv[] = { "program", "--source", "input.txt", "--result", "output.txt" };
    std::string inputFile;
    std::string outputFile;

    BoostCommand command;
    int result = command.parse(argc, const_cast<char**>(argv), inputFile, outputFile);

    EXPECT_NE(result, 3);
}
