class Solution{
    public:
    //arr1,arr2 : the arrays
    // n, m: size of arrays
    //Function to return a list containing the union of the two arrays. 
    vector<int> findUnion(int arr1[], int arr2[], int n, int m)
    {
        //Your code here
        //return vector with correct order of elements
        vector<int>res;
         unordered_set<int>st;
        for(int i=0;i<n;i++)
        {
            st.insert(arr1[i]);
        }
        for(int i=0;i<m;i++)
        {
            st.insert(arr2[i]);
        }
        int i;
        for(auto i:st)
        res.push_back(i);
        sort(res.begin(),res.end());
        return res;
    }
};