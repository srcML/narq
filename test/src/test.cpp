/*

@file test.cpp
@brief Unit test and timing tests for narq

@author Drew Guarnera, Heather Michaud

*/

#include "../../src/tools.hpp"
#include <fstream>
#include <iostream>
#include <ctime>

const std::string outputFile_hup = "timing_increasing_haystack.csv";
const std::string outputFile_nup = "timing_increasing_needle.csv";
const std::string outputFile_bup = "timing_increasing_baseprime.csv";
const std::string outputFile_mup = "timing_increasing_modprime.csv";

const int MIN_N = 10;       // Minimum needle string size
const int MAX_N = 1000;     // Maximum needle string size
const int MIN_H = 100;      // Minimum haystack string size
const int MAX_H = 10000;   // Maximum haystack string size
const int INCREMENT = 100;  // How much the needle & haystack are incremented
const int MIN_BP = 1;       // Minimum base number for rolling hash
const int MAX_BP = 257;     // Maximum base number for rolling hash
const int MIN_MP = 11;      // Minimum mod number for rolling hash
const unsigned int MAX_MP = 1000000007; // Maximum mod number for rolling hash

//! @brief Executes all timing tests on naive and rabin karp algorithm
void timing();

//! @brief Executes timing tests on naive and rabin karp algorithm, varying the
//! size of the needle to search for
void varyNeedleSize();

//! @brief Executes timing tests on naive and rabin karp algorithm, varying the
//! size of the haystack to search in
void varyHaystackSize();

//! @brief Executes timing tests on naive and rabin karp algorithm, varying the
//! size of the base used for the rolling hash
void varyBaseSize();

//! @brief Executes timing tests on naive and rabin karp algorithm, varying the
//! size of the mod number used for the rolling hash
void varyModSize();

//! @brief Generates a string with all values of a letter. This is used te test 
//! the worst case scenario
//! @param n The length of the string to be generated
//! @retval Generated sequence of letters of length n
std::string generateString(long long n, char letter);

// ========================================================================= //
// ===================== Main Execution Point ============================== //
// ========================================================================= //

int main(int argc, char const *argv[])
{
	timing();
	return 0;
}

// ========================================================================= //
// ======================== Testing Utilities ============================== //
// ========================================================================= //

// ========================================================================= //
void timing()
{
	varyNeedleSize();
	varyHaystackSize();
	//varyModSize();
	//varyBaseSize();	
}

// ========================================================================= //
std::string generateString(long long n, char letter)
{
	std::string sequence = "";
	for (int i = 0; i < n; ++i)
		sequence += letter;
	return sequence;
}

// ========================================================================= //
void varyNeedleSize() {
	// Open output file and write header column names
	std::ofstream output(outputFile_hup.c_str());
	if (!output)
	{
		std::cerr << "Could not open results file " << outputFile_nup << "\n";
		return;
	}
	output << "needle size, "          << "haystack size, "
	       << "base number, "          << "mod number, "
	       << "naive time (ms), "      << "index, "
	       << "rabin karp - LV (ms), " << "index, "
	       << "rabin karp - MC (ms), " << "index\n";

	// Varying needle size in a large haystack
	std::cout << "\n";
	std::string haystack = generateString(MAX_H, 'a');
	for (int i = MIN_N; i <= MAX_N; i += INCREMENT)
	{
		int percentComplete = ((i / (double) MAX_N) * 100);
		std::cout << "Testing varying needle size: " << percentComplete << "% " << "\r";
		fflush(stdout);

		std::string needle = generateString(i-1, 'a');
		needle += "b";

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
		double msTotal3 = 1000.0 * (end3 - start3) / CLOCKS_PER_SEC;
		output << i        << "," << MAX_H  << ","
		       << MAX_BP   << "," << MAX_MP << ","
		       << msTotal1 << "," << index1 << ","
		       << msTotal2 << "," << index2 << ","
		       << msTotal3 << "," << index3 << "\n";
	}
	std::cout << "Testing varying needle size: " << 100 << "% " << "\r";
	std::cout << "\n";
	output.close();
}

// ========================================================================= //
void varyHaystackSize() {
	// Open output file and write header column names
	std::ofstream output(outputFile_nup.c_str());
	if (!output)
	{
		std::cerr << "Could not open results file " << outputFile_hup << "\n";
		return;
	}
	output << "needle size, "          << "haystack size, "
	       << "base number, "          << "mod number, "
	       << "naive time (ms), "      << "index, "
	       << "rabin karp - LV (ms), " << "index, "
	       << "rabin karp - MC (ms), " << "index\n";

	std::string needle = generateString(MIN_N - 1, 'a');
	needle += "b";

	// For varying levels of haystack size (string text body to search in)
	for (int i = MIN_H; i <= MAX_H; i += INCREMENT)
	{
		int percentComplete = (i / (double) MAX_H) * 100;
		std::cout << "Testing varying haystack size: " << percentComplete << "%" << "\r";
		fflush(stdout);

		std::string haystack = generateString(i, 'a');

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
		double msTotal3 = 1000.0 * (end3 - start3) / CLOCKS_PER_SEC;
		output << MIN_N    << "," << i      << ","
	           << MAX_BP   << "," << MAX_MP << ","
		       << msTotal1 << "," << index1 << ","
		       << msTotal2 << "," << index2 << ","
		       << msTotal3 << "," << index3 << "\n";
	}
	std::cout << "Testing varying haystack size: " << 100 << "%" << "\r";
	std::cout << "\n";
	output.close();
}

// ========================================================================= //
void varyBaseSize() {
	// Open output file and write header column names
	std::ofstream output(outputFile_bup.c_str());
	if (!output)
	{
		std::cerr << "Could not open results file " << outputFile_bup << "\n";
		return;
	}
	output << "needle size, "          << "haystack size, "
	       << "base number, "          << "mod number, "
	       << "naive time (ms), "      << "index, "
	       << "rabin karp - LV (ms), " << "index, "
	       << "rabin karp - MC (ms), " << "index\n";

	std::string haystack = generateString(MAX_H, 'a');
	std::string needle = generateString(MIN_N - 1, 'a');
	needle += "b";

	for (int i = MIN_BP; i <= MAX_BP; ++i)
	{
		int percentComplete = (i / (double) MAX_BP) * 100;
		std::cout << "Testing varying base size: " << percentComplete << "%" << "\r";
		fflush(stdout);

		// Set base number for rolling hash
		narq::setBase(i);

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
		double msTotal3 = 1000.0 * (end3 - start3) / CLOCKS_PER_SEC;
		output << MIN_N    << "," << MAX_H  << ","
		       << i        << "," << MAX_MP << ","
		       << msTotal1 << "," << index1 << ","
		       << msTotal2 << "," << index2 << ","
		       << msTotal3 << "," << index3 << "\n";
	}
	std::cout << "Testing varying base size: " << 100 << "%" << "\r";
	std::cout << "\n";
	output.close();

	// Reset base number
	narq::setBase(MAX_BP);
}

// ========================================================================= //
void varyModSize() {
	// Open output file and write header column names
	std::ofstream output(outputFile_mup.c_str());
	if (!output)
	{
		std::cerr << "Could not open results file " << outputFile_mup << "\n";
		return;
	}
	output << "needle size, "          << "haystack size, "
	       << "base number, "          << "mod number, "
	       << "naive time (ms), "      << "index, "
	       << "rabin karp - LV (ms), " << "index, "
	       << "rabin karp - MC (ms), " << "index\n";

	std::string haystack = generateString(MAX_H, 'a');
	std::string needle = generateString(MIN_N - 1, 'a');
	needle += "b";

	for (size_t i = MIN_MP; i <= MAX_MP; i+=100)
	{
		int percentComplete = (i / (double) MAX_MP) * 100;
		std::cout << "Testing varying mod size: " << percentComplete << "%" << "\r";
		fflush(stdout);

		// Set mod number for rolling hash
		narq::setMod(i);

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
		double msTotal3 = 1000.0 * (end3 - start3) / CLOCKS_PER_SEC;
		output << MIN_N    << "," << MAX_H  << ","
		       << MAX_BP   << "," << i      << ","
		       << msTotal1 << "," << index1 << ","
		       << msTotal2 << "," << index2 << ","
		       << msTotal3 << "," << index3 << "\n";
	}
	std::cout << "Testing varying mod size: " << 100 << "%" << "\r";
	std::cout << "\n";
	output.close();

	// Reset mod number
	narq::setMod(MAX_MP);
}
