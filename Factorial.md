## 01. Factorial

The problem can be found at the following link: [Question Link](https://www.geeksforgeeks.org/problems/factorial5739/1)

### Problem Description

**Task:** Given a positive integer, n. Find the factorial of n.Examples :Input: n = 5

#### Examples

##### Example 1

- **Output:**
```text
24
```
- **Explanation:** 1 x 2 x 3 x 4 = 24

### Time and Auxiliary Space Complexity

- **Expected Time Complexity:** O(n)
- **Expected Auxiliary Space Complexity:** O(1)

### Accepted Solutions (1)

#### Solution 1 (C++)

- **Submitted:** 2023-07-15 11:10:45
- **Status:** Correct
- **Marks:** 1

```cpp
class Solution{
public:
    long long int factorial(int N){
        //code here
        if(N<=1)
        return 1;
        
        return N*factorial(N-1);
    }
};
```

*Generated on: 10/17/2026, 2:29:29 PM*