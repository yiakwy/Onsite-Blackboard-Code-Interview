Monkey Steps
============

Task Specification:

Given a array A of length K. A[k] 0<=k<=K-1 denotes the time a stone appearance under a river. The height of the river consistantly decrease. A Moneky at position -1, want to jump to position K. 

A moneky can jumpt at most D steps. It can jumpt forward if distance between a stone is less than D. Otherwise, it must wait. A money can jump to the opporsite of the river at position N or never arrive at the point.

For example,

A[0] = 1
A[1] = -1
A[2] = -1
A[3] = 2
A[4] = 0
A[5] = 5


``` txt
      start 0  1  2  3  4  5  end 
 t= 2       ok -  - ok ok  -  end 
```

Hence the monkey can jump continuously at second 2 towards to end point.

Please determine a solution which returns the mininum time the monkey used to get to the end point. If it cannot do that, return -1.

The expected worse time complexity and space complexity are O(K+Max(A[K])) separately. Good Luck!
