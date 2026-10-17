class Solution{
  public:
  
    //Function to return the name of candidate that received maximum votes.
    vector<string> winner(string arr[],int n)
    {
        // Your code here
        // Return the string containing the name and an integer
        // representing the number of votes the winning candidate got
        unordered_map<string,int>umap;
        for(int i=0;i<n;i++)
        {
            string key=arr[i];
            umap[key]++;
        }
        string name="";
        int max=0;
        for(auto itr=umap.begin();itr!=umap.end();itr++)
        {
            string key=itr->first;
            int val=itr->second;
            if(val>max)
           { max=val;
           name=key;
           }
           else if(val==max)
           {
               if(key<name)
               name=key;
           }
        }
        vector<string>res;
        res.push_back(name);
        string t=to_string(max);
        res.push_back(t);
        return res;
    }
};