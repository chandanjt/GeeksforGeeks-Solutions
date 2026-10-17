class Solution{
public:
    int evenlyDivides(int N){
        //code here
         int number=N;
        int count=0;
        while(number>0){
            int lastdigit=number%10;
            number/=10;
            if(lastdigit!=0 && N%lastdigit==0){
                count++;
            }
        
        }
        return count;
    }
};