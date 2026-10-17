
class Solution {
public:
    int Count(vector<vector<int> >& matrix) {
        int n= matrix.size();
        int m= matrix[0].size();
        int ans=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
               
                if(matrix[i][j]==1){
                     int count=0;
                    if(i+1<n && matrix[i+1][j]==0)
                        count++;
                    if(i-1>=0 && matrix[i-1][j]==0 )
                        count++;
                    
                    if(j+1<m && matrix[i][j+1]==0)
                        count++;
                    
                    if(j-1>=0 && matrix[i][j-1]==0)
                        count++;
                    
                    if((i+1<n && j+1<m) && matrix[i+1][j+1]==0)
                        count++;
        
                    if((i-1>=0 && j-1>=0) && matrix[i-1][j-1]==0)
                        count++;
                    
                    if((i+1<n && j-1>=0) && matrix[i+1][j-1]==0)
                        count++;
                    
                    if((i-1>=0 && j+1<m) && matrix[i-1][j+1]==0)
                        count++;
                    
                      if(count % 2==0 && count!=0)
                       ans++;
                         
                }
              
            }
        }
        return ans;
    }
};