//User function Template for C++

class Solution
{
    public:
    //Function to find the first position with different bits.
    int posOfRightMostDiffBit(int m, int n)
    {
        int count  = 0;
        while(m>0 || n>0){
            int temp1 = m%2;
            int temp2 = n%2;
            count++;
            
            int flag = temp1^temp2;
            if(flag == 1)
            return count;
            
            m /= 2;
            n /= 2;
            
        }
        return -1;
    }
};