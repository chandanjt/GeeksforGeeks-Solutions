//User function template for C++
class Solution{
public:
	// The main function that returns the arrangement with the largest value as
	// string.
	// The function accepts a vector of strings
	string printLargest(int n, vector<string> &arr) {
	    // code here
	    auto mycomparator=[](string &s1,string &s2){
	        return (s1+s2)>(s2+s1);
	    };
	    sort(begin(arr),end(arr),[](string &s1,string &s2){
	        return (s1+s2)>(s2+s1);
	    });
	     string res="";
	    for(auto &x: arr)
	    res+=x;
	    return res;
	}
};