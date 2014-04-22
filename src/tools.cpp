/*

@copydoc tools.hpp

*/

#include "tools.hpp"
#include <iostream>

namespace narq
{
	//! @todo We should change these to be arguments to our functions, or to the
	//!  program, so that we can test the inaccuracy of Las Vegas style and the
	//!  increased time complexity of Monte Carlo style Rabin-Karp when provided
	//!  hash tables with high collision rates
	unsigned int BASE = 257;        // reduces collision in hash function
	unsigned int MOD  = 1000000007; // number of elements in hash table

	void setBase(long long base) { BASE = base; }
	void setMod(long long mod) { MOD = mod; }

	// --------------------------------------------------------------------- //
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

	// --------------------------------------------------------------------- //
	long rabinKarpLV(std::string needle, std::string haystack)
	{
		long long needleHash   = rhash(needle);
		long long haystackHash = 0;
		long long power        = 1;

		// power = BASE ^ (size of string to search for)
		for (size_t i = 0; i < needle.size(); ++i)
			power = (power * BASE) % MOD;

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
		return -1;
	}

	// --------------------------------------------------------------------- //
	long rabinKarpMC(std::string needle, std::string haystack)
	{
		long long needleHash   = rhash(needle);
		long long haystackHash = 0;
		long long power        = 1;

		// power = BASE ^ (size of string to search for)
		for (size_t i = 0; i < needle.size(); ++i)
			power = (power * BASE) % MOD;

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
				// Monte Carlo addition: Check that strings are equal before
				// returning.
				if (haystack.substr(i - needle.size() + 1, needle.size()) == needle)
					return i - needle.size() + 1;
			}
		}
		return -1;
	}

	// --------------------------------------------------------------------- //
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
