

//return the address of the string
char* reverse(char *S, int len)
{
    //code here
    stack<char>st;
    for(int i=0;i<len;i++)
    {
        st.push(S[i]);
    }
    char res[len];
    int i=0;
    for(int i=0;i<len;i++)
    {
        S[i]=st.top();
        st.pop();
    }
    
    return S;
}