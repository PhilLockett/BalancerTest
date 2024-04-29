/**
 * @file    Utilities.h
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
 * 'Balancer' is a command-line utility for balancing 'tracks' across multiple
 * sides.
 *
 * Basic utility code for the Balancer.
 */

#if !defined _UTILITIES_H_INCLUDED_
#define _UTILITIES_H_INCLUDED_

#include <string>
#include <vector>


///////////////////////////////////////////////////////////////////////////////
/**
 * @section basic utility code.
 */

extern const std::string whitespace;
extern const std::string digit;

#define WHITESPACE " \t"
const char iSep{'|'};   // Input field seperator.
const char oSep{'|'};   // Output field seperator.

extern size_t timeStringToSeconds(std::string buffer);
extern std::string secondsToTimeString(size_t seconds, const std::string & sep = ":");


///////////////////////////////////////////////////////////////////////////////

extern std::vector<std::string> split(const std::string & line, size_t items);


#endif //!defined _UTILITIES_H_INCLUDED_
