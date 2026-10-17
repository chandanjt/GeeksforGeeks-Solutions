// #define ll long long
class Solution{
public:
int mod =1e9+7 ;
    vector<long long> nthRowOfPascalTriangle(int n) {
        // code here
          vector<long long> ans; 
        if(n==1)return {1} ;
        if(n==2)return {1,1} ;
         ans = {1,1} ;
        int x= 3; 
        while((x++)<=n)
       {
           vector<long long > a ;
           a.push_back(1); 
           for(int i=0 ; i<ans.size()-1; i++ )
        {
        a.push_back((ans[i]+ans[i+1])%mod) ;
        }
           a.push_back(1) ;
           ans= a; 
       }
       return ans; 
    }
};