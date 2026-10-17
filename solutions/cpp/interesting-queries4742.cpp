
#define MAXN 100005
#define BLOCK 318
int cnt[MAXN],a[MAXN],ans[MAXN],answer=0;
struct query
{
    int L,R,i;
};
query q[MAXN];
class Solution {
public:
	static bool acompare(query x,query y)
	{
	    if(x.L/BLOCK!=y.L/BLOCK)
	    {
	        return x.L/BLOCK<y.L/BLOCK;
	    }
	    return x.R<y.R;
	}
	void add(int p,int k)
	{
	    cnt[a[p]]++;
	    if(cnt[a[p]]==k)
	    {
	        answer++;
	    }
	}
    void subtract(int p,int k)
    {
        cnt[a[p]]--;
        if(cnt[a[p]]==k-1)
        {
            answer--;
        }
    }
	vector<int>solveQueries(vector<int>nums, vector<vector<int>>Queries, int k){
		int n = nums.size();
		int m = Queries.size();
		memset(a, 0, sizeof(a));
		memset(cnt, 0, sizeof(cnt));
		answer = 0;
        for(int i = 0; i < n; i++)
        {
            a[i] = nums[i];
        }
        for(int i = 0; i < m; i++)
        {
            q[i].L = Queries[i][0];
            q[i].R = Queries[i][1];
            q[i].L--;
            q[i].R--;
            q[i].i=i;
        }
        sort(q,q+m,acompare);
        int c_l=0,c_r=0,l,r;
        vector<int>ans(m);
        for(int i = 0; i < m; i++)
        {
            l=q[i].L;r=q[i].R;
            while(c_l<l)
            {
                subtract(c_l,k);
                c_l++;
            }
            while(c_l>l)
            {
                add(c_l-1,k);
                c_l--;
            }
            while(c_r<=r)
            {
                add(c_r,k);
                c_r++;
            }
            while(c_r>r+1)
            {
                subtract(c_r-1,k);
                c_r--;
            }
            ans[q[i].i]=answer;
        }
        

	   /*
	    for(int i=0;i<Queries.size();i++)
	    {
	        int l=Queries[i][0];
	        int r=Queries[i][1];
	        int count=0;
	        unordered_map<int,int>m;
	        for(int j=l-1;j<r;j++)
	        {
	            m[nums[j]]++;
	        }
	        for(auto i:m)
	        {
	            if(i.second>=k)
	            {
	                count +=1;
	            }
	        }
	        ans.push_back(count);
	    }*/
	    return ans;
	}
};