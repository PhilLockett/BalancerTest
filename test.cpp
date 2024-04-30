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
#include <algorithm>
#include <filesystem>

#include "TextFile.h"
#include "Side.h"

#include "unittest.h"

/**
 * @section Basic utility code.
 */

const std::string rootDir{"testdata"};
const std::string inputDir{rootDir + "/input/"};
const std::string outputDir{rootDir + "/output/"};
const std::string expectedDir{rootDir + "/expected/"};


static std::vector<std::string> commands{};


static bool createDirectory(const std::string & path)
{
    return std::filesystem::create_directories(path);
}

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
 * @section Test script generation, currently not used.
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
 * @section Support code.
 */

/**
 * @brief Constructs a Balancer command using supplied parameters and executes it.
 * 
 * @param options to be tested.
 * @param inputFileName without the input directory.
 * @param outputFileName without the output directory.
 * @return int the command return value.
 */
static int executeCommand(const std::string & options, const std::string & inputFileName, const std::string & outputFileName)
{
    std::string command{"Balancer " + options + " -i " + inputDir + inputFileName + " > " + outputDir + outputFileName};

    return execute(command);
}

/**
 * @brief compares 2 files (the expected file with the generated file).
 * 
 * @param fileName without the directory.
 * @return true if the 2 files are the same, false otherwise.
 */
static bool compareAlbums(const std::string & fileName)
{
    TextFile<> expected{expectedDir + fileName};
    expected.read();
    TextFile<> output{outputDir + fileName};
    output.read();

    return expected.equal(output);
}


/**
 * @brief Loads in a CSV ('|') output file and converts it to a Album.
 * 
 * @param inputFile to load, must use '|' as a delimiter.
 * @return Album representation of inputFile.
 */
Album loadTracks(const std::string & inputFile)
{
	Album album{};
	album.setTitle(inputFile);

    TextFile input{inputDir + inputFile};
	if (!input.exists())
	    return album;

    input.read();

	// Parse file.
	for (const auto & line : input)
	{
		// Split line into 3 tokens.
		std::vector<std::string> tokens{split(line, 3)};

		// Remove quotes from label.
		std::string label{tokens[2]};
		label.erase(std::find(label.begin(), label.end(), '"'));
		label.erase(std::find(label.begin(), label.end(), '"'));

		// Parse line type.
		if (tokens[0].compare("Side") == 0)
		{
			// Find track count.
		    size_t pos{label.find_first_of(",")};
			if (pos == std::string::npos)
				break;

			size_t digits{};
			auto tracks{std::stoi(label.substr(pos+1), &digits)};

			// Push the side to the album.
			Side side{};
			side.reserve(tracks);
			side.setTitle(label.substr(0, pos));
			album.push(side);
		}
		else
		{
			// Extract seconds.
		    size_t seconds{timeStringToSeconds(tokens[1])};

			// Push the track to the last side of the album.
		    Track track{label, seconds};
			album.pushLast(track);
		}
	}

	album.getHash();

    return album;
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

    REQUIRE(executeCommand("-b 1 -p", "TestTimeFormats.txt", "testtime1.txt") == 0)

    REQUIRE(compareAlbums("testtime1.txt"))

END_TEST

UNIT_TEST(testtime2, "Test input with a variety of time formats generating 'hh:mm:ss' output.")

    REQUIRE(executeCommand("-b 1", "TestTimeFormats.txt", "testtime2.txt") == 0)

    REQUIRE(compareAlbums("testtime2.txt"))

END_TEST

UNIT_TEST(testtime3, "Test input with a variety of time formats generating 'shuffled' output.")

    REQUIRE(executeCommand("-b 1 -s", "TestTimeFormats.txt", "testtime3.txt") == 0)

    REQUIRE(compareAlbums("testtime3.txt"))

END_TEST

UNIT_TEST(testtime4, "Test input with a variety of time formats generating 'CSV' output.")

    REQUIRE(executeCommand("-b 1 -c -a '|'", "TestTimeFormats.txt", "testtime4.txt") == 0)

    REQUIRE(compareAlbums("testtime4.txt"))

END_TEST


/**
 * @section test output generation for multiple boxes.
 *
 */

UNIT_TEST(testoutput11, "Test 'split' output for 4 boxes (plain CSV).")

    REQUIRE(executeCommand("-b 4 -c -a '|' -p", "BeaucoupFish.txt", "split.txt") == 0)

    REQUIRE(compareAlbums("split.txt"))

END_TEST

UNIT_TEST(testoutput12, "Test 'shuffle' output for 4 boxes (plain CSV).")

    REQUIRE(executeCommand("-b 4 -c -a '|' -p -s", "BeaucoupFish.txt", "shuffle.txt") == 0)

    REQUIRE(compareAlbums("shuffle.txt"))

END_TEST


/**
 * @section test output generation for duration.
 *
 */

UNIT_TEST(testoutput21, "Test 'split' output for 22 minute duration (even boxes plain CSV).")

    REQUIRE(executeCommand("-d 22:00 -e -c -a '|' -p", "QueenBest.txt", "split21.txt") == 0)

    REQUIRE(compareAlbums("split21.txt"))

END_TEST

UNIT_TEST(testoutput22, "Test 'split' output for 12 boxes (plain CSV - same result as above).")

    REQUIRE(executeCommand("-b 12 -c -a '|' -p", "QueenBest.txt", "split22.txt") == 0)

    REQUIRE(compareAlbums("split22.txt"))

END_TEST

UNIT_TEST(testoutput23, "Test 'shuffle' output for 22 minute duration (even boxes plain CSV).")

    REQUIRE(executeCommand("-d 22:00 -e -c -a '|' -p -s", "QueenBest.txt", "shuffle23.txt") == 0)

    REQUIRE(compareAlbums("shuffle23.txt"))

END_TEST


/**
 * @section test output generation for ideal case.
 *
 */

UNIT_TEST(testideal11, "Test ideal 'split' output for 4 boxes.")

    REQUIRE(executeCommand("-b 4 -x", "Ideal.txt", "ideal11.txt") == 0)

    REQUIRE(compareAlbums("ideal11.txt"))

END_TEST

UNIT_TEST(testideal12, "Test ideal 'split' output for 20 minute duration.")

    REQUIRE(executeCommand("-d 20:00 -x", "Ideal.txt", "ideal12.txt") == 0)

    REQUIRE(compareAlbums("ideal12.txt"))

END_TEST

UNIT_TEST(testideal21, "Test ideal 'shuffle' output for 4 boxes.")

    REQUIRE(executeCommand("-b 4 -x -s", "Ideal.txt", "ideal21.txt") == 0)

    REQUIRE(compareAlbums("ideal21.txt"))

END_TEST

UNIT_TEST(testideal22, "Test ideal 'shuffle' output for 20 minute duration.")

    REQUIRE(executeCommand("-d 20:00 -x -s", "Ideal.txt", "ideal22.txt") == 0)

    REQUIRE(compareAlbums("ideal22.txt"))

END_TEST


/**
 * @section test Album comparison code.
 *
 */

UNIT_TEST(testcompare12, "Compare identical files.")

	Album album1{loadTracks("ideal11.txt")};
	Album album2{loadTracks("ideal12.txt")};

    REQUIRE(album1.getHash() == album2.getHash())

END_TEST

UNIT_TEST(testcompare13, "Compare files with identical sides, but in a different order.")

	Album album1{loadTracks("ideal11.txt")};
	Album album2{loadTracks("ideal13.txt")};

    REQUIRE(album1.getHash() == album2.getHash())

END_TEST

UNIT_TEST(testcompare14, "Compare files with identical sides, but with tracks in a different order.")

	Album album1{loadTracks("ideal11.txt")};
	Album album2{loadTracks("ideal14.txt")};

    REQUIRE(album1.getHash() == album2.getHash())

END_TEST

UNIT_TEST(testcompare21, "Compare files with tracks arranged differently (but identical side lengths).")

	Album album1{loadTracks("ideal11.txt")};
	Album album2{loadTracks("ideal21.txt")};

    REQUIRE(album1.getHash() != album2.getHash())

END_TEST

UNIT_TEST(testcompare22, "Compare files with same arrangement of tracks but different track lengths.")

	Album album1{loadTracks("ideal11.txt")};
	Album album2{loadTracks("ideal22.txt")};

    REQUIRE(album1.getHash() != album2.getHash())

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

    RUN_TEST(testoutput11)
    RUN_TEST(testoutput12)
    RUN_TEST(testoutput21)
    RUN_TEST(testoutput22)
    RUN_TEST(testoutput23)

    RUN_TEST(testideal11)
    RUN_TEST(testideal12)
    RUN_TEST(testideal21)
    RUN_TEST(testideal22)

    RUN_TEST(testcompare12)
    RUN_TEST(testcompare13)
    RUN_TEST(testcompare14)
    RUN_TEST(testcompare21)
    RUN_TEST(testcompare22)


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
    createDirectory(outputDir);

    return runTests(argv[0]);
}

