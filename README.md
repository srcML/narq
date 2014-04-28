# Narq #

Final project for 3460:635 Advanced Algorithms that utilizes the Rabin-Karp string matching algorithm to detect plagiarism.

### Application Usage

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