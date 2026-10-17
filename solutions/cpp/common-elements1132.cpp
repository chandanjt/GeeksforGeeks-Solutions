class Solution
{
    public:    
       vector <int> commonElements (int A[], int B[], int C[], int n1, int n2, int n3)
        {
            //code here.
            vector<int>ans;
                set<int>st,st2,st3;
            unordered_map<int,int>mp;
            for(int i=0;i<n1;i++){
                st.insert(A[i]);
               
            }
            
            for(int i=0;i<n2;i++){
                st2.insert(B[i]);
                
            }
            
            for(int i=0;i<n3;i++){
                st3.insert(C[i]);
               
            }
            for(auto it:st){
                mp[it]++;
            }
            
             for(auto it:st2){
                mp[it]++;
            }
              
              
               for(auto it:st3){
                mp[it]++;
            }
            for(auto it:mp){
                if(it.second>=3){
                    ans.push_back(it.first);
                }
            }
            
            sort(ans.begin(),ans.end());
            return ans;
        }

};