## 01. Quadratic Equation Roots

The problem can be found at the following link: [Question Link](https://www.geeksforgeeks.org/problems/quadratic-equation-roots/1)

### Problem Description

**Task:** Given a quadratic equation ax^2 + bx + c = 0, find its roots. If the equation has real roots, then return floor value of each root in decreasing order, If the roots are imaginary return -1, the driver code will print Imaginary.Examples:Input: a = 1, b = -2, c = 1

#### Examples

##### Example 1

- **Output:**
```text
[4, 3]
```
- **Explanation:** Roots of equation x^2 - 7x + 12 are 4 and 3.

### Time and Auxiliary Space Complexity

- **Expected Time Complexity:** O(1)
- **Expected Auxiliary Space Complexity:** O(1)

### Accepted Solutions (1)

#### Solution 1 (Java)

- **Submitted:** 2023-07-15 16:24:51
- **Status:** Correct
- **Marks:** 1

```java
class Solution
{
    public double[]  FindRoots(int A, int B, int C)
    {
        // code here
         double r=B*B-4*A*C;
        if(r<0)
            return new double[]{-1.0};// root is not real
        r=Math.sqrt(r);
        double x=(-B+r)/(2*A);
        double y=(-B-r)/(2*A);
        if(x>y){
            double temp=x;
            x=y;
            y=temp;
        }
        return new double[]{x,y};
    }
}
```

*Generated on: 10/17/2026, 2:31:55 PM*