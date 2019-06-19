
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

##### Installation

See `project_root` at [my test repository for OA](https://github.com/yiakwy/Onsite-Blackboard-Code-Interview/tree/master/apollo/cpp)

Download the installation scripts I prepared for `grpc++-pubsub` project into the `project_root/scripts`

> wget https://raw.githubusercontent.com/yiakwy/grpc-gateway/master/scripts/install.sh

Execute the following script

> sh scripts/install.sh

should install all the dependencies for you.

Also see `thirdparties` for other modules installation.

##### Debug & Build

This script will automatically

> sh scripts/init\_xcode\_proj.sh

generate xcode files. You can also build by 

> sh scripts/build.sh

##### Solution Address

[Click here](https://github.com/yiakwy/Onsite-Blackboard-Code-Interview/blob/master/apollo/cpp/src/modules/solutions/lucky_draw_stone_tech.hpp)

##### GTest Snapshot

[Click here](https://github.com/yiakwy/Onsite-Blackboard-Code-Interview/blob/master/apollo/cpp/tests/gtest/test_lucky_draw_benchmark.cpp)

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

##### Solution Address

[Click here](https://github.com/yiakwy/Onsite-Blackboard-Code-Interview/blob/master/apollo/cpp/src/modules/solutions/integral_map.cpp)

##### Asymtotic Time Complexity

```
Big O(nlogn)
```

## Q3

##### QuickSort and Optimization

```
Given that an array of M length is constructed employing a random number generator of (0~65535) unsigned type.

Prob.1 Implement a quicksort routine for ascending sorting of the linked list. (Codes) (10 points)

Prob.2a Suppose we have the priori knowledge that a decent percentage of number generated is 0, say 25%. Improve the above routine. (2 points)

Prob.2b Suppose we have the priori knowledge of the random number’s PDF, which is not necessarily uniform. Improve the above routine. (3 points)


```

##### Solution Address

Check [all three in one solutions](https://github.com/yiakwy/Onsite-Blackboard-Code-Interview/blob/master/apollo/cpp/src/modules/solutions/quick_linked_sort.cpp)
