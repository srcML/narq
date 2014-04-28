# Narq #

Final project for 3460:635 Advanced Algorithms that utilizes the Rabin-Karp string matching algorithm to detect plagiarism.

### Application Usage

__Basic Exection:__

```
narq -[naive|montecarlo|lasvegas] <needle.txt> <haystack.txt>
```

* The first argument provides the approach used to search for a pattern.
* The second argument gives a text file where the needle or needles are read in.
	* _Note: The naive approach only accepts one needle, while the Rabin-Karp Monte Carlo and Las Vegas approaches can accept multiple needles separated by a new line character._
* The third argument is a text file whose content is the body of text to be searched.

__Plagiarism Detection:__

```
narq -copy <original.txt> <copy.txt> <number of partitions>
```

* The first argument activates the plagiarism mode.
* The second argument gives the original text file.
* The third argument is a second text file whose content is the body of text to be searched for patterns from the first file.
* The fourth argument is the number of partitions or patterns to split the original file into.


### Building Narq

Create a bin directory inside the root of the Narq directory:

```
mkdir bin
```

Run ```make```

Run the application using:

```
./bin/narq
```

_See above argument patterns_

Run the test suite using:

```
./bin/test
```

### Supported Platforms:

* OSX
* Ubuntu Linux 12.04 and 14.04