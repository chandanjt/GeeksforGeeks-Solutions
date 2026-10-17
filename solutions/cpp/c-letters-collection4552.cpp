// User function Template for C++

class Solution{
public:
bool s(int a, int b,int n, int m){

    return (a>=0 && a<n && b>=0 && b<m);

}
    vector<int> matrixSum(int n, int m, vector<vector<int>> mat, int q, vector<int> queries[])
    {
        // code here
         vector <int> ans;

        int dr1[]={-1, -1, -1, 0, 0, 1, 1, 1};

        int dc1[]={-1, 0, 1, -1, 1, -1, 0, 1};

        int dr2[] = {-2, -2, -2, -2, -2, -1, 0, 1, 2, 2, 2, 2, 2, 1, 0, -1} ;

        int dc2[] = {-2, -1, 0, 1, 2, 2, 2, 2, 2, 1, 0, -1, -2, -2, -2, -2} ;

       // cout<<sizeof(dr2)/sizeof(dr2[0]);

        for(int j=0;j<q;j++) {

            int hop=queries [j][0];

            int i=queries [j][1];

            int k=queries [j][2];

            int sum=0;

            if(hop==1){

                for(int r=0;r<8;r++){

                    int x=dr1[r];

                    int y=dc1[r];

                   if (s(i+x,k+y,n, m)){

                       //cout<<mat[i+x][k+y];

                    sum+=mat[i+x][k+y];

                   } 

                }

            }

            else if(hop==2){

                for(int r=0;r<16;r++){

                    int x=dr2[r];

                    int y=dc2[r];

                   // cout<<i+x<<k+y<<endl;

                       //cout<<mat[i-x][k-y]<<endl;

                   if (s(i+x,k+y,n, m)){

                       

                    sum+=mat[i+x][k+y];

                   } 

                }

            }

            else{

                sum+=-1;

            }

            //cout<<hop;

            ans.push_back(sum);

        }

        return ans;
    }
};