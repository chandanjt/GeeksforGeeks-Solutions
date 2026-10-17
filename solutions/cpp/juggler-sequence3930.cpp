// User function Template for C++

class Solution{
public:
int res(int n)
{
    return n%2==0?pow(n,0.5):pow(n,1.5);
}
    vector<int> jugglerSequence(int N){
        // code here
        vector<int>ans;
        ans.push_back(N);
        while(N!=1)
        {
            N=res(N);
            ans.push_back(N);
        }
        return ans;
        
    }
};