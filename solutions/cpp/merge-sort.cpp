class Solution
{
    public:
    void merge(int arr[], int l, int m, int r)
    {
         // Your code here
         int temp[r+1];
         int i=l,j=m+1,k=0;
         while(i<=m && j<=r)
         {
             if(arr[i]<arr[j])
             temp[k++]=arr[i++];
             else
             temp[k++]=arr[j++];
         }
         while(i<=m)
         temp[k++]=arr[i++];
         while(j<=r)
         temp[k++]=arr[j++];
         
         for(int i=r;i>=l;i--)
         arr[i]=temp[--k];
         
         
    }
    public:
    void mergeSort(int arr[], int l, int r)
    {
        int mid;
        if(l<r)
        {
            mid=(l+r)/2;
            mergeSort(arr,l,mid);
            mergeSort(arr,mid+1,r);
            merge(arr,l,mid,r);
        }
    }
};