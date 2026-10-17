class Solution {
  public:
    void printTriangle(int n) {
        // code here
       int  count=1;
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=i;j++)
            {
                cout<<count<<" ";
                count++;
            }
            cout<<endl;
        }
        
    }
};