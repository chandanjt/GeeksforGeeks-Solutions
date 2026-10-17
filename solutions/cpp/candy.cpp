class Solution {
  public:
    int minCandy(int n, vector<int> &rat) {
        // code here
           int sum=0;
        vector<int>ans(n);
        ans[0]=1;
        for(int i=1;i<n;i++){
            if(rat[i]>rat[i-1]) ans[i]=ans[i-1]+1;
            else if(rat[i]<=rat[i-1]) ans[i]=1;
            
        }
        for(int i=n-1;i>0;i--){
            if(rat[i]>rat[i-1]){
                if(ans[i]<=ans[i-1]) ans[i]=ans[i-1]+1;
                
            }
            else if(rat[i]<rat[i-1]){
                if(ans[i]>=ans[i-1]) ans[i-1]=ans[i]+1;
            }
            
        }
        for(int i=0;i<n;i++){
            sum+=ans[i];
        }
        return sum;
    }
};