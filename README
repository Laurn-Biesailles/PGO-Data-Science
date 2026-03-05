====================
 ____   ____  ___  
|  _ \ / ___|/ _ \ 
| |_) | |  _| | | |
|  __/| |_| | |_| |
|_|    \____|\___/ 
                   
====================

This is a group assignment for four people. If you have less than four people, some people can take more than one task. 

The goal here is to teach you real-world optimization strategies beyond the basics. The basics are:
1. Pick the right data structure for the job (if your Big-O is terrible your runtime will be terrible)
2. Pick the right algorithm for the job (ditto, nothing will help if your Big-O is bad)
3. When you're doing development, code slow-and-safe (enable ASAN and UBSAN and the safe C++ library), but turn all this off and turn on -O3 (the optimizer) in the compiler and recompile everything


===============================================================================================

Your group will need to make a Github, and each partner will need to work in their own branches

You should work in your branch until you have something to share, then commit it and push it to main with a pull request. Your partners should review your PR and approve it.

In your README.md you should list the jobs each person takes. Give the Data Scientist position to the student who is least likely to procrastinate as literally everyone else's job depends on them, and if they procrastinate the project will fail to complete on time.

===============================================================================================

Person 1 - The Data Scientist

Your job is to do data science and discover interesting things from a data file you download.

Tasks:
1. Go onto Kaggle (https://www.kaggle.com/) and download an interesting CSV dataset that is reasonably large
2. Import the CSV file into your C++ program
3. Do something interesting with the data (pitch it to me) that will take between 10 seconds and 1 minute to run
	A. It needs to have multiple nested branches
	B. It needs to have multiple loops
4. Update the README.md for your project describing what you are doing
5. Your source code must have multiple .cc and .h files with function calls between the different files.
6. Make a Makefile that will handle all the different compilation options (Gcov, PGO generate, PGO use, LTO, -O3, etc)
	A. It should have a make clean option that will erase all .gcda, .gcno, and .gcov files
	B. Down below when there are examples of how to compile a simple program with just main.cc in it, you will need to incorporate those into the Makefile
	C. Your partners can edit and revise the Makefile as well
7. Write up things you find interesting about your data analysis and send it to The Instrumenter for their report

===============================================================================================

Person 2 - The Tester

1. Get gcov to work:
	A. Compile the code with: \g++ -O0 --coverage
	B. Run a.out a bunch of times
	C. Generate a coverage file via: gcov -o a-main main.cc
2. Make tests:
	A. Make several small demo .csv files
	B. Figure out what the output of the program should be for each one
	C. Run the code (with gcov coverage on) and verify all test cases are passed
	D. If your code takes input, write input tests for those as well, both good, bad, and edge.
3. Validate that you have 100% coverage for every branch and loop in the code using Gcov. In other words, if you start with a clean Gcov slate and run all the tests, it should show every line of code getting exercised by your tests
4. Generate an HTML version of your Gcov report and attach it in the report of The Instrumenter.
5. If you find bugs in the code, report them to The Data Scientist to fix

===============================================================================================

Person 3 - The Instrumenter

1. Your job is to collect timing data for each part of the code and to write a report that will be submitted on Canvas showing how long the program takes to run with all the different options of:
	A. Optimizer off, ASAN and UBSAN on
	B. Optimizer off, ASAN and UBSAN off
	C. O3 Optimizer on, ASAN and UBSAN on
	D. O3 Optimizer on, ASAN and UBSAN off
		D2. Ofast Optimizer on, ASAN and UBSAN off (if you're using floats)
	E. PGO + O3 on, ASAN and UBSAN off
	F. PGO + LTO + O3 on, ASAN and UBSAN off
	G. Likely+Unlikely + PGO + LTO + O3 on, ASAN and UBSAN off

2. Collect end to end timing by running "time a.out" and parse the output of time and report it to me in human readable format for each of these optimization options

3. For each of these optimization options, report how long the most important loop in your code takes to run. You can either time the loop using the C way with clock() or the C++ way with chrono.
	A. Call clock() before the loop then after the loop and subtract the results to get how many microseconds the loop took to run. This is the C way of timing code.
	B. The C++ way uses the chrono library. Here's some demo code:
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;
using sc = steady_clock;
int main() {
    auto start = sc::now();
    for (int i = 0; i < 1'000'000; i++) {
        cout << rand() % 100;
    }
    auto end = sc::now();
    cerr << (duration<double>(end - start)).count() << endl;
}

This code above will print out how long the for loop took to run.

Report how long your most important loop takes to run with all of the above compilation options (A-G)

4. For any important branches inside of the for loop, try using the [[likely]] or [[unlikely]] tags and see if that affects the running time. This is optimization option G above.

===============================================================================================

Person 4 - The Pogo Stick

It is your job to do profile guided optimization (PGO), perfing, and LTO.

PGO:

1. Compile the code with \g++ -O3 -std=c++26 -fprofile-generate main.cc 
2. Run the code extensively and repeatedly, including using all tests made by The Tester so you have full code coverage. This will save profiling data to disk.
3. Compile the code again this time with \g++ -O3 -std=c++26 -fprofile-use main.cc. When you compile it with -fprofile-use, it will use the profile data to optimize your code
4. Hand this to the Instrumenter to time (it is Optimization option E above)

Perfing:

1. Compile the code with: \g++ -O3 -g -fno-omit-frame-pointer -std=c++26 main.cc
2. Run the code with: perf record -g a.out and run through all the tests and such
3. Put the perf report into a text file with: perf report --stdio > perf_report.txt
4. View perf_report.txt and see which functions are calling which functions and what percentage of time is spent in each function
5. Write up things you find interesting about this and send it to The Instrumenter for their report

LTO:

1. Add -flto to your compile flags
2. Make clean
3. Make
4. Rerun the timings and hand it to the Instrumenter (this is Optimization options F and G above)
