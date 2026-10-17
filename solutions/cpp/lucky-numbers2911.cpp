//User-function template for C++

// Complete the function
// n: Input n
// Return True if the given number is a lucky number else return False

class Solution{
public:
    bool isLucky(int n) {
        // code here
        int count=2;
        while(true){
            if(n%count == 0){
                return false;
            }
            if(count>n){
                return true;
            }
            n=(n-(n/count));
            count++;
        }
    }
};