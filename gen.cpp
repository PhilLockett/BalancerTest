/**
 * @file    gen.cpp
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
 * Test file generator for the 'tfc' utility.
 *
 */

#include <iostream>
#include <vector>

#include "TextFile.h"
#include "BinaryFile.h"

/**
 * @section basic utility code.
 */

std::string inputDir{};
std::string outputDir{};
std::string expectedDir{};

static bool createDirectory(const std::string & path)
{
    return std::filesystem::create_directories(path);
}

static void deleteDirectory(const std::string & path)
{
    std::filesystem::remove_all(path); // Delete directory and contents.
}

static int writeSummaryFile(const std::string & fileName, const std::string & line2)
{
    const std::string expected{expectedDir + fileName};

    std::cout << "Generating summary file " << expected << "\n";
    if (std::ofstream os{expected, std::ios::out})
    {
        os << inputDir << fileName << '\n' << line2 << '\n';
        return 0;
    }

    return 1;
}


/**
 * @section test summary generation.
 *
 */
int summaryTests(void)
{
/* A mix of space and tab leading, space and tab in middle and CR LF EOL.
testdata/input/test1.txt
  Total Lines:  9
Line begining:
  Space only:   1
  Tab only:     1
  Neither:      3
  Both:         4
Line ending:
  Dos:          9
  Unix:         0
  Malformed:    0
*/
    std::vector<char> test1{ 
        '\t', ' ', ' ', 'S', 'u', 'b', ' ', '1', '\r', '\n', 
        ' ', '\t', ' ', ' ', 'C', 'R', 'L', 'F', '.', 'm', '\r', '\n', 
        ' ', '\t', '\r', '\n', 
        '\t', ' ', '\r', '\n', 
        '\t', 'H', '\t', 'i', '\r', '\n', 
        ' ', 'H', '\t', 'i', '\r', '\n', 
        'H', '\t', 'i', '\r', '\n', 
        'H', ' ', 'i', '\r', '\n', 
        '\r', '\n' 
    };
    std::string filename{"/test1.txt"};
    BinaryFile<> input{inputDir + filename};
    input.write(test1);
    writeSummaryFile(filename, "9 1 1 3 4 9 0 0");

/* A mix of space and tab leading, space and tab in middle and only LF EOL.
testdata/input/test2.txt
  Total Lines:  9
Line begining:
  Space only:   1
  Tab only:     1
  Neither:      3
  Both:         4
Line ending:
  Dos:          0
  Unix:         9
  Malformed:    0
*/
    std::vector<char> test2{ 
        '\t', ' ', ' ', 'S', 'u', 'b', ' ', '1', '\n', 
        ' ', '\t', ' ', ' ', 'L', 'F', '.', 'm', '\n', 
        ' ', '\t', '\n', 
        '\t', ' ', '\n', 
        '\t', 'H', '\t', 'i', '\n', 
        ' ', 'H', '\t', 'i', '\n', 
        'H', '\t', 'i', '\n', 
        'H', ' ', 'i', '\n', 
        '\n' 
    };
    filename = "/test2.txt";
    input.setFileName(inputDir + filename);
    input.write(test2);
    writeSummaryFile(filename, "9 1 1 3 4 0 9 0");

/* A mix of space and tab leading, space and tab in middle and mix of CR LF and LF EOL.
testdata/input/test3.txt
  Total Lines:  9
Line begining:
  Space only:   1
  Tab only:     1
  Neither:      3
  Both:         4
Line ending:
  Dos:          6
  Unix:         3
  Malformed:    0
*/
    std::vector<char> test3{ 
        '\t', ' ', ' ', 'M', 'i', 'x', ' ', '1', '\r', '\n', 
        ' ', '\t', ' ', ' ', 'C', 'R', 'L', 'F', '.', 'm', '\n', 
        ' ', '\t', '\r', '\n', 
        '\t', ' ', '\n', 
        '\t', 'H', '\t', 'i', '\r', '\n', 
        ' ', 'H', '\t', 'i', '\r', '\n', 
        'H', '\t', 'i', '\n', 
        'H', ' ', 'i', '\r', '\n', 
        '\r', '\n' 
    };
    filename = "/test3.txt";
    input.setFileName(inputDir + filename);
    input.write(test3);
    writeSummaryFile(filename, "9 1 1 3 4 6 3 0");

/* A mix of space and tab leading, space and tab in middle and malformed EOL.
testdata/input/test4.txt
  Total Lines:  9
Line begining:
  Space only:   1
  Tab only:     1
  Neither:      3
  Both:         4
Line ending:
  Dos:          0
  Unix:         0
  Malformed:    9
*/
    std::vector<char> test4{ 
        '\t', ' ', ' ', 'S', 'u', 'b', ' ', '1', '\n', '\r', 
        ' ', '\t', ' ', ' ', 'L', 'F', 'C', 'R', '.', 'm', '\n', '\r', 
        ' ', '\t', '\n', '\r', 
        '\t', ' ', '\n', '\r', 
        '\t', 'H', '\t', 'i', '\n', '\r', 
        ' ', 'H', '\t', 'i', '\n', '\r', 
        'H', '\t', 'i', '\n', '\r', 
        'H', ' ', 'i', '\n', '\r', 
        '\n', '\r' 
    };
    filename = "/test4.txt";
    input.setFileName(inputDir + filename);
    input.write(test4);
    writeSummaryFile(filename, "9 1 1 3 4 0 0 9");

    return 0;
}




/**
 * Test environment set up.
 *
 * @param  root - root directory for test environment staging.
 * @param  input - directory for file to be used as input to tfc.
 * @param  output - directory for tfc to place generated files.
 * @param  expected - directory containing the expected files for comparison.
 * @return error value or 0 if no errors.
 */
int init(const std::string & root, const std::string & input, const std::string & output, const std::string & expected)
{
    std::cout << "\nCreating test environment.\n";

    inputDir = input;
    outputDir = output;
    expectedDir = expected;

    deleteDirectory(root);
    createDirectory(input);
    createDirectory(output);
    createDirectory(expected);

    summaryTests();

    return 0;
}
