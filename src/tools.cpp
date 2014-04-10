/*

@file tools.cpp
@brief Storage for various string matching algorithms

@author Drew Guarnera, Heather Michaud

*/

#include "tools.hpp"
#include <iostream>

namespace narq
{
	// --------------------------------------------------------------------- //
	int bruteForce(std::string textBody, std::string pattern)
	{
		int n = textBody.length();
		int m = pattern.length();
		bool match = false;

		// Traverse the text body looking for the pattern
		for (int i = 1; i <= n-m+1; ++i) {
			for (int j = 0; j < m; ++j) {
				match = true;
				if (textBody[i+j-1] != pattern[j]) {
					match = false; // Characters were not equal - no match
					break;         // Break from looping pattern characters
				}
			}
			if (match)             // If entire pattern matches,
				return i-1;        // return beginning index of location
		}
		return -1;                 // Else pattern does not exist in the text
	}

	// --------------------------------------------------------------------- //
	long rabinKarp(std::string pattern, std::string textBody)
	{
		long index = -1;
		return index;
	}

}
