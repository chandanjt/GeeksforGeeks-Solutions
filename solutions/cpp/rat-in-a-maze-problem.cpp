// User function template for C++

class Solution{
    public:
    vector<string>res;
    void solve(vector<vector<int>> &m,int i,int j,int n,string path)
    {
        if(i<0||j<0||i>=n||j>=n||m[i][j]==0)
        return;
        if(i==n-1 && j==n-1&& m[i][j]!=0)
        {
            res.push_back(path);
            return;
        }
        m[i][j]=0;
        //left
        path.push_back('L');
        solve(m,i,j-1,n,path);
        path.pop_back();
        
        //right
        path.push_back('R');
        solve(m,i,j+1,n,path);
        path.pop_back();
        
        //UP
        path.push_back('U');
        solve(m,i-1,j,n,path);
        path.pop_back();
        
        //down
        path.push_back('D');
        solve(m,i+1,j,n,path);
        path.pop_back();
        
        m[i][j]=1;
    }
    vector<string> findPath(vector<vector<int>> &m, int n) {
        // Your code goes here
        solve(m,0,0,n,"");
        return res;
    }
};

    