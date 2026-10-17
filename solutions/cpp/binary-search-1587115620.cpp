// User function template for C++

class Solution {
  public:
    int binarysearch(int arr[], int n, int k) {
        int lb=0,ub,mid,loc=0;
        ub=n-1;
        mid=(lb+ub)/2;
        while(lb<=ub)
        {
            if(arr[mid]==k)
            {
                
          loc=mid;
            return loc;
                
            }
            else if(arr[mid]>k)
            ub=mid-1;
            else
            lb=mid+1;
            mid=(lb+ub)/2;
        }
        if(loc==0)
        return -1;
    }
};