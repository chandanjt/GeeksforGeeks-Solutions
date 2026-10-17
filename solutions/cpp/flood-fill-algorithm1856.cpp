class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        // Code here 
          int n=image.size();
       int m=image[0].size();
       queue<pair<int,int>>q;
       q.push({sr,sc});
          vector<vector<int>> visited(n, vector<int>(m, 0));
          visited[sr][sc]=1;
          int old_color=image[sr][sc];
          image[sr][sc]=newColor;
          int delrow[]={-1,0,+1,0};
          int delcol[]={+0,+1,0,-1};
          while(!q.empty()){
              int row=q.front().first;
              int col=q.front().second;
              q.pop();
              for(int i=0;i<4;i++){
                  int nrow=row+delrow[i];
                  int ncol=col+delcol[i];
                  if(nrow>=0&&ncol>=0&&nrow<n&&ncol<m
                  &&image[nrow][ncol]==old_color&&visited[nrow][ncol]==0){
                       visited[nrow][ncol] = 1;
                image[nrow][ncol] = newColor;
                q.push({nrow, ncol});
                  }
              }
          }
        return image; 
    }
};