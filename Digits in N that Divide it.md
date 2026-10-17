## 01. Digits in N that Divide it

The problem can be found at the following link: [Question Link](https://www.geeksforgeeks.org/problems/count-digits-in-given-number-n-which-divide-n3331/1)

### Problem Description

**Task:** Given a non-negative integer s represented as a string, count the number of digits in s that divide the number represented by s.A digit is considered valid only if it is non-zero and the number represented by s is divisible by that digit.If a digit appears multiple times in s, each occurrence should be counted separately.Examples:Input: s = "35"

#### Examples

##### Example 1

- **Output:**
```text
7
```
- **Explanation:** Every digit in "1122324" divides 1122324. So the answer is 7.

### Time and Auxiliary Space Complexity

- **Expected Time Complexity:** O(n)
- **Expected Auxiliary Space Complexity:** O(1)

### Accepted Solutions (1)

#### Solution 1 (C++)

- **Submitted:** 2024-08-24 23:14:31
- **Status:** Correct
- **Marks:** 2

```cpp
class Solution{
public:
    int evenlyDivides(int N){
        //code here
         int number=N;
        int count=0;
        while(number>0){
            int lastdigit=number%10;
            number/=10;
            if(lastdigit!=0 && N%lastdigit==0){
                count++;
            }
        
        }
        return count;
    }
};
```

*Generated on: 10/17/2026, 2:37:27 PM*