class Solution {
    private:
    void dfs(int node,vector<int>adj[],vector<bool>&visited,vector<int>& res)
    {
        visited[node]=true;
        res.push_back(node);
        for(auto it: adj[node])
        {
            if(!visited[it])
            {
                //visited[it]=true;
                dfs(it,adj,visited,res);
            }
        }
    }
  public:
    // Function to return a list containing the DFS traversal of the graph.
    vector<int> dfsOfGraph(int V, vector<int> adj[]) {
        // Code here
        vector<int>res;
         vector<bool>visited(V+1,false);
        dfs(0,adj,visited,res);
        return res;
    }
};