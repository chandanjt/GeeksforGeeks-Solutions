// User function Template for C++

class Solution{
public:
void dfs(int row, int col ,vector<vector<char>> &grid, int n, int m, char symbol)
    {
        if(row<0 || row>=n || col<0 || col>=m || grid[row][col]!='O') return;
        
        grid[row][col] = symbol;
        dfs(row+1,col,grid,n,m,symbol);
        dfs(row,col+1,grid,n,m,symbol);
        dfs(row-1,col,grid,n,m,symbol);
        dfs(row,col-1,grid,n,m,symbol);
    }
    vector<vector<char>> fill(int n, int m, vector<vector<char>> mat)
    {
        // code here
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(i==0 || i==n-1 || j==0 || j==m-1)
                {
                    if(mat[i][j]=='O'){
                        dfs(i,j,mat,n,m,'$');
                    }
                }
            }
        }
        
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(mat[i][j]=='O')
                {
                    dfs(i,j,mat,n,m,'X');
                }
            }
        }
        
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(mat[i][j] == '$')
                    mat[i][j] = 'O';
            }
        }
        return mat;
    }
};