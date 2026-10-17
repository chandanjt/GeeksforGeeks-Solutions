//User function template for C++
class Solution{
public:
	// Function to check if the
	// Pythagorean triplet exists or not
	bool checkTriplet(int a[], int n) {
	    // code here
	          for(int i=0;i<n;i++){
            a[i]=a[i]*a[i];
            }
            
            unordered_set<int>st(a,a+n);
            for(int i=0;i<n;i++){
                for(int j=i+1;j<n;j++){
                    if(st.find(a[i]+a[j])!=st.end())return true;
                }
            }
            return false;
	}
};