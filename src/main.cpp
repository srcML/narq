/*
@file main.cpp
@brief Execution point for narq
@author Drew Guarnera, Heather Michaud
*/

#include "tools.hpp"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

//! @brief Executes visual tests for brute force and various Rabin Karp algorithms
void debug();

int main(int argc, const char* argv[])
{
	debug();

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
	std::string needlesA[4] = {"aaa", "bbb", "ccc", "eee"};

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
	std::cerr << longString.max_size() << "\n";
}

