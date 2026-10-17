class Solution {
  public:
    void printTriangle(int n) {
        // code here
      for(int i = 1; i <= n; i++)
        {
            // for spaces
            for(int j = 1; j <= (n-i); j++)
                cout << " ";
                
            // for letters
            char c = 'A';
            for(int k = 1; k <= (2*i - 1); k++)
            {
                cout << c;
                if(k >= i) c--;
                else c++;
            }
            cout << endl;
        }
    }
};