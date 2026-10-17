
class Solution
{
	public:
	//Function to find the level of node X.
	int nodeLevel(int v, vector<int> adj[], int x) 
	{
	    // code here
	    queue<int>q;
        vector<int>vis(v,0);
        q.push(0);
         vis[0]=1;
        int k=0;
        while(!q.empty()){
            int size=q.size();
            
             while(size--){
                 int item=q.front();
                 if(item==x)return k;
                 q.pop();
                 for(auto it:adj[item]){
                     if(vis[it]==0){
                     q.push(it);
                       vis[it]=1;
                     }
                 }
             }
             k++;
           
        }
        return -1;
	}
};