class Solution{
  public:
    /*You are required to complete below function */
    string multiplyStrings(string s1, string s2) {
       //Your code here
    //   int n=stoi(s1);
    //   int m=stoi(s2);
    //   int ans=n*m;
    //   return to_string(ans);
          int q=0;
       int n=s1.size();
       if (s1[0]=='-'){
          
           q++;
       }
       int m=s2.size();
        if (s2[0]=='-'){
          
            q++;
        }
       vector<int>v(n+m,0);
       for (int i=n-1;i>=0;i--){
           if (s1[i]=='-')continue;
           for (int j=m-1;j>=0;j--){
               if (s2[j]=='-')continue;
               int k=(s1[i]-'0')*(s2[j]-'0')+v[i+j+1];
               
               
               v[i+j+1]=(k%10);
               v[i+j]+=(k/10);
           }
       }
       string s="";
       if (q==1)s+='-';
       bool flag=0;
       for (auto it:v){
          if (it!=0)flag=1;
          if (flag)
          s+=char(it+48);
   
        
       }
       
       return s;
    }

};