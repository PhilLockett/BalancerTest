# tfcTest
Test code for 'tfc' (a command-line utility Text File Checker).

## Overview
A sequence of regression tests for the 'tfc' utility.

## Cloning and Running
The test code is dependent on UnitTest. To compile and run the tfcTest code you
first need to clone the unit test code, then copy unittest.cpp and unittest.h 
into the tfcTest directory before executing make.

    git clone https://github.com/PhilLockett/UnitTest.git

To clone, build and run this code, execute the following unix/linux commands:

    git clone https://github.com/PhilLockett/tfcTest.git
    cd tfcTest/
    cp ../UnitTest/unittest.cpp .
    cp ../UnitTest/unittest.h .
    make
    ./test

## Points of interest
This code has the following points of interest:

  * The unit test code completely regenerates the required test files.
  * The unit test code exercises all ‘tfc’ options and validates the results.
  * The unit test code lists all ‘tfc’ commands used.
