//User function Template for C++

class Solution{
	public:
  bool isprime(int n)
  {
      if(n==0||n==1)
      return 0;
      for(int i=2;i<=sqrt(n);i++)
      {
          if(n%i==0)
          return 0;
      }
      return 1;
  }
   	long long int prime_Sum(int n){
   	    // Code here
   	
   	 long long ans=0;
           vector<bool>v(n+1,true);
           for(int i=2;i*i<=n;i++){
               if(v[i]){
                   for(int j=2*i;j<=n;j=j+i){
                       v[j]=false;
                   }
               }
           }
           for(int i=2;i<=n;i++){
               if(v[i]){
                   ans=ans+i;
               }
           }
           return ans;

   	}    
};