
class Solution
{
    public:
    //Function to check if brackets are balanced or not.
         bool isMatch(char a, char b){
        if(a == '(' && b == ')'){
            return true;
        }
        if(a == '{' && b == '}'){
            return true;
        }
        if(a == '[' && b == ']'){
            return true;
        }
        
        return false;
    }
    bool ispar(string x)
    {
        stack<char>st;
        for(int i=0;i<x.length();i++)
        {
            if(x[i]=='{'||x[i]=='['||x[i]=='(')
            st.push(x[i]);
            else if(st.empty()){
                return false;
            }
            else if(isMatch(st.top(), x[i]) == false){
                return false;
            }
            else{
                st.pop();
            }
        }
        if(st.empty())
        return true;
        return false;
    }

};