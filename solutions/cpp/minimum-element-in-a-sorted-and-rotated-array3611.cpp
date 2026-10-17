class Solution{
public:
    int findMin(int arr[], int n){
        //complete the function here
        int l=0,r=n-1;
        int res=arr[0];
        for(int i=l;i<=r;i++)
        {
            int temp=min(arr[i],arr[r]);
            res=min(res,temp);
            r--;
        }
        return res;
    }
};