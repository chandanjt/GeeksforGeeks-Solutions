## 01. Rotate Array by One

The problem can be found at the following link: [Question Link](https://www.geeksforgeeks.org/problems/cyclically-rotate-an-array-by-one2614/1)

### Problem Description

**Task:** Given an array arr[], rotate the array by one position in clockwise direction.Examples:Input: arr[] = [1, 2, 3, 4, 5]

#### Examples

##### Example 1

- **Output:**
```text
[3, 9, 8, 7, 6, 4, 2, 1]Explanation: After rotating clock-wise 3 comes in first position.
```

### Time and Auxiliary Space Complexity

- **Expected Time Complexity:** O(n)
- **Expected Auxiliary Space Complexity:** O(1)

### Accepted Solutions (1)

#### Solution 1 (JavaScript)

- **Submitted:** 2024-08-24 23:10:54
- **Status:** Correct
- **Marks:** 1

```javascript
// User function Template for javascript
class Solution {
    rotate(arr) {
        // code here
        let x= arr.pop();
        arr.unshift(x);
    }
}
```

*Generated on: 10/17/2026, 3:04:35 PM*