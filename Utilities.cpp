/**
 * @file    Utilities.cpp
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

#include "Utilities.h"
#include "TextFile.h"


///////////////////////////////////////////////////////////////////////////////
/**
 * @section basic utility code.
 */

const std::string whitespace{" \t"};
const std::string digit{"0123456789"};

/**
 * @brief Break a time string (H:M:S) down to get total number of seconds.
 * Also handles M:S and S formats.
 * 
 * @param buffer time string to parse.
 * @return size_t the equivalent number of seconds.
 */
size_t timeStringToSeconds(std::string buffer)
{
    size_t digits{};
    size_t seconds{};
    size_t pos{};

    for (int i = 0; i < 3; ++i)
    {
        buffer = buffer.substr(digits);
        pos = buffer.find_first_of(digit);
        if (pos == std::string::npos)
            break;

        seconds *= 60;
        buffer = buffer.substr(pos);
        seconds += std::stoi(buffer, &digits);
    }

    return seconds;
}


/**
 * @brief Generates a time string in the form H:M:S from the given seconds.
 * 
 * @param seconds number of seconds to represent.
 * @param sep optional seperator or ':' if none specified.
 * @return std::string time string in the form H:M:S.
 */
std::string secondsToTimeString(size_t seconds, const std::string & sep)
{
    std::ostringstream ss;

    size_t hours{seconds / 3600};
    seconds -= hours * 3600;

    size_t minutes{seconds / 60};
    seconds -= minutes * 60;

    ss.width(2);
    ss.fill('0');
    ss << hours << sep;
    ss.width(2);
    ss << minutes << sep;
    ss.width(2);
    ss << seconds;

    return ss.str();
}




///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Split a line (a maximum of items times), delimited by '|' into a 
 * vector of strings.
 * 
 * @param line to be split.
 * @param items maximum number of items.
 * @return std::vector<std::string> 
 */
std::vector<std::string> split(const std::string & line, size_t items)
{
    size_t start{};
    size_t end = line.find(iSep, start);
    std::vector<std::string> list{};
    list.reserve(items);
    while (end != std::string::npos && items > 1)
    {
        --items;
        list.emplace_back(line.substr(start, end-start));

        start = end + 1;
        end = line.find(iSep, start);
    }
    list.emplace_back(line.substr(start));

    return list;
}


