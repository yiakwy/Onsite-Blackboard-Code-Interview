
## Q1

#### Lucky draw

```
You'll need to implement a Lucky Draw program using C/C++. Actually, you're not +only required to write a program. Instead, you need to compose a shared library, which exposes only 1 function.
The exported function's declaration looks like below:
  
  int lucky_draw (int persons[]);
 
'persons' array is a fixed length integer array represent IDs of persons. The length of the array is 100.
The requirements of the lucky_draw function is below:
A. If calling lucky_draw() 100 times, it should return a unique ID for each call. Saying, a person cannot be luck twice.
B. Choose a person randomly!
 
There're 2 extra requirements for this programming task.
1.	The shared library should have a unit test using google test. i.e. you should write test for lucky_draw function
For more information, you can check the following link
https://github.com/google/googletest
 
1.	The entire project (shared library + unitest) should be organized using CMake
https://cmake.org
 
In summary, I expect to receive the following files in a compressed format.
1. draw.cc and draw.h
2. unitest file
3. CMakeLists.txt, which organizes everything
```

#### Answer

```txt
[==========] Running 1 test from 1 test case.
[----------] Global test environment set-up.
[----------] 1 test from LuckyDrawTest
[ RUN      ] LuckyDrawTest.BENCH_100_CALLS
[       OK ] LuckyDrawTest.BENCH_100_CALLS (0 ms)
[----------] 1 test from LuckyDrawTest (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test case ran. (1 ms total)
[  PASSED  ] 1 test.
Program ended with exit code: 0
```

## Q2

#### Find a given value in an integral map

```
Integral map is defined as a matrix I(x,y) with monotonic increasing row and column, i.e.


Fig. Illustration of an integral map

Prob.1 Develop a less complex algorithm compared with global search, to find a designated value v in the map. (Codes) (10 points)

```

#### Answer
