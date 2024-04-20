/**
 * @file    test.cpp
 * @author  Phil Lockett <phillockett65@gmail.com>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * https://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * Unit test code for the 'tfc' utility.
 *
 * Build using:
 *    g++ -std=c++20 -c -o test.o test.cpp
 *    g++ -std=c++20 -c -o gen.o gen.cpp
 *    g++ -std=c++20 -c -o unittest.o unittest.cpp
 *    g++ -std=c++20 -o test test.o gen.o unittest.o
 *
 * Test using:
 *    ./test
 *
 */

#include <iostream>

#include "TextFile.h"

#include "unittest.h"

/**
 * @section basic utility code.
 */

const std::string rootDir{"testdata"};
const std::string inputDir{rootDir + "/input"};
const std::string outputDir{rootDir + "/output"};
const std::string expectedDir{rootDir + "/expected"};


static std::vector<std::string> commands{};

static int execute(const std::string & command)
{
    commands.push_back(command);
    // std::cout << "Executing: '" << command << "'\n";

    return system(command.c_str());
}

static int displayCommands(void)
{
    for (auto & command : commands)
        std::cout << "  " << command << '\n';

    return commands.size();
}

/**
 * @section test script generation, currently not used.
 */

static int genTestScript(const std::string & fileName, const char * program)
{
    namespace fs = std::filesystem;

    if (std::ofstream os{fileName, std::ios::out})
    {
        os << "#!/bin/sh\n";
        os << '\n';
        os << "# This file was generated as \"" << fileName << "\" using " << program << '\n';
        os << "#\n";
        os << '\n';
        for (auto command : commands)
            os << command << '\n';

        os.close();

        // Ensure output scripts are executable.
        fs::perms permissions{fs::perms::owner_all |
            fs::perms::group_read | fs::perms::group_exec | 
            fs::perms::others_read | fs::perms::others_exec};
        fs::permissions(fileName, permissions, fs::perm_options::add);

        return 0;
    }

    return 1;
}

/**
 * @brief Constructs a Balancer command using supplied parameters and executes it.
 * 
 * @param options to be tested.
 * @param inputFileName without the input directory.
 * @param outputFileName with the output directory.
 * @return int the command return value.
 */
static int executeCommand(const std::string & options, const std::string & inputFileName, const std::string & outputFileName)
{
    std::string command{"Balancer " + options + " -i " + inputDir + "/" +inputFileName + " > " + outputFileName};

    return execute(command);
}

/**
 * @brief compares 2 files (the expected file with the generated file).
 * 
 * @param fileName without the expected directory.
 * @param outputFileName with the output directory.
 * @return true if the 2 files are the same, false otherwise.
 */
static bool compareAlbums(const std::string & fileName, const std::string & outputFileName)
{
    TextFile<> expected{expectedDir + fileName};
    expected.read();
    TextFile<> output{outputFileName};
    output.read();

    return expected.equal(output);
}

/**
 * @section check test environment setup.
 *
 */

UNIT_TEST(test0, "Test environment'.")

    REQUIRE(system(NULL) != 0)

END_TEST


/**
 * @section test input with a variety of time formats.
 *
 */

UNIT_TEST(testtime1, "Test input with a variety of time formats generating 'plain' output.")

    std::string fileName{"/testtime1.txt"};
    std::string outputFileName{outputDir + fileName};

    REQUIRE(executeCommand("-b 1 -p", "TestTimeFormats.txt", outputFileName) == 0)

    REQUIRE(compareAlbums(fileName, outputFileName))

END_TEST

UNIT_TEST(testtime2, "Test input with a variety of time formats generating 'hh:mm:ss' output.")

    std::string fileName{"/testtime2.txt"};
    std::string outputFileName{outputDir + fileName};

    REQUIRE(executeCommand("-b 1 ", "TestTimeFormats.txt", outputFileName) == 0)

    REQUIRE(compareAlbums(fileName, outputFileName))

END_TEST

UNIT_TEST(testtime3, "Test input with a variety of time formats generating 'shuffled' output.")

    std::string fileName{"/testtime3.txt"};
    std::string outputFileName{outputDir + fileName};

    REQUIRE(executeCommand("-b 1 -s", "TestTimeFormats.txt", outputFileName) == 0)

    REQUIRE(compareAlbums(fileName, outputFileName))

END_TEST

UNIT_TEST(testtime4, "Test input with a variety of time formats generating 'CSV' output.")

    std::string fileName{"/testtime4.txt"};
    std::string outputFileName{outputDir + fileName};

    REQUIRE(executeCommand("-b 1 -c -a '|'", "TestTimeFormats.txt", outputFileName) == 0)

    REQUIRE(compareAlbums(fileName, outputFileName))

END_TEST


/**
 * @section test output generation for multiple boxes.
 *
 */

UNIT_TEST(testoutput1, "Test 'split' output for 4 boxes (plain CSV).")

    std::string fileName{"/split.txt"};
    std::string outputFileName{outputDir + fileName};

    REQUIRE(executeCommand("-b 4 -c -a '|' -p", "BeaucoupFish.txt", outputFileName) == 0)

    REQUIRE(compareAlbums(fileName, outputFileName))

END_TEST

UNIT_TEST(testoutput2, "Test 'shuffle' output for 4 boxes (plain CSV).")

    std::string fileName{"/shuffle.txt"};
    std::string outputFileName{outputDir + fileName};

    REQUIRE(executeCommand("-b 4 -c -a '|' -p -s", "BeaucoupFish.txt", outputFileName) == 0)

    REQUIRE(compareAlbums(fileName, outputFileName))

END_TEST



int runTests(const char * program)
{
    std::cout << "\nExecuting all tests.\n";

    TIMINGS_OFF

    RUN_TEST(test0)
    RUN_TEST(testtime1)
    RUN_TEST(testtime2)
    RUN_TEST(testtime3)
    RUN_TEST(testtime4)
    RUN_TEST(testoutput1)
    RUN_TEST(testoutput2)


    const auto err{FINISHED};
    if (!err)
    {
        std::cout << "\nCommands executed:\n";
        displayCommands();
        // genTestScript("runTests.sh", program);
    }
    OUTPUT_SUMMARY;

    return err;
}

/**
 * Test system entry point.
 *
 * @param  argc - command line argument count.
 * @param  argv - command line argument vector.
 * @return error value or 0 if no errors.
 */

int main(int argc, char *argv[])
{
    return runTests(argv[0]);
}

