
class Solution
{
  public:
    int countPairs(int arr1[], int arr2[],  int m, int n, int x) 
    { 
        //code here.
        int i=0,j=n-1,count=0;
        while(i<m && j>=0)
        {
            int sum = (arr1[i]+arr2[j]);
            
            if(sum == x)
            {
                count ++;
                i++;
                j--;
            }
            else if(sum<x)
            {
                i++;
            }
            else
            {
                j--;
            }
        }
        return count;
    } 
};