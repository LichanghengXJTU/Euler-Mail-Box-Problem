#include <iostream>
#include <vector>
using namespace std;

//声明函数
//Anouncement
void create ( vector<vector<int>>& pre, vector<vector<int>>& chart, vector<vector<int>>& result,int n);
void putin( vector<int>& it, vector<vector<int>>& next, int n);
void putin2( vector<int>& it, vector<vector<int>>& next, int n);

//递归更新next数组求解解法
//Recursive Update Next Array Solution
void create(vector<vector<int>>& pre, vector<vector<int>>& chart, vector<vector<int>>& next, int n)
{
        if (n == 2)
        {
                next = chart;
                return;
        }


        next = {{}};
        create(pre, chart, next, n - 1);

        for( auto it = chart.begin(); it < chart.end(); it++)
        {
                //n>=3时执行n换前面n-1解中的任意数的方法
                //The method of executing n to replace any number in the previous n-1 solution when n >= 3
                if ( n >= 3)
                {
                        putin(*it,next,n);
                }

        }

        for( auto it = pre.begin(); it < pre.end(); it++)
        {
                //n>=4再执行前n-1个数有一个相同，用n替换它的解法
                //Replace the solution with n if there is one of the same n-1 numbers when n >= 4
                if ( n >= 4)
                {
                        putin2(*it,next,n);
                }
        }

        //更新数组，实现迭代更新（简单的DP思想）
        //Update arrays and implement iterative updates (simple DP mindset)
        pre = chart;
        chart = next;

}

//n换前面n-1解中的任意数的方法
//The method of replacing any number in the previous n-1 solution with n
void putin( vector<int>& it, vector<vector<int>>& next, int n)
{
        int i = 0;
        for(i = 0; i < n-1; i++)
        {
                vector<int> temp = it;

                //实现i与n的调换
                //Swap index i with index n
                temp.push_back(temp[i]);
                temp[i] = n;

                next.push_back(temp);

        }

}

//前n-1个数有一个相同，用n替换它的解法
//The solution of replacing the only same on among the first n-1 numbers with n
void putin2( vector<int>& it, vector<vector<int>>& next, int n)
{
        int i = 0;
        it.push_back(n-1);
        for( i = 0; i < n - 1; i++)
        {
                int j = 0;
                for( j = 0; j < n - 1; j++)
                {
                        //找到为i的位置j
                        //Find position j for i
                        
                        //因为没有办法直接实现一个数组中只有一个数相同（没有保存单一错误解的表格，否则数据量太大了）这里采用先假定我要换第i个，找到为i的位置j，交换i和j, 再把n-1放进数组中，交换n-1和j，很明显这是一个双射，对每一个n-2解都有唯一确定的n-1数组使得只有第i位相同。这时候交换i和n。
                        ////Because it is not possible to directly implement an array where only one number is the same (without a table that stores a single incorrect solution, otherwise the amount of data is too large), here we assume that I need to replace the i-th one, find the position j for i, exchange i and j, and then put n-1 into the array, exchange n-1 and j. Obviously, this is a bijective, and for each n-2 solution, there is a unique and definite n-1 array so that only the i-th position is the same. At this point, exchange i and n.
                        if ( it[j]-1 == i)
                        {      
                                //注意，我这里说的位置都是+1后的结果
                                ////Note that the positions I am referring to here are all the results after+1
                                vector<int> temp = it;

                                //置换ij
                                //Swap the index i and index j
                                temp[j] = temp[i];
                                temp[i] = i;

                                //放进n-1（n-1位与j置换）
                                //Put n-1 in the array( BY swapping the index of n-1 and index of j
                                temp[n-2] = temp[j];
                                temp[j] = n-1;

                                //置换i与n
                                //Swap index i and index n
                                temp.push_back(i+1);
                                temp[i] = n;

                                next.push_back(temp);
                                break;
                        }
                }
        }
}

int main ()
{
        vector<vector<int>> pre;
        //最初解，没有办法，必须先解出2的解
        //The initially solving is impossible, we must first solve for the solution of 2
        vector<vector<int>> chart = {{2,1}};
        int n;
        //输入信的个数
        //Type in the number of letters
        cin>>n;
        vector<vector<int>> result;
        //构造next数组求得解（因为某种奇怪的原因，我没法实现重新更新next数组，只能不断叠加，所以输出要进行如下处理
        //Construct the next array to obtain the solution (for some strange reason, I cannot update the next array again and can only stack it continuously, so the output needs to be processed as follows)
        create(pre,chart,result,n);


        int count = 0;
        for(auto it = result.begin(); it < result.end(); it++)
        {       
                //只输出长度为n的数组
                //Only print the array whose length is n
                if ( it -> size() == n )
                {
                        for( auto itt = (*it).begin(); itt < (*it).end(); itt++)
                        {
                                cout<<*itt<<" ";
                        }
                        cout<<endl;
                        count++;
                }
        }

        cout<<"The euler mail box problem has "<<count<<" solutions";//求解解的个数

        //这串代码存在两个可以基本忽略的问题：
        //1. next数组没有更新，浪费空间（肯定有更新办法，但我没想到），但考虑到n=6的解是265个，n=7的解是1854个，二者存储数据量相差8.45倍，n=8的理论解个数是14833个，存储数据量相比n=7差9.14倍，所以n=6及以前的空间消耗可以忽略
        //2.用双vector存储有空间限制，可以用链表解决问题，但是在代码实现上增加了一定的复杂度

        //There are two issues with this code that can be basically ignored:
        //1 The next array has not been updated, which wastes space (there must be an update method, but I didn't think of it). However, considering that there are 265 solutions for n=6 and 1854 solutions for n=7, the difference in storage data between the two is 8.45 times. The theoretical number of solutions for n=8 is 14833, and the storage data is 9.14 times less than that of n=7. Therefore, the space consumption for n=6 and before can be ignored.
        //2. Using dual vectors for storage has space limitations and can be solved using linked lists, but it adds some complexity to the code implementation.

}
