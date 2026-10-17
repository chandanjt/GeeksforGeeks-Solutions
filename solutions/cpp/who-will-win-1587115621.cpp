class Solution{
    public:
    // Function to find element in sorted array
    // arr: input array
    // N: size of array
    // K: element to be searche
    int searchInSorted(int arr[], int N, int K) 
    { 
      
       int lb=0;
       int ub=N-1;
       while(lb<=ub)
       {
           int mid=(ub+lb)/2;
           if(arr[mid]==K)
           return 1;
           if(arr[mid]>K)
           ub=mid-1;
           else
           lb=mid+1;
       }
       return -1;
    }
};