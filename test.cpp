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
#include <vector>

#include "TextFile.h"
#include "BinaryFile.h"

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
 * @section check test environment setup.
 *
 */

UNIT_TEST(test0, "Test environment'.")

    REQUIRE(system(NULL) != 0)

END_TEST


/**
 * @section test summary generation.
 *
 */

UNIT_TEST(test1, "Test summary generation for 'test1.txt'.")

    std::string fileName{"/test1.txt"};
    std::string inputFileName{inputDir + fileName};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -x -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(test2, "Test summary generation for 'test2.txt'.")

    std::string fileName{"/test2.txt"};
    std::string inputFileName{inputDir + fileName};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -x -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(test3, "Test summary generation for 'test3.txt'.")

    std::string fileName{"/test3.txt"};
    std::string inputFileName{inputDir + fileName};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -x -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(test4, "Test summary generation for 'test4.txt'.")

    std::string fileName{"/test4.txt"};
    std::string inputFileName{inputDir + fileName};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -x -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST


/**
 * @section test leading space generation.
 *
 */

UNIT_TEST(test1s, "Test leading space generation for 'test1.txt'.")

    std::string fileName{"/test1s.txt"};
    std::string inputFileName{inputDir + "/test1.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -s -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(test2s, "Test leading space generation for 'test2.txt'.")

    std::string fileName{"/test2s.txt"};
    std::string inputFileName{inputDir + "/test2.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -s -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(test3s, "Test leading space generation for 'test3.txt'.")

    std::string fileName{"/test3s.txt"};
    std::string inputFileName{inputDir + "/test3.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -s -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(test4s, "Test leading space generation for 'test4.txt'.")

    std::string fileName{"/test4s.txt"};
    std::string inputFileName{inputDir + "/test4.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -s -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST


/**
 * @section test leading tab generation.
 *
 */

UNIT_TEST(test1t, "Test leading tab generation for 'test1.txt'.")

    std::string fileName{"/test1t.txt"};
    std::string inputFileName{inputDir + "/test1.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -t -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(test2t, "Test leading tab generation for 'test2.txt'.")

    std::string fileName{"/test2t.txt"};
    std::string inputFileName{inputDir + "/test2.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -t -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(test3t, "Test leading tab generation for 'test3.txt'.")

    std::string fileName{"/test3t.txt"};
    std::string inputFileName{inputDir + "/test3.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -t -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(test4t, "Test leading tab generation for 'test4.txt'.")

    std::string fileName{"/test4t.txt"};
    std::string inputFileName{inputDir + "/test4.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -t -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST


/**
 * @section test trailing dos generation.
 *
 */

UNIT_TEST(test1d, "Test trailing dos generation for 'test1.txt'.")

    std::string fileName{"/test1d.txt"};
    std::string inputFileName{inputDir + "/test1.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -d -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(test2d, "Test trailing dos generation for 'test2.txt'.")

    std::string fileName{"/test2d.txt"};
    std::string inputFileName{inputDir + "/test2.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -d -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(test3d, "Test trailing dos generation for 'test3.txt'.")

    std::string fileName{"/test3d.txt"};
    std::string inputFileName{inputDir + "/test3.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -d -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(test4d, "Test trailing dos generation for 'test4.txt'.")

    std::string fileName{"/test4d.txt"};
    std::string inputFileName{inputDir + "/test4.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -d -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST


/**
 * @section test trailing unix generation.
 *
 */

UNIT_TEST(test1u, "Test trailing unix generation for 'test1.txt'.")

    std::string fileName{"/test1u.txt"};
    std::string inputFileName{inputDir + "/test1.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -u -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(test2u, "Test trailing unix generation for 'test2.txt'.")

    std::string fileName{"/test2u.txt"};
    std::string inputFileName{inputDir + "/test2.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -u -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(test3u, "Test trailing unix generation for 'test3.txt'.")

    std::string fileName{"/test3u.txt"};
    std::string inputFileName{inputDir + "/test3.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -u -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(test4u, "Test trailing unix generation for 'test4.txt'.")

    std::string fileName{"/test4u.txt"};
    std::string inputFileName{inputDir + "/test4.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -u -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST


/**
 * @section test leading space and trailing dos generation.
 *
 */

UNIT_TEST(test1sd, "Test leading space and trailing dos generation for 'test1.txt'.")

    std::string fileName{"/test1sd.txt"};
    std::string inputFileName{inputDir + "/test1.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -s -d -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(test2sd, "Test leading space and trailing dos generation for 'test2.txt'.")

    std::string fileName{"/test2sd.txt"};
    std::string inputFileName{inputDir + "/test2.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -s -d -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(test3sd, "Test leading space and trailing dos generation for 'test3.txt'.")

    std::string fileName{"/test3sd.txt"};
    std::string inputFileName{inputDir + "/test3.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -s -d -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(test4sd, "Test leading space and trailing dos generation for 'test4.txt'.")

    std::string fileName{"/test4sd.txt"};
    std::string inputFileName{inputDir + "/test4.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -s -d -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST


/**
 * @section test leading tab and trailing dos generation.
 *
 */

UNIT_TEST(test1td, "Test leading tab and trailing dos generation for 'test1.txt'.")

    std::string fileName{"/test1td.txt"};
    std::string inputFileName{inputDir + "/test1.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -t -d -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(test2td, "Test leading tab and trailing dos generation for 'test2.txt'.")

    std::string fileName{"/test2td.txt"};
    std::string inputFileName{inputDir + "/test2.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -t -d -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(test3td, "Test leading tab and trailing dos generation for 'test3.txt'.")

    std::string fileName{"/test3td.txt"};
    std::string inputFileName{inputDir + "/test3.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -t -d -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(test4td, "Test leading tab and trailing dos generation for 'test4.txt'.")

    std::string fileName{"/test4td.txt"};
    std::string inputFileName{inputDir + "/test4.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -t -d -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST


/**
 * @section test leading space and trailing unix generation.
 *
 */

UNIT_TEST(test1su, "Test leading space and trailing unix generation for 'test1.txt'.")

    std::string fileName{"/test1su.txt"};
    std::string inputFileName{inputDir + "/test1.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -s -u -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(test2su, "Test leading space and trailing unix generation for 'test2.txt'.")

    std::string fileName{"/test2su.txt"};
    std::string inputFileName{inputDir + "/test2.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -s -u -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(test3su, "Test leading space and trailing unix generation for 'test3.txt'.")

    std::string fileName{"/test3su.txt"};
    std::string inputFileName{inputDir + "/test3.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -s -u -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(test4su, "Test leading space and trailing unix generation for 'test4.txt'.")

    std::string fileName{"/test4su.txt"};
    std::string inputFileName{inputDir + "/test4.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -s -u -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST


/**
 * @section test leading tab and trailing unix generation.
 *
 */

UNIT_TEST(test1tu, "Test leading tab and trailing unix generation for 'test1.txt'.")

    std::string fileName{"/test1tu.txt"};
    std::string inputFileName{inputDir + "/test1.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -t -u -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(test2tu, "Test leading tab and trailing unix generation for 'test2.txt'.")

    std::string fileName{"/test2tu.txt"};
    std::string inputFileName{inputDir + "/test2.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -t -u -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(test3tu, "Test leading tab and trailing unix generation for 'test3.txt'.")

    std::string fileName{"/test3tu.txt"};
    std::string inputFileName{inputDir + "/test3.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -t -u -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(test4tu, "Test leading tab and trailing unix generation for 'test4.txt'.")

    std::string fileName{"/test4tu.txt"};
    std::string inputFileName{inputDir + "/test4.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -t -u -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    BinaryFile<> expected{expectedDir + fileName};
    expected.read();
    BinaryFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST


/**
 * @section test leading space to tab replacement.
 *
 */

UNIT_TEST(testSpace2, "Test leading space to tab replacement 'testSpace2.txt'.")

    std::string fileName{"/testSpace2.txt"};
    std::string inputFileName{inputDir + "/testSpace.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -t -2 -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    TextFile<> expected{expectedDir + fileName};
    expected.read();
    TextFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(testSpace4, "Test leading space to tab replacement 'testSpace4.txt'.")

    std::string fileName{"/testSpace4.txt"};
    std::string inputFileName{inputDir + "/testSpace.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -t -4 -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    TextFile<> expected{expectedDir + fileName};
    expected.read();
    TextFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(testSpace8, "Test leading space to tab replacement 'testSpace8.txt'.")

    std::string fileName{"/testSpace8.txt"};
    std::string inputFileName{inputDir + "/testSpace.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -t -8 -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    TextFile<> expected{expectedDir + fileName};
    expected.read();
    TextFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST


/**
 * @section test leading tab to space replacement.
 *
 */

UNIT_TEST(testTab2, "Test leading space to tab replacement 'testTab2.txt'.")

    std::string fileName{"/testTab2.txt"};
    std::string inputFileName{inputDir + "/testTab.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -s -2 -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    TextFile<> expected{expectedDir + fileName};
    expected.read();
    TextFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(testTab4, "Test leading space to tab replacement 'testTab4.txt'.")

    std::string fileName{"/testTab4.txt"};
    std::string inputFileName{inputDir + "/testTab.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -s -4 -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    TextFile<> expected{expectedDir + fileName};
    expected.read();
    TextFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST

UNIT_TEST(testTab8, "Test leading space to tab replacement 'testTab8.txt'.")

    std::string fileName{"/testTab8.txt"};
    std::string inputFileName{inputDir + "/testTab.txt"};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc -s -8 -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)

    TextFile<> expected{expectedDir + fileName};
    expected.read();
    TextFile<> output{outputFileName};
    output.read();
    REQUIRE(expected.equal(output))

END_TEST


/**
 * @section test option validation.
 *
 */

UNIT_TEST(testOptions0, "Test invalid option.")

    std::string command{"tfc -z"};
    REQUIRE(execute(command) != 0)

END_TEST

UNIT_TEST(testOptions1, "Test help option (both '-h' and '--help').")

    std::string command{"tfc -h"};
    REQUIRE(execute(command) == 0)

    command = "tfc --help";
    REQUIRE(execute(command) == 0)

END_TEST

UNIT_TEST(testOptions2, "Test version option (both '-v' and '--version').")

    std::string command{"tfc -v"};
    REQUIRE(execute(command) == 0)

    command = "tfc --version";
    REQUIRE(execute(command) == 0)

END_TEST

UNIT_TEST(testOptions3, "Test incomplete input option.")

    std::string command{"tfc -i"};
    REQUIRE(execute(command) != 0)

END_TEST

UNIT_TEST(testOptions4, "Test invalid input file.")

    std::string command{"tfc -i zxcv"};
    REQUIRE(execute(command) != 0)

END_TEST

UNIT_TEST(testOptions5, "Test source file replacement with summary (both '-r' and '--replace').")

    std::string fileName{"/testOptions.txt"};
    std::string inputFileName{inputDir + fileName};

    std::string command{"tfc -r " + inputFileName};
    REQUIRE(execute(command) != 0)

    command = "tfc --replace " + inputFileName;
    REQUIRE(execute(command) != 0)

END_TEST

UNIT_TEST(testOptions6, "Test source file and destination file are the same.")

    std::string fileName{"/testOptions.txt"};
    std::string inputFileName{inputDir + fileName};

    std::string command{"tfc --space --input " + inputFileName + " --output " + inputFileName};
    REQUIRE(execute(command) != 0)

END_TEST

UNIT_TEST(testOptions7, "Test overwriting of existing destination file.")

    std::string fileName{"/testOptions.txt"};
    std::string inputFileName{inputDir + fileName};
    std::string outputFileName{outputDir + fileName};

    std::string command{"tfc --tab -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)  // Create destination.

    command = "tfc --space -i " + inputFileName + " -o " + outputFileName;
    REQUIRE(execute(command) == 0)  // Overwrite destination.

END_TEST

UNIT_TEST(testOptions8, "Test overwriting of source file (both '-r' and '--replace').")

    std::string inputFileName{inputDir + "/testOptions.txt"};
    std::string outputFileName{outputDir + "/testOverwrite.txt"};

    std::string command{"tfc --dos -i " + inputFileName + " -o " + outputFileName};
    REQUIRE(execute(command) == 0)  // Create "testOverwrite.txt".

    command = "tfc --unix -r " + outputFileName;
    REQUIRE(execute(command) == 0)  // Replace "testOverwrite.txt".

    command = "tfc --dos --replace " + outputFileName;
    REQUIRE(execute(command) == 0)  // Replace "again testOverwrite.txt".

END_TEST


int runTests(const char * program)
{
    std::cout << "\nExecuting all tests.\n";

    TIMINGS_OFF

    RUN_TEST(test0)
    RUN_TEST(test1)
    RUN_TEST(test2)
    RUN_TEST(test3)
    RUN_TEST(test4)
    RUN_TEST(test1s)
    RUN_TEST(test2s)
    RUN_TEST(test3s)
    RUN_TEST(test4s)
    RUN_TEST(test1t)
    RUN_TEST(test2t)
    RUN_TEST(test3t)
    RUN_TEST(test4t)
    RUN_TEST(test1d)
    RUN_TEST(test2d)
    RUN_TEST(test3d)
    RUN_TEST(test4d)
    RUN_TEST(test1u)
    RUN_TEST(test2u)
    RUN_TEST(test3u)
    RUN_TEST(test4u)
    RUN_TEST(test1sd)
    RUN_TEST(test2sd)
    RUN_TEST(test3sd)
    RUN_TEST(test4sd)
    RUN_TEST(test1td)
    RUN_TEST(test2td)
    RUN_TEST(test3td)
    RUN_TEST(test4td)
    RUN_TEST(test1su)
    RUN_TEST(test2su)
    RUN_TEST(test3su)
    RUN_TEST(test4su)
    RUN_TEST(test1tu)
    RUN_TEST(test2tu)
    RUN_TEST(test3tu)
    RUN_TEST(test4tu)
    RUN_TEST(testSpace2)
    RUN_TEST(testSpace4)
    RUN_TEST(testSpace8)
    RUN_TEST(testTab2)
    RUN_TEST(testTab4)
    RUN_TEST(testTab8)
    RUN_TEST(testOptions0)
    RUN_TEST(testOptions1)
    RUN_TEST(testOptions2)
    RUN_TEST(testOptions3)
    RUN_TEST(testOptions4)
    RUN_TEST(testOptions5)
    RUN_TEST(testOptions6)
    RUN_TEST(testOptions7)
    RUN_TEST(testOptions8)

    const int err = FINISHED;
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
extern int init(const std::string & root, const std::string & input, const std::string & output, const std::string & expected);

int main(int argc, char *argv[])
{
    init(rootDir, inputDir, outputDir, expectedDir);

    return runTests(argv[0]);
}

