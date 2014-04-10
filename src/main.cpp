#include "tools.hpp"
#include <iostream>

int main(int argc, const char* argv[])
{
	std::cerr << narq::bruteForce("testing", "test") << "\n";
	std::cerr << narq::bruteForce("oval", "circle") << "\n";
	std::cerr << narq::bruteForce("butterscotch", "scotch") << "\n";
	std::cerr << narq::bruteForce("aaaaaaaaaaaaaaaaaaab", "b") << "\n";
	return 0;
}
