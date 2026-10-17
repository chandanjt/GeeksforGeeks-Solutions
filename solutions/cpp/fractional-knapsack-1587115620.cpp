//class implemented
/*
struct Item{
    int value;
    int weight;
};
*/


class Solution
{
    public:
    //Function to get the maximum total value in the knapsack.
    double fractionalKnapsack(int W, Item arr[], int n)
    {
       vector<pair<double, int>> v;
        for (int i = 0; i < n; i++) {
            double valuePerWeight = (double)(arr[i].value) / arr[i].weight;
            v.push_back({valuePerWeight, arr[i].weight});
        }
        sort(v.begin(), v.end());
    
        double totalValue = 0.0;
        for (int i = n - 1; i >= 0; i--) {
            if (W >= v[i].second) {
                totalValue += v[i].first * v[i].second;
                W -= v[i].second;
            } else {
                totalValue += v[i].first * W;
                break;
            }
        }

        return totalValue;
    }
        
};