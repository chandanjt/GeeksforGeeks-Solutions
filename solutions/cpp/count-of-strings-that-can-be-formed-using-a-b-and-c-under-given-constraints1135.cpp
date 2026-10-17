

long long fact(long long int k){
    long long p=1;
    
    for(int i=1;i<=k;i++)p*=i;
    
    return p;
}
long long int countStr(long long int n){
    //complete the function here
      long long ans=0;
    
    // with only b;
    
    ans+=n;
    // with only c;
    ans+=n;
    
    // with 2 c
    ans+=(n*(n-1))/2;
    
    // with b and c;
    ans+=(n*(n-1));
    // with 2 c  and 1 b;
    
    ans+=(n*(n-1)*(n-2))/2;
    ans+=1;
    
    
    return ans;
}