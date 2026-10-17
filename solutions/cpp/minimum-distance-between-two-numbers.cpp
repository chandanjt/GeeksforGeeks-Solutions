
class Solution{
  public:
    int minDist(int a[], int n, int x, int y) {
        // code here
          int b1=-1,b2=-1;
        int res = INT_MAX;
        for(int i=0;i<n;i++){
            
            if(a[i]==x)
            {
                b1=i;
            }
            if(a[i]==y){
                b2 = i;
            }
            
            if(b1!=-1 && b2!=-1){
                res = min(res,abs(b1-b2));
            }
        }
        
        if(b1==-1 || b2==-1) return -1;//x or y not present in array
        else
        return res;
    }
};