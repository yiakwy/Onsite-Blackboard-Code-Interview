## Questions

#### Title:  Minium operations of flipping of a tree values \(yiak.wy@gmail.com\)

1. Given a tree and its initial values and final ones. Find minimum operations to used from initial values to final ones with so defined
flipping:

> If you flip one of nodes, descendants in alternating layers of those nodes will be also filped.

2. Input-Output examples:

###### Input:

```
N // Number of nodes
1 : 2, 3, 4, 5 // Parent: children list. 
3 : 7, 8
5 : 9, 10
7 : 11

initial values: 1 0 1 0 1 0 1 0 1 0 
final values: 1 0 0 0 0 0 1 0 1 1
```

###### Expected Output:

With above input, we expect 3 operations to flip initial values to final ones:

```
flip 3
flip 11
flip 5
flip 11
3
```
###### Your job:

Your are required to write codes to parsing input and print computed output onto console for testing.
