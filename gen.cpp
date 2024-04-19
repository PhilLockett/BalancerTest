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
 * @section test leading space generation.
 *
 * tfc -s -i testdata/input/testX.txt -o testdata/output/testXs.txt
 */
int spaceTests(void)
{
// test1.txt : A mix of space and tab leading, space and tab in middle and CR LF EOL.
    std::vector<char> test1{ 
        ' ', ' ', ' ', ' ', ' ', ' ', 'S', 'u', 'b', ' ', '1', '\r', '\n', 
        ' ', ' ', ' ', ' ', ' ', ' ', 'C', 'R', 'L', 'F', '.', 'm', '\r', '\n', 
        ' ', ' ', ' ', ' ', '\r', '\n', 
        ' ', ' ', ' ', ' ', ' ', '\r', '\n', 
        ' ', ' ', ' ', ' ', 'H', '\t', 'i', '\r', '\n', 
        ' ', 'H', '\t', 'i', '\r', '\n', 
        'H', '\t', 'i', '\r', '\n', 
        'H', ' ', 'i', '\r', '\n', 
        '\r', '\n' 
    };
    BinaryFile<> input{expectedDir + "/test1s.txt"};
    input.write(test1);

// test2.txt : A mix of space and tab leading, space and tab in middle and only LF EOL.
    std::vector<char> test2{ 
        ' ', ' ', ' ', ' ', ' ', ' ', 'S', 'u', 'b', ' ', '1', '\n', 
        ' ', ' ', ' ', ' ', ' ', ' ', 'L', 'F', '.', 'm', '\n', 
        ' ', ' ', ' ', ' ', '\n', 
        ' ', ' ', ' ', ' ', ' ', '\n', 
        ' ', ' ', ' ', ' ', 'H', '\t', 'i', '\n', 
        ' ', 'H', '\t', 'i', '\n', 
        'H', '\t', 'i', '\n', 
        'H', ' ', 'i', '\n', 
        '\n' 
    };
    input.setFileName(expectedDir + "/test2s.txt");
    input.write(test2);

// test3.txt : A mix of space and tab leading, space and tab in middle and mix of CR LF and LF EOL.
    std::vector<char> test3{ 
        ' ', ' ', ' ', ' ', ' ', ' ', 'M', 'i', 'x', ' ', '1', '\r', '\n', 
        ' ', ' ', ' ', ' ', ' ', ' ', 'C', 'R', 'L', 'F', '.', 'm', '\n', 
        ' ', ' ', ' ', ' ', '\r', '\n', 
        ' ', ' ', ' ', ' ', ' ', '\n', 
        ' ', ' ', ' ', ' ', 'H', '\t', 'i', '\r', '\n', 
        ' ', 'H', '\t', 'i', '\r', '\n', 
        'H', '\t', 'i', '\n', 
        'H', ' ', 'i', '\r', '\n', 
        '\r', '\n' 
    };
    input.setFileName(expectedDir + "/test3s.txt");
    input.write(test3);

// test4.txt : A mix of space and tab leading, space and tab in middle and malformed EOL.
    std::vector<char> test4{ 
        ' ', ' ', ' ', ' ', ' ', ' ', 'S', 'u', 'b', ' ', '1', '\n', '\r', 
        ' ', ' ', ' ', ' ', ' ', ' ', 'L', 'F', 'C', 'R', '.', 'm', '\n', '\r', 
        ' ', ' ', ' ', ' ', '\n', '\r', 
        ' ', ' ', ' ', ' ', ' ', '\n', '\r', 
        ' ', ' ', ' ', ' ', 'H', '\t', 'i', '\n', '\r', 
        ' ', 'H', '\t', 'i', '\n', '\r', 
        'H', '\t', 'i', '\n', '\r', 
        'H', ' ', 'i', '\n', '\r', 
        '\n', '\r' 
    };
    input.setFileName(expectedDir + "/test4s.txt");
    input.write(test4);

    return 0;
}


/**
 * @section test leading tab generation.
 *
 * tfc -t -i testdata/input/testX.txt -o testdata/output/testXt.txt
 */
int tabTests(void)
{
// test1.txt : A mix of space and tab leading, space and tab in middle and CR LF EOL.
    std::vector<char> test1{ 
        '\t', ' ', ' ', 'S', 'u', 'b', ' ', '1', '\r', '\n', 
        '\t', ' ', ' ', 'C', 'R', 'L', 'F', '.', 'm', '\r', '\n', 
        '\t', '\r', '\n', 
        '\t', ' ', '\r', '\n', 
        '\t', 'H', '\t', 'i', '\r', '\n', 
        ' ', 'H', '\t', 'i', '\r', '\n', 
        'H', '\t', 'i', '\r', '\n', 
        'H', ' ', 'i', '\r', '\n', 
        '\r', '\n' 
    };
    BinaryFile<> input{expectedDir + "/test1t.txt"};
    input.write(test1);

// test2.txt : A mix of space and tab leading, space and tab in middle and only LF EOL.
    std::vector<char> test2{ 
        '\t', ' ', ' ', 'S', 'u', 'b', ' ', '1', '\n', 
        '\t', ' ', ' ', 'L', 'F', '.', 'm', '\n', 
        '\t', '\n', 
        '\t', ' ', '\n', 
        '\t', 'H', '\t', 'i', '\n', 
        ' ', 'H', '\t', 'i', '\n', 
        'H', '\t', 'i', '\n', 
        'H', ' ', 'i', '\n', 
        '\n' 
    };
    input.setFileName(expectedDir + "/test2t.txt");
    input.write(test2);

// test3.txt : A mix of space and tab leading, space and tab in middle and mix of CR LF and LF EOL.
    std::vector<char> test3{ 
        '\t', ' ', ' ', 'M', 'i', 'x', ' ', '1', '\r', '\n', 
        '\t', ' ', ' ', 'C', 'R', 'L', 'F', '.', 'm', '\n', 
        '\t', '\r', '\n', 
        '\t', ' ', '\n', 
        '\t', 'H', '\t', 'i', '\r', '\n', 
        ' ', 'H', '\t', 'i', '\r', '\n', 
        'H', '\t', 'i', '\n', 
        'H', ' ', 'i', '\r', '\n', 
        '\r', '\n' 
    };
    input.setFileName(expectedDir + "/test3t.txt");
    input.write(test3);

// test4.txt : A mix of space and tab leading, space and tab in middle and malformed EOL.
    std::vector<char> test4{ 
        '\t', ' ', ' ', 'S', 'u', 'b', ' ', '1', '\n', '\r', 
        '\t', ' ', ' ', 'L', 'F', 'C', 'R', '.', 'm', '\n', '\r', 
        '\t', '\n', '\r', 
        '\t', ' ', '\n', '\r', 
        '\t', 'H', '\t', 'i', '\n', '\r', 
        ' ', 'H', '\t', 'i', '\n', '\r', 
        'H', '\t', 'i', '\n', '\r', 
        'H', ' ', 'i', '\n', '\r', 
        '\n', '\r' 
    };
    input.setFileName(expectedDir + "/test4t.txt");
    input.write(test4);

    return 0;
}


/**
 * @section test trailing dos generation.
 *
 * tfc -d -i testdata/input/testX.txt -o testdata/output/testXd.txt
 */
int dosTests(void)
{
// test1.txt : A mix of space and tab leading, space and tab in middle and CR LF EOL.
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
    BinaryFile<> input{expectedDir + "/test1d.txt"};
    input.write(test1);

// test2.txt : A mix of space and tab leading, space and tab in middle and only LF EOL.
    std::vector<char> test2{ 
        '\t', ' ', ' ', 'S', 'u', 'b', ' ', '1', '\r', '\n', 
        ' ', '\t', ' ', ' ', 'L', 'F', '.', 'm', '\r', '\n', 
        ' ', '\t', '\r', '\n', 
        '\t', ' ', '\r', '\n', 
        '\t', 'H', '\t', 'i', '\r', '\n', 
        ' ', 'H', '\t', 'i', '\r', '\n', 
        'H', '\t', 'i', '\r', '\n', 
        'H', ' ', 'i', '\r', '\n', 
        '\r', '\n' 
    };
    input.setFileName(expectedDir + "/test2d.txt");
    input.write(test2);

// test3.txt : A mix of space and tab leading, space and tab in middle and mix of CR LF and LF EOL.
    std::vector<char> test3{ 
        '\t', ' ', ' ', 'M', 'i', 'x', ' ', '1', '\r', '\n', 
        ' ', '\t', ' ', ' ', 'C', 'R', 'L', 'F', '.', 'm', '\r', '\n', 
        ' ', '\t', '\r', '\n', 
        '\t', ' ', '\r', '\n', 
        '\t', 'H', '\t', 'i', '\r', '\n', 
        ' ', 'H', '\t', 'i', '\r', '\n', 
        'H', '\t', 'i', '\r', '\n', 
        'H', ' ', 'i', '\r', '\n', 
        '\r', '\n' 
    };
    input.setFileName(expectedDir + "/test3d.txt");
    input.write(test3);

// test4.txt : A mix of space and tab leading, space and tab in middle and malformed EOL.
    std::vector<char> test4{ 
        '\t', ' ', ' ', 'S', 'u', 'b', ' ', '1', '\r', '\n', 
        ' ', '\t', ' ', ' ', 'L', 'F', 'C', 'R', '.', 'm', '\r', '\n', 
        ' ', '\t', '\r', '\n', 
        '\t', ' ', '\r', '\n', 
        '\t', 'H', '\t', 'i', '\r', '\n', 
        ' ', 'H', '\t', 'i', '\r', '\n', 
        'H', '\t', 'i', '\r', '\n', 
        'H', ' ', 'i', '\r', '\n', 
        '\r', '\n' 
    };
    input.setFileName(expectedDir + "/test4d.txt");
    input.write(test4);
 
    return 0;
}


/**
 * @section test trailing unix generation.
 *
 * tfc -u -i testdata/input/testX.txt -o testdata/output/testXu.txt
 */
int unixTests(void)
{
// test1.txt : A mix of space and tab leading, space and tab in middle and CR LF EOL.
    std::vector<char> test1{ 
        '\t', ' ', ' ', 'S', 'u', 'b', ' ', '1', '\n', 
        ' ', '\t', ' ', ' ', 'C', 'R', 'L', 'F', '.', 'm', '\n', 
        ' ', '\t', '\n', 
        '\t', ' ', '\n', 
        '\t', 'H', '\t', 'i', '\n', 
        ' ', 'H', '\t', 'i', '\n', 
        'H', '\t', 'i', '\n', 
        'H', ' ', 'i', '\n', 
        '\n' 
    };
    BinaryFile<> input{expectedDir + "/test1u.txt"};
    input.write(test1);

// test2.txt : A mix of space and tab leading, space and tab in middle and only LF EOL.
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
    input.setFileName(expectedDir + "/test2u.txt");
    input.write(test2);

// test3.txt : A mix of space and tab leading, space and tab in middle and mix of CR LF and LF EOL.
    std::vector<char> test3{ 
        '\t', ' ', ' ', 'M', 'i', 'x', ' ', '1', '\n', 
        ' ', '\t', ' ', ' ', 'C', 'R', 'L', 'F', '.', 'm', '\n', 
        ' ', '\t', '\n', 
        '\t', ' ', '\n', 
        '\t', 'H', '\t', 'i', '\n', 
        ' ', 'H', '\t', 'i', '\n', 
        'H', '\t', 'i', '\n', 
        'H', ' ', 'i', '\n', 
        '\n' 
    };
    input.setFileName(expectedDir + "/test3u.txt");
    input.write(test3);

// test4.txt : A mix of space and tab leading, space and tab in middle and malformed EOL.
    std::vector<char> test4{ 
        '\t', ' ', ' ', 'S', 'u', 'b', ' ', '1', '\n', 
        ' ', '\t', ' ', ' ', 'L', 'F', 'C', 'R', '.', 'm', '\n', 
        ' ', '\t', '\n', 
        '\t', ' ', '\n', 
        '\t', 'H', '\t', 'i', '\n', 
        ' ', 'H', '\t', 'i', '\n', 
        'H', '\t', 'i', '\n', 
        'H', ' ', 'i', '\n', 
        '\n' 
    };
    input.setFileName(expectedDir + "/test4u.txt");
    input.write(test4);

    return 0;
}


/**
 * @section test leading space and trailing dos generation.
 *
 * tfc -s -d -i testdata/input/testX.txt -o testdata/output/testXsd.txt
 */
int spaceDosTests(void)
{
// test1.txt : A mix of space and tab leading, space and tab in middle and CR LF EOL.
    std::vector<char> test1{ 
        ' ', ' ', ' ', ' ', ' ', ' ', 'S', 'u', 'b', ' ', '1', '\r', '\n', 
        ' ', ' ', ' ', ' ', ' ', ' ', 'C', 'R', 'L', 'F', '.', 'm', '\r', '\n', 
        ' ', ' ', ' ', ' ', '\r', '\n', 
        ' ', ' ', ' ', ' ', ' ', '\r', '\n', 
        ' ', ' ', ' ', ' ', 'H', '\t', 'i', '\r', '\n', 
        ' ', 'H', '\t', 'i', '\r', '\n', 
        'H', '\t', 'i', '\r', '\n', 
        'H', ' ', 'i', '\r', '\n', 
        '\r', '\n' 
    };
    BinaryFile<> input{expectedDir + "/test1sd.txt"};
    input.write(test1);

// test2.txt : A mix of space and tab leading, space and tab in middle and only LF EOL.
    std::vector<char> test2{ 
        ' ', ' ', ' ', ' ', ' ', ' ', 'S', 'u', 'b', ' ', '1', '\r', '\n', 
        ' ', ' ', ' ', ' ', ' ', ' ', 'L', 'F', '.', 'm', '\r', '\n', 
        ' ', ' ', ' ', ' ', '\r', '\n', 
        ' ', ' ', ' ', ' ', ' ', '\r', '\n', 
        ' ', ' ', ' ', ' ', 'H', '\t', 'i', '\r', '\n', 
        ' ', 'H', '\t', 'i', '\r', '\n', 
        'H', '\t', 'i', '\r', '\n', 
        'H', ' ', 'i', '\r', '\n', 
        '\r', '\n' 
    };
    input.setFileName(expectedDir + "/test2sd.txt");
    input.write(test2);

// test3.txt : A mix of space and tab leading, space and tab in middle and mix of CR LF and LF EOL.
    std::vector<char> test3{ 
        ' ', ' ', ' ', ' ', ' ', ' ', 'M', 'i', 'x', ' ', '1', '\r', '\n', 
        ' ', ' ', ' ', ' ', ' ', ' ', 'C', 'R', 'L', 'F', '.', 'm', '\r', '\n', 
        ' ', ' ', ' ', ' ', '\r', '\n', 
        ' ', ' ', ' ', ' ', ' ', '\r', '\n', 
        ' ', ' ', ' ', ' ', 'H', '\t', 'i', '\r', '\n', 
        ' ', 'H', '\t', 'i', '\r', '\n', 
        'H', '\t', 'i', '\r', '\n', 
        'H', ' ', 'i', '\r', '\n', 
        '\r', '\n' 
    };
    input.setFileName(expectedDir + "/test3sd.txt");
    input.write(test3);

// test4.txt : A mix of space and tab leading, space and tab in middle and malformed EOL.
    std::vector<char> test4{ 
        ' ', ' ', ' ', ' ', ' ', ' ', 'S', 'u', 'b', ' ', '1', '\r', '\n', 
        ' ', ' ', ' ', ' ', ' ', ' ', 'L', 'F', 'C', 'R', '.', 'm', '\r', '\n', 
        ' ', ' ', ' ', ' ', '\r', '\n', 
        ' ', ' ', ' ', ' ', ' ', '\r', '\n', 
        ' ', ' ', ' ', ' ', 'H', '\t', 'i', '\r', '\n', 
        ' ', 'H', '\t', 'i', '\r', '\n', 
        'H', '\t', 'i', '\r', '\n', 
        'H', ' ', 'i', '\r', '\n', 
        '\r', '\n' 
    };
    input.setFileName(expectedDir + "/test4sd.txt");
    input.write(test4);

    return 0;
}


/**
 * @section test leading tab and trailing dos generation.
 *
 * tfc -t -d -i testdata/input/testX.txt -o testdata/output/testXtd.txt
 */
int tabDosTests(void)
{
// test1.txt : A mix of space and tab leading, space and tab in middle and CR LF EOL.
    std::vector<char> test1{ 
        '\t', ' ', ' ', 'S', 'u', 'b', ' ', '1', '\r', '\n', 
        '\t', ' ', ' ', 'C', 'R', 'L', 'F', '.', 'm', '\r', '\n', 
        '\t', '\r', '\n', 
        '\t', ' ', '\r', '\n', 
        '\t', 'H', '\t', 'i', '\r', '\n', 
        ' ', 'H', '\t', 'i', '\r', '\n', 
        'H', '\t', 'i', '\r', '\n', 
        'H', ' ', 'i', '\r', '\n', 
        '\r', '\n' 
    };
    BinaryFile<> input{expectedDir + "/test1td.txt"};
    input.write(test1);

// test2.txt : A mix of space and tab leading, space and tab in middle and only LF EOL.
    std::vector<char> test2{ 
        '\t', ' ', ' ', 'S', 'u', 'b', ' ', '1', '\r', '\n', 
        '\t', ' ', ' ', 'L', 'F', '.', 'm', '\r', '\n', 
        '\t', '\r', '\n', 
        '\t', ' ', '\r', '\n', 
        '\t', 'H', '\t', 'i', '\r', '\n', 
        ' ', 'H', '\t', 'i', '\r', '\n', 
        'H', '\t', 'i', '\r', '\n', 
        'H', ' ', 'i', '\r', '\n', 
        '\r', '\n' 
    };
    input.setFileName(expectedDir + "/test2td.txt");
    input.write(test2);

// test3.txt : A mix of space and tab leading, space and tab in middle and mix of CR LF and LF EOL.
    std::vector<char> test3{ 
        '\t', ' ', ' ', 'M', 'i', 'x', ' ', '1', '\r', '\n', 
        '\t', ' ', ' ', 'C', 'R', 'L', 'F', '.', 'm', '\r', '\n', 
        '\t', '\r', '\n', 
        '\t', ' ', '\r', '\n', 
        '\t', 'H', '\t', 'i', '\r', '\n', 
        ' ', 'H', '\t', 'i', '\r', '\n', 
        'H', '\t', 'i', '\r', '\n', 
        'H', ' ', 'i', '\r', '\n', 
        '\r', '\n' 
    };
    input.setFileName(expectedDir + "/test3td.txt");
    input.write(test3);

// test4.txt : A mix of space and tab leading, space and tab in middle and malformed EOL.
    std::vector<char> test4{ 
        '\t', ' ', ' ', 'S', 'u', 'b', ' ', '1', '\r', '\n', 
        '\t', ' ', ' ', 'L', 'F', 'C', 'R', '.', 'm', '\r', '\n', 
        '\t', '\r', '\n', 
        '\t', ' ', '\r', '\n', 
        '\t', 'H', '\t', 'i', '\r', '\n', 
        ' ', 'H', '\t', 'i', '\r', '\n', 
        'H', '\t', 'i', '\r', '\n', 
        'H', ' ', 'i', '\r', '\n', 
        '\r', '\n' 
    };
    input.setFileName(expectedDir + "/test4td.txt");
    input.write(test4);

    return 0;
}


/**
 * @section test leading space and trailing unix generation.
 *
 * tfc -s -u -i testdata/input/testX.txt -o testdata/output/testXsu.txt
 */
int spaceUnixTests(void)
{
// test1.txt : A mix of space and tab leading, space and tab in middle and CR LF EOL.
    std::vector<char> test1{ 
        ' ', ' ', ' ', ' ', ' ', ' ', 'S', 'u', 'b', ' ', '1', '\n', 
        ' ', ' ', ' ', ' ', ' ', ' ', 'C', 'R', 'L', 'F', '.', 'm', '\n', 
        ' ', ' ', ' ', ' ', '\n', 
        ' ', ' ', ' ', ' ', ' ', '\n', 
        ' ', ' ', ' ', ' ', 'H', '\t', 'i', '\n', 
        ' ', 'H', '\t', 'i', '\n', 
        'H', '\t', 'i', '\n', 
        'H', ' ', 'i', '\n', 
        '\n' 
    };
    BinaryFile<> input{expectedDir + "/test1su.txt"};
    input.write(test1);

// test2.txt : A mix of space and tab leading, space and tab in middle and only LF EOL.
    std::vector<char> test2{ 
        ' ', ' ', ' ', ' ', ' ', ' ', 'S', 'u', 'b', ' ', '1', '\n', 
        ' ', ' ', ' ', ' ', ' ', ' ', 'L', 'F', '.', 'm', '\n', 
        ' ', ' ', ' ', ' ', '\n', 
        ' ', ' ', ' ', ' ', ' ', '\n', 
        ' ', ' ', ' ', ' ', 'H', '\t', 'i', '\n', 
        ' ', 'H', '\t', 'i', '\n', 
        'H', '\t', 'i', '\n', 
        'H', ' ', 'i', '\n', 
        '\n' 
    };
    input.setFileName(expectedDir + "/test2su.txt");
    input.write(test2);

// test3.txt : A mix of space and tab leading, space and tab in middle and mix of CR LF and LF EOL.
    std::vector<char> test3{ 
        ' ', ' ', ' ', ' ', ' ', ' ', 'M', 'i', 'x', ' ', '1', '\n', 
        ' ', ' ', ' ', ' ', ' ', ' ', 'C', 'R', 'L', 'F', '.', 'm', '\n', 
        ' ', ' ', ' ', ' ', '\n', 
        ' ', ' ', ' ', ' ', ' ', '\n', 
        ' ', ' ', ' ', ' ', 'H', '\t', 'i', '\n', 
        ' ', 'H', '\t', 'i', '\n', 
        'H', '\t', 'i', '\n', 
        'H', ' ', 'i', '\n', 
        '\n' 
    };
    input.setFileName(expectedDir + "/test3su.txt");
    input.write(test3);

// test4.txt : A mix of space and tab leading, space and tab in middle and malformed EOL.
    std::vector<char> test4{ 
        ' ', ' ', ' ', ' ', ' ', ' ', 'S', 'u', 'b', ' ', '1', '\n', 
        ' ', ' ', ' ', ' ', ' ', ' ', 'L', 'F', 'C', 'R', '.', 'm', '\n', 
        ' ', ' ', ' ', ' ', '\n', 
        ' ', ' ', ' ', ' ', ' ', '\n', 
        ' ', ' ', ' ', ' ', 'H', '\t', 'i', '\n', 
        ' ', 'H', '\t', 'i', '\n', 
        'H', '\t', 'i', '\n', 
        'H', ' ', 'i', '\n', 
        '\n' 
    };
    input.setFileName(expectedDir + "/test4su.txt");
    input.write(test4);

    return 0;
}


/**
 * @section test leading tab and trailing unix generation.
 *
 * tfc -t -u -i testdata/input/testX.txt -o testdata/output/testXtu.txt
 */
int tabUnixTests(void)
{
// test1.txt : A mix of space and tab leading, space and tab in middle and CR LF EOL.
    std::vector<char> test1{ 
        '\t', ' ', ' ', 'S', 'u', 'b', ' ', '1', '\n', 
        '\t', ' ', ' ', 'C', 'R', 'L', 'F', '.', 'm', '\n', 
        '\t', '\n', 
        '\t', ' ', '\n', 
        '\t', 'H', '\t', 'i', '\n', 
        ' ', 'H', '\t', 'i', '\n', 
        'H', '\t', 'i', '\n', 
        'H', ' ', 'i', '\n', 
        '\n' 
    };
    BinaryFile<> input{expectedDir + "/test1tu.txt"};
    input.write(test1);

// test2.txt : A mix of space and tab leading, space and tab in middle and only LF EOL.
    std::vector<char> test2{ 
        '\t', ' ', ' ', 'S', 'u', 'b', ' ', '1', '\n', 
        '\t', ' ', ' ', 'L', 'F', '.', 'm', '\n', 
        '\t', '\n', 
        '\t', ' ', '\n', 
        '\t', 'H', '\t', 'i', '\n', 
        ' ', 'H', '\t', 'i', '\n', 
        'H', '\t', 'i', '\n', 
        'H', ' ', 'i', '\n', 
        '\n' 
    };
    input.setFileName(expectedDir + "/test2tu.txt");
    input.write(test2);

// test3.txt : A mix of space and tab leading, space and tab in middle and mix of CR LF and LF EOL.
    std::vector<char> test3{ 
        '\t', ' ', ' ', 'M', 'i', 'x', ' ', '1', '\n', 
        '\t', ' ', ' ', 'C', 'R', 'L', 'F', '.', 'm', '\n', 
        '\t', '\n', 
        '\t', ' ', '\n', 
        '\t', 'H', '\t', 'i', '\n', 
        ' ', 'H', '\t', 'i', '\n', 
        'H', '\t', 'i', '\n', 
        'H', ' ', 'i', '\n', 
        '\n' 
    };
    input.setFileName(expectedDir + "/test3tu.txt");
    input.write(test3);

// test4.txt : A mix of space and tab leading, space and tab in middle and malformed EOL.
    std::vector<char> test4{ 
        '\t', ' ', ' ', 'S', 'u', 'b', ' ', '1', '\n', 
        '\t', ' ', ' ', 'L', 'F', 'C', 'R', '.', 'm', '\n', 
        '\t', '\n', 
        '\t', ' ', '\n', 
        '\t', 'H', '\t', 'i', '\n', 
        ' ', 'H', '\t', 'i', '\n', 
        'H', '\t', 'i', '\n', 
        'H', ' ', 'i', '\n', 
        '\n' 
    };
    input.setFileName(expectedDir + "/test4tu.txt");
    input.write(test4);

    return 0;
}



/**
 * @section test leading space to tab replacement.
 * 
 * tfc -t -Y -i testdata/input/testSpace.txt -o testdata/output/testSpaceY.txt
 */

int spaceToTabTests(void)
{
    std::string filename{"/testSpace"};


    std::vector<std::string> testSpace{ 
        "0", 
        " 1", 
        "  2", 
        "   3", 
        "    4", 
        "     5", 
        "      6", 
        "       7", 
        "        8", 
        "         9"
    };
    TextFile<> input{inputDir + filename + ".txt"};
    input.write(testSpace);

    std::vector<std::string> testSpace2{ 
        "0", 
        " 1", 
        "\t2", 
        "\t 3", 
        "\t\t4", 
        "\t\t 5", 
        "\t\t\t6", 
        "\t\t\t 7", 
        "\t\t\t\t8", 
        "\t\t\t\t 9"
    };
    TextFile<> expected{expectedDir + filename + "2.txt"};
    expected.write(testSpace2);

    std::vector<std::string> testSpace4{ 
        "0", 
        " 1", 
        "  2", 
        "   3", 
        "\t4", 
        "\t 5", 
        "\t  6", 
        "\t   7", 
        "\t\t8", 
        "\t\t 9"
    };
    expected.setFileName(expectedDir + filename + "4.txt");
    expected.write(testSpace4);

    std::vector<std::string> testSpace8{ 
        "0", 
        " 1", 
        "  2", 
        "   3", 
        "    4", 
        "     5", 
        "      6", 
        "       7", 
        "\t8", 
        "\t 9"
    };
    expected.setFileName(expectedDir + filename + "8.txt");
    expected.write(testSpace8);

    return 0;
}

/**
 * @section test leading tab to space replacement.
 * 
 * tfc -s -Y -i testdata/input/testSpace.txt -o testdata/output/testSpaceY.txt
 */

int tabToSpaceTests(void)
{
    std::string filename{"/testTab"};


    std::vector<std::string> testTab{ 
        "\t0", 
        " \t1", 
        "  \t2", 
        "   \t3", 
        "    \t4", 
        "     \t5", 
        "      \t6", 
        "       \t7", 
        "        \t8", 
        "         \t9"
    };
    TextFile<> input{inputDir + filename + ".txt"};
    input.write(testTab);

    std::vector<std::string> testTab2{ 
        "  0", 
        "  1", 
        "    2", 
        "    3", 
        "      4", 
        "      5", 
        "        6", 
        "        7", 
        "          8", 
        "          9"
    };
    TextFile<> expected{expectedDir + filename + "2.txt"};
    expected.write(testTab2);

    std::vector<std::string> testTab4{ 
        "    0", 
        "    1", 
        "    2", 
        "    3", 
        "        4", 
        "        5", 
        "        6", 
        "        7", 
        "            8", 
        "            9"
    };
    expected.setFileName(expectedDir + filename + "4.txt");
    expected.write(testTab4);

    std::vector<std::string> testTab8{ 
        "        0", 
        "        1", 
        "        2", 
        "        3", 
        "        4", 
        "        5", 
        "        6", 
        "        7", 
        "                8", 
        "                9"
    };
    expected.setFileName(expectedDir + filename + "8.txt");
    expected.write(testTab8);

    return 0;
}


/**
 * @section test source file replacement.
 * 
 * tfc -r testdata/input/testOptions.txt
 */

int optionsTests(void)
{
    std::vector<std::string> testOptions{ 
        "Line 0", 
        "Line 1", 
        "Line 2", 
        "Line 3", 
        "Line 4"
    };
    TextFile<> input{inputDir + "/testOptions.txt"};
    input.write(testOptions);

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

    spaceTests();
    tabTests();
    dosTests();
    unixTests();
    spaceDosTests();
    tabDosTests();
    spaceUnixTests();
    tabUnixTests();
    spaceToTabTests();
    tabToSpaceTests();
    optionsTests();

    return 0;
}
