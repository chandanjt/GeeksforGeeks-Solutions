class Solution{
public: 
    long long int largestPrimeFactor(int N){
        // code here
          int i=2;
        while(i<N){
            if(N%i==0)
                N=N/i;
            else
                i=i+1;
        }
        return N;
    }
};