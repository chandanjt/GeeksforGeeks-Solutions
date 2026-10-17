// User function template in C++

class Solution {
  public:
    // Function to return the position of the first repeating element.
    int firstRepeated(int arr[], int n) {
        // code here
        unordered_map<int,int>umap;
        for(int i=0;i<n;i++)
        {
            int key=arr[i];
            umap[key]++;
        }
       int key;
        for(int i=0;i<n;i++)
        {
             key=arr[i];
            auto temp=umap.find(key);
            if(temp->second>1)
           return i+1;
           
        }
        
        return -1;
        
    }
};