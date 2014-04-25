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

std::string expectedInput = "narq -[naive|montecarlo|lasvegas] <needle.txt> <haystack.txt>\n"   \
"The first argument provides the apprach used to search for a pattern. The second argument gives "\
"is a text file where the needle or needles are read in. The naive approach only accepts one "    \
"needle. The Rabin Karp Monte-Carlo and Las-Vegas approaches can accept multiple needles, which " \
"are separated by a new line character. The third argument is a text file whose content is the "  \
"body of text that the needles are searched for.\n\n"\
"narq [-copy] <original.txt> <copy.txt> <number of partitions>\n";

//! @brief Executes visual tests for brute force and various Rabin Karp algorithms
void debug();

int main(int argc, const char* argv[])
{
	//debug();
	
	if (argc < 4 || argc > 5) {
		std::cerr << "Invalid arguments. Expected: \n";
		std::cerr << expectedInput;
		return 1;
	}

	std::string approach  = argv[1];
	std::string fNeedle   = argv[2];
	std::string fHaystack = argv[3];

	if (argc == 4)
	{
		std::ifstream inputNeedle(fNeedle.c_str());
		if (!inputNeedle)
		{
			std::cerr << "Could not open needle text file: " << fNeedle << "\n";
			return 2;
		}

		std::ifstream inputHaystack(fHaystack.c_str(), std::ios::in | std::ios::binary);
		if (!inputHaystack)
		{
			std::cerr << "Could not open haystack text file: " << fHaystack << "\n";
			return 2;
		}

		inputNeedle.close();

		// Read entirue haystack file into the haystack string.
		std::string haystack;
		inputHaystack.seekg(0, std::ios::end);
		haystack.resize(inputHaystack.tellg());
		inputHaystack.seekg(0, std::ios::beg);
		inputHaystack.read(&haystack[0], haystack.size());
		inputHaystack.close();

		if (approach == "-naive")
		{
			// Use brute force algorithm
			std::cout << "Using naive, brute force approach.\n";
		}
		else if (approach == "-montecarlo")
		{
			// Use monte carlo multi
			std::cout << "Using Rabin-Karp Monte-Carlo approach.\n";
		}
		else if (approach == "-lasvegas")
		{
			// Use las vegas multi
			std::cout << "Using Rabin-Karp Las Vegas approach.\n";
		}
		else
		{
			std::cerr << "Invalid arguments. Expected: \n";
			std::cerr << expectedInput;
			return 1;
		}
	}
	else
	{
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

		std::cout << "Detecting plagiarism using " << numNeedles << " partitions...\n";
		std::vector<int> matches = narq::rabinKarpMulti(needles, haystack, numNeedles);

		int totalMatches = 0;
		for (int i = 0; i < numNeedles; ++i)
		{
			//std::cout << std::right << std::setw(15) << needles[i] << ":"
		    //          << std::left << std::setw(15) << matches[i] << "\n";
			totalMatches += matches[i];
		}
		std::cout << "Total matches: " << totalMatches << "\n";

	}

	return 0;
}

void debug()
{
	std::cerr << "\n=======================================\n";
	std::cerr << std::setw(10) << "naive"
	          << std::setw(15) << "rabin-karp LV"
	          << std::setw(15) << "rabin-karp MC"
	          << "\n";

	std::cerr << std::setw(10) << narq::bruteForce("test", "testing")
	          << std::setw(15) << narq::rabinKarpLV("test", "testing")
	          << std::setw(15) << narq::rabinKarpMC("test", "testing")
	          << "\n";

	std::cerr << std::setw(10) << narq::bruteForce("circle", "oval")
	          << std::setw(15) << narq::rabinKarpLV("circle", "oval")
	          << std::setw(15) << narq::rabinKarpMC("circle", "oval")
	          << "\n";

	std::cerr << std::setw(10) << narq::bruteForce("scotch", "butterscotch")
	          << std::setw(15) << narq::rabinKarpLV("scotch", "butterscotch")
	          << std::setw(15) << narq::rabinKarpMC("scotch", "butterscotch")
	          << "\n";

	std::cerr << std::setw(10) << narq::bruteForce("b", "aaaaaaaaaaaaaaaaaaab")
	          << std::setw(15) << narq::rabinKarpLV("b", "aaaaaaaaaaaaaaaaaaab")
	          << std::setw(15) << narq::rabinKarpMC("b", "aaaaaaaaaaaaaaaaaaab")
	          << "\n";

	
	std::cerr << "\n=======================================\n";
	int numNeedles = 4;
	std::string needles[4] = {"aaa", "bbb", "ccc", "eee"};
	std::vector<std::string> needlesA (needles, needles + sizeof(needles) / sizeof(needles[0]) );

	std::string haystack = "abc aaa bbb ccc ddd eee abc";
	std::cerr << std::setw(20) << haystack << "\n";
	std::vector<int> result = narq::rabinKarpMulti(needlesA, haystack, numNeedles);
	std::cerr << "========= Matches ========\n";
	for (int i = 0; i < numNeedles; ++i) {
		std::cout << std::right << std::setw(15) << needlesA[i] << ":"
		          << std::left << std::setw(15) << result[i] << "\n";
	}
	std::cerr << "\n";

	haystack = "aaa";
	std::cerr << std::setw(20) << haystack << "\n";
	result = narq::rabinKarpMulti(needlesA, haystack, numNeedles);
	std::cerr << "========= Matches ========\n";
	for (int i = 0; i < numNeedles; ++i) {
		std::cout << std::right << std::setw(15) << needlesA[i] << ":"
		          << std::left << std::setw(15) << result[i] << "\n";
	}
	std::cerr << "\n";

	haystack = "ddddddd";
	std::cerr << std::setw(20) << haystack << "\n";
	result = narq::rabinKarpMulti(needlesA, haystack, numNeedles);
	std::cerr << "========= Matches ========\n";
	for (int i = 0; i < numNeedles; ++i) {
		std::cout << std::right << std::setw(15) << needlesA[i] << ":"
		          << std::left << std::setw(15) << result[i] << "\n";
	}
	std::cerr << "\n";

	haystack = "abc abc abc d eee";
	std::cerr << std::setw(20) << haystack << "\n";
	result = narq::rabinKarpMulti(needlesA, haystack, numNeedles);
	std::cerr << "========= Matches ========\n";
	for (int i = 0; i < numNeedles; ++i) {
		std::cout << std::right << std::setw(15) << needlesA[i] << ":"
		          << std::left << std::setw(15) << result[i] << "\n";
	}
	std::cerr << "\n";

	std::cerr << "=======================================\n";
	std::cerr << "Maximum size of string: ";
	std::string longString = "abcdefghijklmnopqrstuvwxyz";
	std::cerr << longString.max_size() << "\n\n";

	std::cerr << "=======================================\n";
	std::cerr << "Partitioning... \n";
	std::string s = "Here is a long string that should be partitioned. Wowee I'm a long string!";
	for (int i = 1; i <= 10; ++i) {
		std::cerr << "\nNumber of partitions = " << i << "\n";
		std::vector<std::string> res = narq::partition(s, i);
		std::cerr << "Partitions are: \n";
		for (int j = 0; j < res.size(); ++j) {
			std::cerr << "\t" << j << ": " << res[j] << "\n";
		}
		res.clear();
	}
}

