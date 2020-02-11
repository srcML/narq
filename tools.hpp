/*
@file tools.cpp
@brief Storage for various string matching algorithms
@author Drew Guarnera, Heather Michaud
*/

#include <string>
#include <vector>

namespace narq
{
	//! @brief Finds the number of matches for k needles in a haystack
	//! @param needles The list of equal length strings to search for in the text body
	//! @param haystack The body of text to searh for patterns in
	//! @param numNeedles The number of needles to search for
	//! @retval A vector containing the number of matches found for each needle, corresponding to 
	//! the original index of the needle in the needles array
	std::vector<int> rabinKarpMulti(std::vector<std::string>& needle, std::string haystack,
	                                int numNeedles);

	// Calculates a rolling hash on a string based on each character in the string, using 
	unsigned long long rhash(const std::string & s);

	//! @brief Partitions a given string into a specified number of pieces
	//! @param s The string to be partitioned
	//! @param numPartitions The number of partitions to slice s into
	//! @retval A vector of string partitions
	std::vector<std::string> partition(std::string &s, int numPartitions);
}
