## Description

```txt
You have 4 cards each containing a number from 1 to 9. You need to judge whether they could operated through *, /, +, -, (, ) to get the value of 24.
```

## Example

1. Input:

```txt
Input: [4, 1, 8, 7]
```

2. Output:

> True

2. Explanation:

```
The arithmetic expression is equivalent to a expression tree where parenthesis eliminated. Here are possible solutions using brute force search of possible tree structures, we find:

8*(7-4/1)
8*(4/1-7)
(4-8)*(1-7)
(4-8)*(7-1)
(8-4)*(1-7)
(8-4)*(7-1)
4*8-1+7
1+7-4*8
(1-7)*(4-8)
(1-7)*(8-4)
(7-1)*(4-8)
(7-1)*(8-4)

```
