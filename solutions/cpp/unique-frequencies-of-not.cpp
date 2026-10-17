//User function Template for C++
class Solution
{
    public:
    bool isFrequencyUnique(int n, int arr[])
    {
        unordered_map<int,int>freq;
           for(int i=0;i<n;i++)
            freq[arr[i]]++;
        unordered_set<int>s;
        for(auto x:freq)
        {
            s.insert(x.second);
        }
        return freq.size()==s.size();
    }
};