class Solution
{
    public:
    void sort012(int a[], int n)
    {
       int count0=0,count1=0,count2=0,i;
       for(i=0;i<n;i++)
       {
           if(a[i]==0)
           count0++;
           if(a[i]==1)
           count1++;
           if(a[i]==2)
           count2++;
       }
       for(i=0;i<count0;i++)
       a[i]=0;
        for(i=count0;i<(count0+count1);i++)
       a[i]=1;
        for(i=count0+count1;i<n;i++)
       a[i]=2;
    }
    
};