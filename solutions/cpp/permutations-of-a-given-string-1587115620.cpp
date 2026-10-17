class Solution{
    public:
    //Complete this function
    void solve(string st, vector<string> &ans, int index){
        if(index >= st.length()){
            ans.push_back(st);
            return;
        }
        
        for(int i=index; i<st.length(); i++){
            swap(st[index], st[i]);
            solve(st, ans, index+1);
            
            swap(st[index], st[i]);
        }
    }
    vector<string> permutation(string S)
    {
        //Your code here
          vector<string> ans;
        string st = S;
        
        solve(S, ans, 0);
        sort(ans.begin(), ans.end());
        return ans;
    }
};