#include "tools.hpp"
#include <iostream>

namespace narq
{
	int bruteForce(std::string textBody, std::string pattern)
	{
		int n = textBody.length();
		int m = pattern.length();
		bool match = false;

		for (int i = 1; i <= n-m+1; ++i) {
			for (int j = 0; j < m; ++j) {
				match = true;
				if (textBody[i+j-1] != pattern[j]) {
					match = false;
					break;
				}
			}
			if (match)
				return i-1;
		}
		return -1;

	}

	
}