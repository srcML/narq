/* @copydoc tools.hpp */

#include "tools.hpp"
#include <iostream>
#include <map>
#include <algorithm>

namespace narq
{
	const unsigned int BASE = 257;        // reduces collision in hash function
	const unsigned int MOD  = 1000000007; // number of elements in hash table

	int bruteForce(std::string needle, std::string haystack)
	{
		int n = haystack.length();
		int m = needle.length();
		bool match = false;

		// Traverse the text body looking for the needle
		for (int i = 1; i <= n-m+1; ++i) {
			for (int j = 0; j < m; ++j) {
				match = true;
				if (haystack[i+j-1] != needle[j]) {
					match = false; // Characters were not equal - no match
					break;         // Break from looping needle characters
				}
			}
			if (match)             // If entire patten matches,
				return i-1;        // return beginning index of location
		}
		return -1;                 // Else pattern does not exist in the text
	}

	long rabinKarpLV(std::string needle, std::string haystack)
	{
		long long needleHash   = rhash(needle);
		long long haystackHash = 0;
		long long power        = 1;

		for (size_t i = 0; i < needle.size(); ++i)
			power = (power * BASE) % MOD; // power = BASE ^ (size of string to search for)

		for (size_t i = 0; i < haystack.size(); ++i)
		{
			// Calculate the rolling hash for the haystack
			haystackHash = haystackHash * BASE + haystack[i];
			haystackHash = haystackHash % MOD;

			// "Skip", or remove, previous strings from the haystack
			if (i >= needle.size())
			{
				haystackHash -= power * haystack[i - needle.size()] % MOD;
				if (haystackHash < 0)
					haystackHash += MOD;
			}

			// Check if hashes are equal
			if ((i >= needle.size() - 1) && (haystackHash == needleHash))
				return i - needle.size() + 1;
		}
		return -1; // Pattern does not exist in the text
	}

	long rabinKarpMC(std::string needle, std::string haystack)
	{
		long long needleHash   = rhash(needle);
		long long haystackHash = 0;
		long long power        = 1;

		for (size_t i = 0; i < needle.size(); ++i)
			power = (power * BASE) % MOD; // power = BASE ^ (size of string to search for)

		for (size_t i = 0; i < haystack.size(); ++i)
		{
			// Calculate the rolling hash for the haystack
			haystackHash = haystackHash * BASE + haystack[i];
			haystackHash = haystackHash % MOD;

			// "Skip", or remove, previous strings from the haystack
			if (i >= needle.size())
			{
				haystackHash -= power * haystack[i - needle.size()] % MOD;
				if (haystackHash < 0)
					haystackHash += MOD;
			}

			// Check if hashes are equal
			if ((i >= needle.size() - 1) && (haystackHash == needleHash))
			{
				// Monte Carlo addition: Check that strings are equal before returning.
				if (haystack.substr(i - needle.size() + 1, needle.size()) == needle)
					return i - needle.size() + 1;
			}
		}
		return -1; // Pattern does not exist in the text
	}

	// --------------------------------------------------------------------- //
	std::vector<int> rabinKarpMulti(std::string needles[], std::string haystack, int numNeedles)
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
			if (i >= m)
			{
				haystackHash -= power * haystack[i - m] % MOD;
				if (haystackHash < 0)
					haystackHash += MOD;

				// Check if hashes are equal
				for (int k = 0; k < numNeedles; ++k) 
				{
					if (hn[k] == haystackHash && haystack.substr(i - m + 1, m) == needles[k])
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

}
