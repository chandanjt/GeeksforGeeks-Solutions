//User function Template for C++

class Solution{
    public:
       bool help(int* arr,int parent,int s,int e,bool flag)
    {
        //base case
        if(s>e)
        return 1;
        
        int mid=(s+e)/2;
        int node=arr[mid];
        
        if(flag)
        {
            if(node>=parent)
            return 0;
        }
        else
        {
            if(node<parent)
            return 0;
        }
        
        bool left=help(arr,node,s,mid-1,1);
        if(!left)
        return 0;
        
        bool right=help(arr,node,mid+1,e,0);
        
        return right;
    }
    int isRepresentingBST(int arr[], int N)
    {
        // code here
         int mid=(0+(N-1))/2;
        int node=arr[mid];
        bool a=help(arr,node,0,mid-1,1);
        if(!a)
        return 0;
        
        bool b=help(arr,node,mid+1,N-1,0);
        return b;
    }
};