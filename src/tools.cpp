/*

@copydoc tools.hpp

*/

#include "tools.hpp"
#include <iostream>
#include <map>
#include <algorithm>

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
	std::vector<int> rabinKarpMulti(std::string needles[], std::string haystack, int numNeedles) {
		//int numNeedles = 4; // (sizeof(needles)/sizeof(*needles));

		std::vector<int> matches(numNeedles);
		for (int i = 0; i < numNeedles; ++i)
			matches.push_back(0);

		std::cerr << "Have " << numNeedles << " total needles. \n";
		long long hn[numNeedles];
		long long haystackHash = 0;
		long long power        = 1;

		// Compute hash for each needle
		size_t m = needles[0].size();
		for (int i = 0; i < numNeedles; ++i) {
			hn[i] = rhash(needles[i]);
		}

		// power = BASE ^ (size of string to search for)
		for (size_t i = 0; i < needles[0].size(); ++i)
			power = (power * BASE) % MOD;

		for (size_t i = 0; i < haystack.size(); ++i)
		{
			if (i >= m - 1) {
				std::cerr << "Checking haystack substring: " 
			    	      << haystack.substr(i - m + 1, m) << "\n";
			}

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
					std::cerr << "\tChecking needle: '" << needles[k] 
					          << "' against '" << haystack.substr(i - m + 1, m) << "'\n";
					if (haystack.substr(i - m + 1, m) == needles[k]) {
						std::cerr << "\t\tCHEAT: Found a match at haystack index: " << i << "\n";
						std::cerr << "\t\tHaystack hash: " << haystackHash << "\n";
						std::cerr << "\t\tNeedle hash: " << hn[k] << "\n";
					}
					if (hn[k] == haystackHash && 
						haystack.substr(i - m + 1, m) == needles[k]) 
					{
						//addMatch(k, (int) i);
						std::cerr << "\t\tFound a match at haystack index: " << i << "\n";
						std::cerr << "\t\tMatches pattern: " << needles[k] << "\n";
						matches[k]++;
					}
				}

			}
		}
		std::cerr << "End multi" << "\n";
		return matches;
	}

	void addMatch(int needleNumber, int haystackIndex) {

	}


	// --------------------------------------------------------------------- //
	long rabinKarpSet(std::vector<std::string> needles, std::string haystack)
	{
		std::map<long long, int> hneedles;
		for (size_t i = 0; i < needles.size(); ++i) {
			hneedles.insert( std::make_pair<long long, int>(rhash(needles[i]), i));
		}

		long long haystackHash = 0;
		long long power        = 1;

		// power = BASE ^ (size of string to search for)
		for (size_t i = 0; i < needles[0].size(); ++i)
			power = (power * BASE) % MOD;

		for (size_t i = 0; i < haystack.size(); ++i)
		{
			// Calculate the rolling hash for the haystack
			haystackHash = haystackHash * BASE + haystack[i];
			haystackHash = haystackHash % MOD;

			// "Skip", or remove, previous strings from the haystack
			if (i >= needles[0].size())
			{
				haystackHash -= power * haystack[i - needles[0].size()] % MOD;
				if (haystackHash < 0)
					haystackHash += MOD;
			}

			// Check if hashes are equal
			if ((i >= needles[0].size() - 1) && (hneedles.find(haystackHash) != hneedles.end()))
			{
				// Monte Carlo addition: See if substring is found in set before returning
				// Check that strings are equal before returning.

				std::string haystackSub = haystack.substr(i - needles[0].size() + 1, needles[0].size());
				for (size_t i = 0; i < needles.size(); ++i) {
					if (haystackSub == needles[i])
						return i - needles[i].size() + 1;
				}
			}
		}
		return -1;
	}

	// --------------------------------------------------------------------- //

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
