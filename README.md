# BalancerTest
Test code for [Balancer](https://github.com/PhilLockett/Balancer) (a
command-line utility for balancing 'tracks' across multiple 'sides').

**USE AT OWN RISK.**

## Overview
A sequence of regression tests for the [Balancer](https://github.com/PhilLockett/Balancer) utility.

## Cloning and Running
This test code is dependent on [UnitTest](https://github.com/PhilLockett/UnitTest).
To compile and run the `BalancerTest` code, first clone the unit test code:

    git clone https://github.com/PhilLockett/UnitTest.git

Then copy unittest.cpp and unittest.h into the `BalancerTest` directory before
executing 'make'.

Therefore, to clone, build and run `BalancerTest`, execute the following
unix/linux commands:

    git clone https://github.com/PhilLockett/BalancerTest.git
    cd BalancerTest/
    cp ../UnitTest/unittest.cpp .
    cp ../UnitTest/unittest.h .
    make
    ./test

## Points of interest
This code has the following points of interest:

  * The unit test code uses example input and expected output test files.
  * The unit test code exercises `Balancer` options and validates the results.
  * The unit test code lists all `Balancer` commands tested.
  * Also tests compare code that ignores order and instead looks at lengths.
