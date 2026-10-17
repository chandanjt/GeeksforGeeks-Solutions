
class Solution
{
    //Function to find the smallest positive number missing from the array.
    static int missingNumber(int arr[], int size)
    {
        // Your code here
        int n=size;
        int i=0;
        while(i<n)
        {
            int el=arr[i];
            int indx=el-1;
            if(indx>=0 && indx<n)
            {
                if(arr[indx]!=el)
                {
                    int temp=arr[indx];
                    arr[indx]=arr[i];
                    arr[i]=temp;
                    continue;
                }
            }
            i++;
        }
        for(i=0;i<n;i++)
        {
            if(arr[i]!=i+1)
            return i+1;
        }
        return n+1;
    }
}