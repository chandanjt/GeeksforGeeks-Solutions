
class Solution
{
    public:
    int minNumber(int arr[],int N)
    {
         int result=0;
       int data=0;
       for(int i=0;i<N;i++)
        data+=arr[i];
        if(data==1) return 1;
       
       for(int i=2;i<=(data+result)/2;i++){
         if((data+result)%i==0){
             result++;
             i=2;
          }
        }
        return result;
    }
};