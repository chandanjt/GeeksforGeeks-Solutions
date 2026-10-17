class Solution {
  public:
    void printSquare(int n) {
        // code here
        int cnt = 4;
        for(int i=0;i<2*n - 1;i++){
            for(int j = 0;j<2*n-1;j++){
                cout<<(n - min({i,j,(2*n-2)-j,(2*n-2)-i}))<<" ";
            }
            cout<<endl;
        }
    }
};