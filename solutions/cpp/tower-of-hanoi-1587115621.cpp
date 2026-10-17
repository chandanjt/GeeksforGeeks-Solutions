class Solution{
    public:
    // You need to complete this function

    // avoid space at the starting of the string in "move disk....."
    long long count=0;
   
   
    long long toh(int N, int from, int to, int aux) {
        // Your code here
        if(N>0)
        {
            //n-1 rod from from-->aux  with the help of to
       toh(N-1,from,aux,to);
        cout<<"move disk "<<N<<" from rod "<<from<<" to rod "<<to<<endl;
        count++;
        //n-1 rod from aux->to with the help of from
        toh(N-1,aux,to,from);
            
        }
        
        return count;
    }

};