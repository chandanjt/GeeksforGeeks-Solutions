//User function Template for C++

class Solution{
  public:
    vector<vector<string> > Anagrams(vector<string>& string_list) {
        //code here
         vector<vector<string>> ans;
         unordered_map<string,vector<string>> umap;
         for(auto x:string_list)
         {
             string temp=x;
             sort(x.begin(),x.end());
             umap[x].push_back(temp);
         }
         for(auto x:umap)
         {
             vector<string>temp=x.second;
             ans.push_back(temp);
         }
         return ans;
    }
};