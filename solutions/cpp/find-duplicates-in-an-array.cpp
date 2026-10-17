class Solution{
  public:
    vector<int> duplicates(int arr[], int n) {
        // code here
       sort(arr,arr+n);
        vector<int>ans;
        unordered_map<int,int>mp;
        for(int i=0;i<n;i++)
        {
            mp[arr[i]]++;
        if(mp[arr[i]]==2)
        ans.push_back(arr[i]);
            
        }
        if(ans.size()==0)
        ans.push_back(-1);
        return ans;
    }
};