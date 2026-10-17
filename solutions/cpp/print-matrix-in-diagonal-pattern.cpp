/*You are required to complete this method */

class Solution{
  public:
    vector<int> matrixDiagonally(vector<vector<int>>&mat)
    {
         //Your code here
         int n=mat.size();
         vector<int>res;
         map<int,vector<int>>mp;
         for(int i=0;i<n;i++)
         {
             for(int j=0;j<n;j++)
             {
                 mp[i+j].push_back(mat[i][j]);
             }
         }
         bool flip=true;
         for(auto &it:mp)
         {
             if(flip)
             reverse(it.second.begin(),it.second.end());
             
             for(auto &itr:it.second)
             {
                 res.push_back(itr);
             }
             flip=!flip;
         }
         return res;
      
    }
};