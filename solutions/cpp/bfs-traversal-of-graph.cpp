class Solution {
  public:
    // Function to return Breadth First Traversal of given graph.
    vector<int> bfsOfGraph(int V, vector<int> adj[]) {
        // Code here
        vector<int>res;
        vector<bool>visited(V+1,false);
        queue<int>q;
        visited[0]=true;
        q.push(0);
        res.push_back(0);
        while(!q.empty())
        {
            int src=q.front();
            for(int i=0;i<adj[src].size();i++)
            {
                if(visited[adj[src][i]]==false)
                {
                    visited[adj[src][i]]=true;
                    res.push_back(adj[src][i]);
                    q.push(adj[src][i]);
                }
            }
            q.pop();
        }
        return res;
        
    }
};