class Solution {
	public:
		string FirstNonRepeating(string A){
		    // Code here
		    int n=A.length();
   string t="";
   if(n==0){
       return t;
   }
   unordered_map<int,int>m;
   queue<char>q;
   for(int i=0;i<n;i++){
       m[A[i]]++;
           if(q.empty()){
               t+=A[i];
           }else{
               char x=q.front();
               while(!q.empty() && m[q.front()]>1){
                   q.pop();
               }
               if(q.empty() && m[A[i]]==1){
                   t+=A[i];
               }else if(q.empty() && m[A[i]]>1){
                   t+="#";
               }
               else{
                   t+=q.front();
               }
           }
       q.push(A[i]);
   }
   return t;
		}

};