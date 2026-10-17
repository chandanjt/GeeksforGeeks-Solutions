//Back-end complete function Template for C++

class Solution {
  public:
    int minCostClimbingStairs(vector<int>&cost ,int N) {
        //Write your code here
        for(int i=2;i<N;i++){
            cost[i] = cost[i] + min(cost[i-1],cost[i-2]);
        }
        return min(cost[N-1],cost[N-2]);
    }
};