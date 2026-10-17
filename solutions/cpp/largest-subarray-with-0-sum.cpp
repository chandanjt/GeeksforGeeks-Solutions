/*You are required to complete this function*/

class Solution {
  public:
    int maxLen(vector<int>& arr, int n) {
        unordered_map<long long, int> mp;
        long long sum=0;
        int maxi=0;
               
        for (int i=0; i<n; i++){
            sum += arr[i];
            if(sum == 0){  
                mp[sum] = i;
                maxi = max(maxi, i+1);
        
            }
            else if(mp.find(sum) == mp.end()){ 
                mp[sum] = i;
            }
            else if(mp.find(sum) != mp.end()){ 
                maxi = max(maxi, i - mp[sum]);
        
            }
        }
        return maxi;
    }
};