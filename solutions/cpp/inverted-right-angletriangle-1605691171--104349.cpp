class Solution {
  public:
    void printTriangle(int n) {
        // code here
        for(int i=n;i>=1;i--)
        {
            char temp='A';
            for(int j=1;j<=i;j++)
            {
                cout<<temp;
                temp++;
            }
            cout<<endl;
        }
    
    }
};