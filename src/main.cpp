/*
@file main.cpp
@brief Execution point for narq
@author Drew Guarnera, Heather Michaud
*/

#include "tools.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

std::string expectedInput = "narq [-copy] <original.txt> <copy.txt> <number of partitions>\n";

//! @brief Executes visual tests for brute force and various Rabin Karp algorithms
void debug();

int main(int argc, const char* argv[])
{
	if (argc != 5) {
		std::cerr << "Invalid arguments. Expected: \n";
		std::cerr << expectedInput;
		return 1;
	}

	std::string approach  = argv[1];
	std::string fNeedle   = argv[2];
	std::string fHaystack = argv[3];

	int numNeedles = 0;
	std::stringstream ss;
	ss << argv[4];
	ss >> numNeedles;

	std::ifstream inputNeedle(fNeedle.c_str());
	if (!inputNeedle)
	{
		std::cerr << "Could not open original text file: " << fNeedle << "\n";
		return 2;
	}


	std::ifstream inputHaystack(fHaystack.c_str(), std::ios::in | std::ios::binary);
	if (!inputHaystack)
	{
		std::cerr << "Could not open suspected copied text file: " << fHaystack << "\n";
		return 2;
	}

	std::string needle;
	inputNeedle.seekg(0, std::ios::end);
	needle.resize(inputNeedle.tellg());
	inputNeedle.seekg(0, std::ios::beg);
	inputNeedle.read(&needle[0], needle.size());
	inputNeedle.close();

	std::vector<std::string> needles = narq::partition(needle, numNeedles);

	// Read entirue haystack file into the haystack string.
	std::string haystack;
	inputHaystack.seekg(0, std::ios::end);
	haystack.resize(inputHaystack.tellg());
	inputHaystack.seekg(0, std::ios::beg);
	inputHaystack.read(&haystack[0], haystack.size());
	inputHaystack.close();

	std::cout << "\nDetecting plagiarism using " << numNeedles << " partitions";
	std::vector<int> matches = narq::rabinKarpMulti(needles, haystack, numNeedles);

	int totalMatches = 0;
	for (int i = 0; i < numNeedles; ++i)
	{
		if (i == 0)
			std::cout << ", each containing " << needles[i].length() << " characters.\n";

		if (matches[i] > 0)
		{
			std::cout << std::left 
			          << std::setw(10) << matches[i] << std::setw(3) << " : "
			          << std::setw(50) << needles[i] << "\n";
	    }
		totalMatches += matches[i];
	}
	std::cout << "\nPlagiarism detection complete.\n";
	std::cout << "Used " << numNeedles << " partitions, each containing "
	          << needles[0].length() << " characters.\n";
	std::cout << "Total matches: " << totalMatches << "\n";

	return 0;
}
