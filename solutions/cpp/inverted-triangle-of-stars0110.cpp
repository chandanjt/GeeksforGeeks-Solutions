class Solution{
public:
	
	void printTriangle(int n) {
	    // code here
	      for(int i=1; i<=n; i++){
           for(int j=1; j<i; j++){
               cout<<" ";
           }
           for(int k=1; k<=2*n-2*i+1; k++){
               cout<<"*";
           }
           cout<<endl;
	      }
	}
};