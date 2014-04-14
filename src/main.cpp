/*

@file main.cpp
@brief Execution point for narq

@author Drew Guarnera, Heather Michaud

*/

#include "tools.hpp"
#include <iostream>
#include <iomanip>

int main(int argc, const char* argv[])
{

	std::cerr << std::setw(10) << "naive"
	          << std::setw(15) << "rabin-karp"
	          << "\n";

	std::cerr << std::setw(10) << narq::bruteForce("test", "testing")
	          << std::setw(15) << narq::rabinKarp("test", "testing")
	          << "\n";

	std::cerr << std::setw(10) << narq::bruteForce("circle", "oval")
	          << std::setw(15) << narq::rabinKarp("circle", "oval")
	          << "\n";

	std::cerr << std::setw(10) << narq::bruteForce("scotch", "butterscotch")
	          << std::setw(15) << narq::rabinKarp("scotch", "butterscotch")
	          << "\n";

	std::cerr << std::setw(10) << narq::bruteForce("b", "aaaaaaaaaaaaaaaaaaab")
	          << std::setw(15) << narq::rabinKarp("b", "aaaaaaaaaaaaaaaaaaab")
	          << "\n";

	return 0;
}
