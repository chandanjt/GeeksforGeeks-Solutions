//User function teamplate for C++

class Solution{
  public:
    vector<int> printClosest(int arr[], int brr[], int n, int m, int x) {
        //code here
         vector<int> ans(2,0);
        int i=0,j=m-1;
        int mini_diff=INT_MAX;
        while(i<n && j>=0){
            int sum=arr[i]+brr[j];
            if(mini_diff>(abs(x-sum))){
                mini_diff=abs(sum-x);
                ans[0]=arr[i];
                ans[1]=brr[j];
            }
            if(sum>x)
            j--;
            else
            i++;
        }
        return ans;
    }
};