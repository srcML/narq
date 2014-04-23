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

int main(int argc, const char* argv[])
{

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

	std::cerr << "=======================================\n";
	
	std::vector<std::string> needles;
	
	needles.push_back("aaa");
	needles.push_back("bbb");
	needles.push_back("ccc");
	needles.push_back("eee");

	std::string haystack = "aabbcc ccc bbb aaa";
	std::cerr << std::left << std::setw(20) << haystack
	          << std::setw(5)  << narq::rabinKarpSet(needles, haystack) << "\n";

	haystack = "aaa";
	std::cerr << std::setw(20) << haystack
	          << std::setw(5)  << narq::rabinKarpSet(needles, haystack) << "\n";

	haystack = "ccc";
	std::cerr << std::setw(20) << haystack
	          << std::setw(5)  << narq::rabinKarpSet(needles, haystack) << "\n";

	haystack = "ddddddd";
	std::cerr << std::setw(20) << haystack
	          << std::setw(5)  << narq::rabinKarpSet(needles, haystack) << "\n";

	haystack = "abc abc abc d eee";
	std::cerr << std::setw(20) << haystack
	          << std::setw(5)  << narq::rabinKarpSet(needles, haystack) << "\n";

	std::cerr << "=======================================\n";

	std::string needlesA[4] = {"aaa", "bbb", "ccc", "eee"};

	haystack = "abc aaa bbb ccc ddd eee abc";
	std::cerr << std::setw(20) << haystack << "\n";
	narq::rabinKarpMulti(needlesA, haystack);
	std::cerr << "\n";

	haystack = "aaa";
	std::cerr << std::setw(20) << haystack << "\n";
	narq::rabinKarpMulti(needlesA, haystack);
	std::cerr << "\n";

	haystack = "ddddddd";
	std::cerr << std::setw(20) << haystack << "\n";
	narq::rabinKarpMulti(needlesA, haystack);
	std::cerr << "\n";

	haystack = "abc abc abc d eee";
	std::cerr << std::setw(20) << haystack << "\n";
	narq::rabinKarpMulti(needlesA, haystack);
	std::cerr << "\n";


	return 0;
}
