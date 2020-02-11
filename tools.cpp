/* @copydoc tools.hpp */

#include "tools.hpp"
#include <iostream>
#include <map>
#include <algorithm>

namespace narq
{
	const unsigned int BASE = 257;        // reduces collision in hash function
	const unsigned int MOD  = 1000000007; // number of elements in hash table

	// --------------------------------------------------------------------- //
	std::vector<int> rabinKarpMulti(std::vector<std::string>& needles, std::string haystack, int numNeedles)
	{
		// Initialize to 0 matches for each needle
		std::vector<int> matches(numNeedles);
		for (int i = 0; i < numNeedles; ++i)
			matches.push_back(0);

		long long hn[numNeedles];
		long long haystackHash = 0;
		long long power        = 1;

		// Compute hash for each needle
		size_t m = needles[0].size();
		for (int i = 0; i < numNeedles; ++i) {
			hn[i] = rhash(needles[i]);
		}
		
		for (size_t i = 0; i < needles[0].size(); ++i)
			power = (power * BASE) % MOD; // power = BASE ^ (size of string to search for)

		for (size_t i = 0; i < haystack.size(); ++i)
		{
			// Calculate the rolling hash for the haystack
			haystackHash = haystackHash * BASE + haystack[i];
			haystackHash = haystackHash % MOD;

			// "Skip", or remove, previous strings from the haystack
			if (i >= m - 1)
			{
				if (i >= m) 
				{
					haystackHash -= power * haystack[i - m] % MOD;
					if (haystackHash < 0)
						haystackHash += MOD;
				}

				// Check if hashes are equal
				for (int k = 0; k < numNeedles; ++k) 
				{
					if (hn[k] == haystackHash)
						matches[k]++;
				}
			}
		}
		return matches;
	}

	unsigned long long rhash(const std::string & s)
	{
		long long ret = 0;
		for (size_t i = 0; i < s.size(); ++i)
		{
			ret = ret * BASE + s[i];
			ret = ret % MOD;
		}
		return ret;
	}

	std::vector<std::string> partition(std::string &s, int numPartitions)
	{
		std::vector<std::string> needles;
		int m = s.size();
		int n = m / numPartitions;
		for (int i = 0; (i+n) <= m; i += n)
		{
			std::string needle = s.substr(i, n);
			needles.push_back(needle);
		}
		return needles;
	}

}
