class Solution {
  public:
    // Function to find the number of islands.
     vector<vector<int>> visited;
    bool isValid(int i, int j, int n, int m, vector<vector<char>> &grid){
        return i >= 0 && i < n && j >= 0 && j < m && grid[i][j] == '1' && !visited[i][j];
    }
    void dft(int i, int j, int n, int m, vector<vector<char>> &grid){
        visited[i][j] = 1;
        for(int delrow = -1; delrow <= 1; delrow++){
            for(int delcol = -1; delcol <= 1; delcol++){
                int nrow = i + delrow;
                int ncol = j + delcol;
                if(isValid(nrow, ncol, n, m, grid))
                    dft(nrow, ncol, n, m, grid);
            }} }
    int numIslands(vector<vector<char>>& grid) {
        // Code here
          int n = grid.size();
        int m = grid[0].size();
        visited.resize(n, vector<int>(m, 0));
        int cnt = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(grid[i][j] == '1' && !visited[i][j]){
                    cnt++;
                    dft(i, j, n, m, grid);
                }} }
        return cnt;
    }
};