//User function template for C++
class Solution{
public:
	string removeDuplicates(string str) {
	    // code here
	   unordered_set<char>st;
	    string res="";
	    for(int i=0;i<str.length();i++)
	    {
	        if(st.find(str[i])==st.end())
	        {
	            res+=str[i];
	        st.insert(str[i]);
	        }
	    }
	   
	    return res;
	}
};