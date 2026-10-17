// User function Template for C++

class Solution{
public:
    string findLargest(int N, int S){
        // code here
          string v;
        
        if((S>9*N)  || (S==0)&&(N>1)) return "-1";
        
        for(int i=0;i<N;i++){
            
            if(S<9){
                v.push_back(S+'0');
                S=0;
            }
            else{
                v.push_back('9');
                S -=9;
            }
        }
        return v;
    }
};