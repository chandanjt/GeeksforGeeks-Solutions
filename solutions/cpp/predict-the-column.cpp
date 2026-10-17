//User function Template for C++

class Solution{
    public:
    /*Function to count zeros in each column
    * N : Number of rows and columns in array
    M is the matrix that is globally declared
    */
    int columnWithMaxZeros(vector<vector<int>>arr,int N){
        
        // Your code here
        
          int ans = -1;
        int max = -1;
        bool p = false;
        
        for(int i=0;i<N;i++)
        {
            int count = 0;
            for(int j=0;j<N;j++)
            {
                if(arr[j][i]==0)
                {
                    count++;
                    p = true;
                }
            }
            if(count>max)
            {
                max = count;
                ans = i;
            }
        }
        
        if(p) return ans;
        
        return -1;
    }
};