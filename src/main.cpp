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

	return 0;
}
