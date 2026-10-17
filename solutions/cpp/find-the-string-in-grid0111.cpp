class Solution {
public:
	vector<vector<int>>searchWord(vector<vector<char>>grid, string word){
	    // Code here
	    int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> v;
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[i].size(); j++)
            {
                if (grid[i][j] == word[0])
                {
                    int kl = 0;
                    for (int k = -1; k < 2; k++)
                    {                   //pair (k,l) check karega sabhi direction me eg (-1,0)== will check
                //in all upward direction like (i-1,j-0) ab to samajh gye honge 
                        for (int l = -1; l < 2; l++)
                        {
                            if (kl == 1) 
                                break;
                            if (k == 0 && l == 0)
                            {
                                continue;
                            }
                            else
                            {
                                int I = i, J = j, L;
                                for (L = 0; L < word.size(); L++)
                                {
                                    if (I >= 0 && J >= 0 && I < grid.size() && J < grid[i].size() && grid[I][J] == word[L])
                                    {
                                        I += k;
                                        J += l;
                                    }
                                    else
                                    {
                                        break;
                                    }
                                }
                                if (L == word.size())
                                {
                                    kl = 1;
                                    v.push_back({i, j});
                                }
                            }
                        }
                    }
                }
            }
        }
        sort(v.begin(), v.end());
        return v;
	}
};