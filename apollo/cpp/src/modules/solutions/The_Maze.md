## The Maze LintCode 787

There is a ball in a maze with empty spaces and walls. The ball can go through empty spaces by rolling up, down, left or right, but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction.

Given the ball's start position, the destination and the maze, determine whether the ball could stop at the destination.

The maze is represented by a binary 2D array. 1 means the wall and 0 means the empty space. You may assume that the borders of the maze are all walls. The start and destination coordinates are represented by row and column indexes.


## Example

Input:

```txt
map = 
[
 [0,0,1,0,0],
 [0,0,0,0,0],
 [0,0,0,1,0],
 [1,1,0,1,1],
 [0,0,0,0,0]
]
```

Output:
true

Explanation:

``` txt
0,4> -> <0,3> -> <1,3> -> <1,2> -- rolling to --> <1,0> -> <2,0> -> <2,1> -- rolling to --> <2,2> -> <3,2>
```
