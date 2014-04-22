/*

@file tools.cpp
@brief Storage for various string matching algorithms

@author Drew Guarnera, Heather Michaud

*/

#include <string>
#include <vector>

namespace narq
{
	//! @brief Finds a string in a text body matching a specific pattern using
	//!  a naive brute force algorithm
	//! @param needle The string pattern to search for in the text body
	//! @param haystack The body of text to search for the pattern in
	//! @retval The beginning index where the pattern is found in the text body
	//!  or -1 if not found.
	int bruteForce(std::string needle, std::string haystack);

	//! @brief Finds a string in a text body matching a specific pattern using
	//!  the Rabin-Karp algorithm - Las Vegas style. Thus, the time complexity
	//!  is gauranteed to be polynomial, but it's possible that it returns an
	//!  incorrect match.
	//! @param needle The string pattern to search for in the text body
	//! @param haystack The body of text to search for the pattern in
	//! @retval The beginning index where the pattern is found in the text body
	long rabinKarpLV(std::string needle, std::string haystack);

	//! @brief Finds a string in a text body matching a specific pattern using
	//!  the Rabin-Karp algorithm - Monte Carlo style. Thus, the time complexity
	//!  is likely polynomial, and the return is gauranteed to be a correct
	//!  match
	//! @param needle The string pattern to search for in the text body
	//! @param haystack The body of text to search for the pattern in
	//! @retval The beginning index where the pattern is found in the text body
	long rabinKarpMC(std::string needle, std::string haystack);

	//! @brief Finds all k needles in a haystack
	long rabinKarpSet(std::vector<std::string> needles, std::string haystack);

	//! @brief Calculates a rolling hash on a string based on each character in
	//!  the string, using prime base and modular numbers te prevent collisions
	//! @param s The string to seed the rolling hash
	//! @retval Hash of the string
	unsigned long long rhash(const std::string & s);

	void setBase(long long base);
	void setMod(long long mod);
	void multiString(std::vector<std::string>& input);
}
