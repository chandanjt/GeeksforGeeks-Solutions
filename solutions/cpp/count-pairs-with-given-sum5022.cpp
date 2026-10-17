//User function template for C++

class Solution{   
public:
    int getPairsCount(int arr[], int n, int k) {
        // code here
        
    unordered_map<int, int> freq;
        int count = 0;

        for (int i = 0; i < n; i++) {
            int complement = k- arr[i];
            count += freq[complement];  

            freq[arr[i]]++;  
        }
    return count;
    }
};