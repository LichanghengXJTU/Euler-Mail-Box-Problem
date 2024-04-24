# Euler-Mail-Box-Problem
Euler Mail Box solution: Printing all the solutions of this problem. Need to be optimize. As the course assignments for the COMP000105( Taught By Dr. Shi) in XJTU.

This problem can be solved using simple DP thinking

Consider the situation of n:

1 2 3 4 5...... I-1 i i+1...... N-1 n

Given the solution of n-1, when exchanging n and i, it is obvious that each is different and can be traced back to each determined n-1 solution through inverse transformation.
Since n can be exchanged with n-1 numbers, there are (n-1) * f (n-1) solutions here.

Another possibility is that for a n-1 array where only one number i is the same, i and n can be exchanged to solve the problem. It is obvious that in this case, it can also be traced back to the determined original array, and this array will not appear in the previous situation.
So considering the differences in i (there are n-1 cases), each case corresponds to a definite n-2 solution (for the n-2 solution, the number no longer represents the number, but represents the number after subtracting i from 1 to n-1), so there are (n-1) * f (n-2) solutions here.

In summary, there are a total of (n-1) * (f (n-1)+f (n-2)) solutions here, and there is a recursive equation f (n)=(n-1) * (f (n-1)+f (n-2))

It is worth noticing that this code has two issues:
1. The next array has limited storage space and results in smaller solutions (7)
2. The next array has not been updated, which wastes space (there must be an update method, but I didn't think of it). However, considering that there are 265 solutions for n=6 and 1854 solutions for n=7, the difference in data storage between the two is 8.45 times. The theoretical number of solutions for n=8 is 14833, and the storage data is 9.14 times less than that of n=7. Therefore, the space consumption for n=6 and before can be ignored.

This is the method written in Chinese:

可以用简单的DP思想解决这个问题

考虑n的情况：

1	2	3	4	5 …………i-1	i	i+1……………………n-1	n

已知n-1的解，这时候交换n和i，明显的，每个都不相同，而且可以通过逆变换追溯到每一个确定的n-1解。
由于n可以和n-1个数进行交换，所以这里有(n-1)*f(n-1)个解。

还有一种可能是对于一个n-1个数组中只有一个数i相同的情况，可以交换i和n来求解。很明显，这种情况下也可以追溯到确定的原数组，且此数组不会出现在上一种情况中。
所以考虑i的不同（有n-1种情况），每种情况对应一个确定的n-2的解（对n-2的解来说数字不再代表数字，而是代表从1~n-1刨掉i后的第几个数），所以这里有(n-1)*f(n-2)个解。

综上这里 一共(n-1)*(f(n-1)+f(n-2))个解，有递推方程 f(n) = (n-1)*(f(n-1)+f(n-2))

值得注意的是，这串代码存在两个问题：
1.next数组存储空间有限,求解结果较小（7）
2.next数组没有更新，浪费空间（肯定有更新办法，但我没想到），但考虑到n=6的解是265个，n=7的解是1854个，二者存储数据量相差8.45倍，n=8的理论解个数是14833个，存储数据量相比n=7差9.14倍，所以n=6及以前的空间消耗可以忽略。
