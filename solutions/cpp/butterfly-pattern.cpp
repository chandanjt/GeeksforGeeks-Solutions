class Solution {
  public:
    void printTriangle(int n) {
        // code here
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=i;j++)
            {
                cout<<"*";
            }
            for(int k=1;k<=(n-i)*2;k++)
            cout<<" ";
            for(int j=1;j<=i;j++)
            {
                cout<<"*";
            }
            cout<<endl;
        }
        int s=0;
         for(int i=n-1;i>=1;i--)
        {
            for(int j=1;j<=i;j++)
            {
                cout<<"*";
            }
            s=s+2;
            for(int k=1;k<=s;k++)
            cout<<" ";
            for(int j=1;j<=i;j++)
            {
                cout<<"*";
            }
            cout<<endl;
        }
    }
};