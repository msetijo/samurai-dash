//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <vector>

#include <glm/vec3.hpp>

// Case insensitive strings (eg: Hello == HELLo) 
// This is used for parsing scene files
// Stolen from: Herb Suter - http://www.gotw.ca/gotw/029.htm

struct ci_char_traits : public std::char_traits<char>
              // just inherit all the other functions
              //  that we don't need to override
{
  static bool eq( char c1, char c2 )
    { return toupper(c1) == toupper(c2); }
   static bool ne( char c1, char c2 )
    { return toupper(c1) != toupper(c2); }
   static bool lt( char c1, char c2 )
    { return toupper(c1) <  toupper(c2); }

  static int compare( const char* s1,
                      const char* s2,
                      size_t n ) {

  return _memicmp( s1, s2, n );
      // if available on your compiler,
             //  otherwise you can roll your own
    }

    static const char*
    find( const char* s, int n, char a ) {
      while( n-- > 0 && toupper(*s) != toupper(a) ) {
          ++s;
      }
      return s;
    }
};

// Add to the list if you need to...
typedef std::basic_string<char, ci_char_traits> ci_string;
typedef std::basic_ifstream<char, ci_char_traits> ci_ifstream;
typedef std::basic_istringstream<char, ci_char_traits> ci_istringstream;
typedef std::basic_stringstream<char, ci_char_traits> ci_stringstream;
typedef std::basic_istream<char, ci_char_traits> ci_istream;

class PasingHelper {

public:
	static void parseVec3(const std::vector<ci_string> &token, glm::vec3& v) {

		assert(token.size() > 4);
		assert(token[1] == "=");

		v.x = static_cast<float>(atof(token[2].c_str()));
		v.y = static_cast<float>(atof(token[3].c_str()));
		v.z = static_cast<float>(atof(token[4].c_str()));
	}
};