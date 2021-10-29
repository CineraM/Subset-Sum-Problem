# Subset-Sum-Problem
DP c++ program that sucessfully implements SSP - USF Group Project  
Implemented the naive algorithm, sketched the recursion tree, group members in charge of memoizing it
The goal of the subset sum problem is to find all the possible subsets which sum equals to a target. 

Example:  
Given the set: {1, 1, 1, 1, 1, 2, 2, 3} or  
{5, 2, 3} --> 5 ones, 2 twos, 1 three Target = 7

The parsing algorithm iterate like this:  

![image](https://user-images.githubusercontent.com/64340009/138242779-90e0438b-7358-4a6c-8c80-c309584b7da5.png)

Thus, this set will have 5 different different solutions.  
Since there are multiple calls of essentially the same recursive call you will need to memoize it to significantly decrease  
the time complexity


Note( Input format )  
7 3 5 2 1 --> The first parameter is the target sum, the second is the largest number in the set, the following are the contents of the set  
numbers in the set based on the index:  5 2 1
5 --> 5 ones  
2 --> 2 two
1 --> 1 three
