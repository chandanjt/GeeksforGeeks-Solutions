//User function Template for C++

class Solution
{
  public:
    vector<int> findOrder(int n, int m, vector<vector<int>> &prerequisites) 
    {
        //code here
         vector<int> indegree(n, 0);
        vector<vector<int>> adj(n, vector<int>());
    
        for (auto& pre : prerequisites) {
            int u = pre[1];
            int v = pre[0];
            indegree[v]++;
            adj[u].push_back(v);
        }
        
        queue<int>q;
        for(int i=0; i<n; i++){
            if(indegree[i]==0) q.push(i);
        }
        
        vector<int>ans;
        while(!q.empty()){
            int node=q.front();
            q.pop();
            ans.push_back(node);
            
            for(auto it:adj[node]){
                indegree[it]--;
                if(indegree[it]==0) q.push(it);
            }
        }
        
        if(ans.size()!=n) return {};
        else return ans;
    }
};