/*

@file test.cpp
@brief Unit test and timing tests for narq

@author Drew Guarnera, Heather Michaud

*/

#include "../../src/tools.hpp"
#include <fstream>
#include <iostream>
#include <ctime>

const long long MAX_SEQUENCE = 10000;
const std::string outputFile = "timing.csv";

//! @brief Generates a string with all values "a". This is used te test the
//!  worst case scenario
//! @param n The length of the string to be generated
//! @retval Generated sequence of 'a's of length n
std::string generateString(long long n)
{
	std::string sequence = "";
	for (int i = 0; i < n; ++i)
		sequence += "a";
	return sequence;
}

//! @brief Executes timing tests on naive and rabin karp algorithm
void timing()
{
	std::ofstream output(outputFile);
	if (!output)
	{
		std::cerr << "Could not open results file " << outputFile << "\n";
		return;
	}

	output << "naive time (ms), "
	       << "index, "
	       << "rabin karp (ms), "
	       << "index\n";

	for (int i = 1000; i < MAX_SEQUENCE; i += 10)
	{
		std::string haystack = generateString(i);

		//! @todo We should look into varying sizes of this as well, to show
		//!  haw this affects the time
		std::string needle = "b";

		// Time Naive brute force algorithm
		std::clock_t start1 = std::clock();
		int index1 = narq::bruteForce(needle, haystack);
		std::clock_t end1 = std::clock();

		// Time Las Vegas Rabin Karp algorithm
		std::clock_t start2 = std::clock();
		int index2 = narq::rabinKarp(needle, haystack);
		std::clock_t end2 = std::clock();

		double msTotal1 = 1000.0 * (end1 - start1) / CLOCKS_PER_SEC;
		double msTotal2 = 1000.0 * (end2 - start2) / CLOCKS_PER_SEC;

		output << msTotal1 << ","
		       << index1 << ","
		       << msTotal2 << ","
		       << index2 << "\n";
	}
}


int main(int argc, char const *argv[])
{
	timing();
	return 0;
}
