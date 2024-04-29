/**
 * @file    Side.cpp
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

#include <iostream>

#include "Side.h"
#include "Utilities.h"



/**
 * @section Define Track support.
 *
 */

bool Track::stream(std::ostream & os, bool plain, bool csv) const
{
    std::string time{plain ? std::to_string(seconds) : secondsToTimeString(seconds)};

    os << "    ";
    const std::string c{oSep};
    if (csv)
        os << "Track" << c << time << c << "\"" << title << "\"";
    else
        os << time << " - " << title;
    os << "\n";

    return true;
}


/**
 * @section Define Side class.
 *
 */

void Side::push(const Track & track)
{
    tracks.push_back(track);
    seconds += track.getValue();
}

void Side::pop(void)
{
    seconds -= tracks.back().getValue();
    tracks.pop_back();
}


size_t Side::getHash(void)
{
    if (!hash)
    {
        hash = size();

        std::multiset<size_t> values{};
        for (const auto & track : tracks)
            values.insert(track.getValue());


        // std::cout << "  ";
        for (const auto & value : values)
        {
            hash <<= 1;
            hash ^= std::hash<size_t>{}(value);
            // std::cout << value << " ";
        }
        // std::cout << "\n";
        // std::cout << "hash: " << hash << "\n";
    }

    return hash;
}

bool Side::stream(std::ostream & os, bool plain, bool csv) const
{
    std::string time{plain ? std::to_string(seconds) : secondsToTimeString(seconds)};

    os << "  ";
    const std::string c{oSep};
    if (csv)
        os << "Side" << c << time << c << "\"" << title << ", " << std::to_string(size()) << " tracks\"";
    else
        os << title << " - " << std::to_string(size()) << " tracks";
    os << "\n";

    for (const auto & track : tracks)
        track.stream(os, plain, csv);

    if (!csv)
        os << "  " << time << "\n\n";

    return true;
}

bool Side::summary(std::ostream & os, bool plain) const
{
    const std::string time{plain ? std::to_string(seconds) : secondsToTimeString(seconds)};
    os << getTitle() << " - " << size() << " tracks " << time << "\n";

    return true;
}


/**
 * @section Define Album class.
 *
 */

void Album::push(const Side & side)
{
    sides.push_back(side);
    seconds += side.getValue();
}

void Album::pop()
{
    seconds -= sides.back().getValue();
    sides.pop_back();
}

size_t Album::getHash(void)
{
    if (!hash)
    {
        hash = size();

        std::multiset<size_t> values{};
        for (auto & side : sides)
            values.insert(side.getHash());

        for (const auto & value : values)
        {
            hash <<= 1;
            hash ^= std::hash<size_t>{}(value);
            // std::cout << value << " ";
        }
        // std::cout << "\n";
        // std::cout << "hash: " << hash << "\n";
    }

    return hash;
}

bool Album::stream(std::ostream & os, bool plain, bool csv) const
{
    os << title << ":\n";

    for (const auto & side : sides)
        side.stream(std::cout, plain, csv);

    std::string time{plain ? std::to_string(seconds) : secondsToTimeString(seconds)};
    os << time << "\n";

    return true;
}

bool Album::summary(std::ostream & os, bool plain) const
{
    for (const auto & side : sides)
        side.summary(std::cout, plain);

    return true;
}
