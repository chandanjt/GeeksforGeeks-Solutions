class Solution
{
public:    
    
    int transitionPoint(int arr[], int n) {
        // code here
         int low = 0;
        int high = n-1;
        while(low < high)
        {
            int mid = (low + high) >> 1;
            if(arr[mid] == 1)
            {
                high = mid;
            }
            else 
            {
                low = mid+1;
            }
        }
        if(arr[low] == 0)
        {
            return -1;
        }
        return low;
    }
};