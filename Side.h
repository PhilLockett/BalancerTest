/**
 * @file    Side.h
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
 * Class definitions for the Balancer.
 */

#if !defined _SIDE_H_INCLUDED_
#define _SIDE_H_INCLUDED_

#include <string>
#include <vector>
#include <set>

#include "Utilities.h"


/**
 * @section Define Track class.
 *
 */

class Track
{
public:
    Track(const std::string & t, size_t s) : title{t}, seconds{s} { }

    std::string getTitle() const { return title; }
    size_t getValue() const { return seconds; }

    bool stream(std::ostream & os, bool plain=false, bool csv=false) const;

private:
    const std::string title;
    const size_t seconds;
};


/**
 * @section Define Side class.
 *
 */

class Side
{
public:
    using Iterator = std::vector<Track>::const_iterator;

    Side(void) : title{}, seconds{}, hash{} {}

    void setTitle(const std::string & t) { title = t; }
    void reserve(size_t len) { tracks.reserve(len); }

    void push(const Track & track);
    void pop(void);

    const std::string & getTitle() const { return title; }
    size_t getValue(void) const { return seconds; }
    size_t getHash(void);

    size_t size(void) const { return tracks.size(); }
    Iterator begin(void) const { return tracks.begin(); }
    Iterator end(void) const { return tracks.end(); }

    bool stream(std::ostream & os, bool plain=false, bool csv=false) const;
    bool summary(std::ostream & os, bool plain=false) const;

    void clear(void) { seconds = 0; tracks.clear(); }

private:
    std::string title;
    size_t seconds;
    size_t hash;
    std::vector<Track> tracks;

};


/**
 * @section Define Album class.
 *
 */

class Album
{
public:
    using Iterator = std::vector<Side>::const_iterator;

    Album(void) : title{}, seconds{}, hash{} {}

    void setTitle(const std::string & t) { title = t; }
    // void reserve(size_t len) { sides.reserve(len); }

    void push(const Side & side);
    void pop(void);

    const std::string & getTitle() const { return title; }
    size_t getValue(void) const { return seconds; }
    size_t getHash(void);

    size_t size(void) const { return sides.size(); }
    Iterator begin(void) const { return sides.begin(); }
    Iterator end(void) const { return sides.end(); }

    bool stream(std::ostream & os, bool plain=false, bool csv=false) const;
    bool summary(std::ostream & os, bool plain=false) const;

    void clear(void) { seconds = 0; for (auto item : sides) item.clear(); sides.clear(); }

    void pushLast(const Track & track) { seconds += track.getValue(); sides[size()-1].push(track); }
    // const Side & operator[](size_t index) const { return sides[index]; }

private:
    std::string title;
    size_t seconds;
    size_t hash;
    std::vector<Side> sides;

};

#endif //!defined _SIDE_H_INCLUDED_
