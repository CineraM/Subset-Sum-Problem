# Subset-Sum-Problem
DP c++ program that sucessfully implements SSP - USF Group Project  
Succesfully implemented the algorithm, were parters in charge of memoizing it
The goal of the subset sum problem is to find all the possible subsets which sum equals to a target. 

Example:  
Given the set: {1, 1, 1, 1, 1, 2, 2, 3} or  
{5, 2, 3} --> 5 ones, 2 twos, 1 three Target = 7

The parsing algorithm iterate like this:  

![image](https://user-images.githubusercontent.com/64340009/138242779-90e0438b-7358-4a6c-8c80-c309584b7da5.png)

Thus, this set will have 5 different different solutions.  
Since there are multiple calls of essentially the same recursive call you will need to memoize it to significantly decrease  
the time complexity
