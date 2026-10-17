//User function Template for C++

class Solution {
    private:
    void dfs(int node,vector<int>adj[],vector<bool>&visited)
    {
        visited[node]=true;
        for(auto it:adj[node])
        {
            if(!visited[it])
            {
                dfs(it,adj,visited);
            }
        }
    }
  public:
    int numProvinces(vector<vector<int>> adj, int V) {
        // code here
        vector<int>adjlist[V];
        for(int i=0;i<V;i++)
        {
            for(int j=0;j<V;j++)
            {
                if(adj[i][j]==1)
                {
                    adjlist[i].push_back(j);
                     adjlist[j].push_back(i);
                }
            }
        }
        vector<bool>visited(V+1,false);
        int count=0;
        for(int i=0;i<V;i++)
        {
            if(!visited[i])
            {
                count++;
                dfs(i,adjlist,visited);
            }
        }
        return count;
    }
};