// User function template for C++

class Solution {
  public:
  
    long long sumOfSeries(long long N) {
        // code here
        if(N == 1){
            return 1; 
        }
        long prev = sumOfSeries(N-1);
        long now = (N*N*N) + prev;
        return now;
    }
};