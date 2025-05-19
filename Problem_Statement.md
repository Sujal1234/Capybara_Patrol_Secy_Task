# Santa's little integers

<p align="center"><img src="images/bombardino.jpg"></p>

It's Christmas and the king of the Bombinawa kingdom is once again disguising himself as Santa Claus to set up the festival mood for his people, the Bombardino Crocodilos.

The Bombardino Crocodilos love maths so the children want integers as their Christmas presents.  
There are $n$ children numbered $1$ to $n$ and each one wants an $\bf{integer}$ $a_i$ between $1$ to $10^5$ (inclusive).  
However, some of these children are best friends. They only want integers such that the sum of the integers both friends receive is $\bf{odd}$, because the arch nemeses of the Bombardino Crocodilos, the Tralalero Tralalas, worship even numbers.

As the king it is your duty to figure out whether it is possible to gift integers to all the children such that all the pairs of best friends are happy. If yes, then you need to output the integers you will gift to each children.

## Input
The first line contains a integer $n$ $(2 \leq n \leq 10^5)$, the number of children.

The second line contains an integer $m$ $(1 \leq m \leq 10^7)$, the number of best friend pairs. It is guaranteed that every unordered pair is distinct.

The next $m$ lines each contain two space-separated integers $x$, $y$ $(1 \leq x, y \leq n)$ denoting that child $x$ and child $y$ are best friends.

## Output
If it is impossible to gift integers to the children such that the sum of integers in every best friend pair is odd, then print $-1$.

Otherwise print $n$ integers $a_1$ to $a_n$ where $a_i$ is the integer the $i^{th}$ child receives.

### Example
#### Input
```
5
4
1 5
2 5
5 3
4 5
```
#### Output
```
321 13 9025 1 2
```
#### Note
Child $5$ is friends with all other children in this test case so $a_1+a_5=323$, $a_2+a_5=15$, $a_3+a_5=9027$, $a_4+a_5=3$ all of which are even. So all the children are happy.

### Example
#### Input
```
6
3
2 1
1 3
2 3
```
#### Output
```
-1
```