class Solution {
public:
    bool divisorGame(int N) {
        // code here
        if(N<=1)
        return false;
        for(int x=1;x<N;x++)
        {
            if(N%x==0)
           return !divisorGame(N-x);
        }
        return false;
    }
};