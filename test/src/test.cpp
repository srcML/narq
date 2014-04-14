/*

@file test.cpp
@brief Unit test and timing tests for narq

@author Drew Guarnera, Heather Michaud

*/

#include "../../src/tools.hpp"
#include <fstream>
#include <iostream>
#include <ctime>

const std::string outputFile = "timing.csv";

//! @brief Generates a string with all values of a letter. This is used te test 
//! the worst case scenario
//! @param n The length of the string to be generated
//! @retval Generated sequence of letters of length n
std::string generateString(long long n, char letter)
{
	std::string sequence = "";
	for (int i = 0; i < n; ++i)
		sequence += letter;
	return sequence;
}

//! @brief Executes timing tests on naive and rabin karp algorithm
void timing()
{
	const int MIN_N = 10;     // Minimum needle string size
	const int MAX_N = 1000;   // Maximum needle string size
	const int MIN_H = 1000;   // Minimum haystack string size
	const int MAX_H = 10000;  // Maximum haystack string size
	const int INCREMENT = 10; // How much the needle & haystack are incremented

	// Open output file and write header column names
	std::ofstream output(outputFile);
	if (!output)
	{
		std::cerr << "Could not open results file " << outputFile << "\n";
		return;
	}
	output << "naive time (ms), "      << "index, "
	       << "rabin karp - LV (ms), " << "index, "
	       << "rabin karp - MC (ms), " << "index\n";

	// For varying levels of haystack size (string text body to search in)
	for (int i = MIN_H; i < MAX_H; i += INCREMENT)
	{
		std::string haystack = generateString(i, 'a');

		// For varying levels of needle size (string pattern to search for)
		for (int j = MIN_N; j < MAX_N; j += INCREMENT)
		{
			std::string needle = generateString(j, 'b');

			// Time Naive brute force algorithm
			std::clock_t start1 = std::clock();
			int index1 = narq::bruteForce(needle, haystack);
			std::clock_t end1 = std::clock();

			// Time Las Vegas Rabin Karp algorithm
			std::clock_t start2 = std::clock();
			int index2 = narq::rabinKarpLV(needle, haystack);
			std::clock_t end2 = std::clock();

			// Time Monte Carlo Rabin Karp algorithm
			std::clock_t start3 = std::clock();
			int index3 = narq::rabinKarpMC(needle, haystack);
			std::clock_t end3 = std::clock();

			// Calculate and output time differences and found index. All
			// indices should be -1 because the sequence was not found.
			double msTotal1 = 1000.0 * (end1 - start1) / CLOCKS_PER_SEC;
			double msTotal2 = 1000.0 * (end2 - start2) / CLOCKS_PER_SEC;
			double msTotal3 = 1000.0 * (end2 - start2) / CLOCKS_PER_SEC;
			output << msTotal1 << "," << index1 << ","
			       << msTotal2 << "," << index2 << ","
			       << msTotal3 << "," << index3 << "\n";
		}
	}
}


int main(int argc, char const *argv[])
{
	timing();
	return 0;
}
