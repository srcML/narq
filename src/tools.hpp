/*

@file tools.cpp
@brief Storage for various string matching algorithms

@author Drew Guarnera, Heather Michaud

*/

#include <string>

namespace narq
{
	//! @brief Finds a string in a text body matching a specific pattern using
	//!  a naive brute force algorithm
	//! @param pattern The string pattern to search for in the text body
	//! @param textBody The body of text to search for the pattern in
	//! @retval The beginning index where the pattern is found in the text body
	//!  or -1 if not found.
	int bruteForce(std::string pattern, std::string textBody);

	//! @brief Finds a string in a text body matching a specific pattern using
	//!  the Rabin-Karp algorithm
	//! @param pattern The string pattern to search for in the text body
	//! @param textBody The body of text to search for the pattern in
	//! @retval The beginning index where the pattern is found in the text body
	long rabinKarp(std::string pattern, std::string textBody);
}
