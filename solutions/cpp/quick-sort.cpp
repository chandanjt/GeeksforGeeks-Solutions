class Solution
{
    public:
    //Function to sort an array using quick sort algorithm.
    void quickSort(int arr[], int low, int high)
    {
        // code here
        if(low>high)
        return;
        int pi=partition(arr,low,high);
        quickSort(arr,low,pi-1);
        quickSort(arr,pi+1,high);
    }
    
    public:
    int partition (int arr[], int low, int high)
    {
       // Your code here
       int pivot=arr[high];
       int pi=low-1;
       for(int i=low;i<high;i++)
       {
           if(arr[i]<pivot)
           {
               ++pi;
               swap(arr[i],arr[pi]);
               
           }
       }
       ++pi;
       swap(arr[high],arr[pi]);
       return pi;
    }
};