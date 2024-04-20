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


bool compareAlbums(const TextFile<> & expected, const TextFile<> & output)
{
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
    std::string inputFileName{inputDir + "/TestTimeFormats.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"Balancer -b 1 -p -i " + inputFileName + " > " + outputFileName};
    REQUIRE(execute(command) == 0)

    TextFile<> expected{expectedDir + fileName};
    expected.read();
    TextFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(testtime2, "Test input with a variety of time formats generating 'hh:mm:ss' output.")

    std::string fileName{"/testtime2.txt"};
    std::string inputFileName{inputDir + "/TestTimeFormats.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"Balancer -b 1 -i " + inputFileName + " > " + outputFileName};
    REQUIRE(execute(command) == 0)

    TextFile<> expected{expectedDir + fileName};
    expected.read();
    TextFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(testtime3, "Test input with a variety of time formats generating 'shuffled' output.")

    std::string fileName{"/testtime3.txt"};
    std::string inputFileName{inputDir + "/TestTimeFormats.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"Balancer -b 1 -s -i " + inputFileName + " > " + outputFileName};
    REQUIRE(execute(command) == 0)

    TextFile<> expected{expectedDir + fileName};
    expected.read();
    TextFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(testtime4, "Test input with a variety of time formats generating 'CSV' output.")

    std::string fileName{"/testtime4.txt"};
    std::string inputFileName{inputDir + "/TestTimeFormats.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"Balancer -b 1 -c -a '|' -i " + inputFileName + " > " + outputFileName};
    REQUIRE(execute(command) == 0)

    TextFile<> expected{expectedDir + fileName};
    expected.read();
    TextFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST


/**
 * @section test output generation for multiple boxes.
 *
 */

UNIT_TEST(testoutput1, "Test 'split' output for 4 boxes (plain CSV).")

    std::string fileName{"/split.txt"};
    std::string inputFileName{inputDir + "/BeaucoupFish.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"Balancer -b 4 -c -a '|' -p -i " + inputFileName + " > " + outputFileName};
    REQUIRE(execute(command) == 0)

    TextFile<> expected{expectedDir + fileName};
    expected.read();
    TextFile<> output{outputFileName};
    output.read();
    REQUIRE(compareAlbums(expected, output))

END_TEST

UNIT_TEST(testoutput2, "Test 'shuffle' output for 4 boxes (plain CSV).")

    std::string fileName{"/shuffle.txt"};
    std::string inputFileName{inputDir + "/BeaucoupFish.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"Balancer -b 4 -c -a '|' -p -s -i " + inputFileName + " > " + outputFileName};
    REQUIRE(execute(command) == 0)

    TextFile<> expected{expectedDir + fileName};
    expected.read();
    TextFile<> output{outputFileName};
    output.read();
    REQUIRE(compareAlbums(expected, output))

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

