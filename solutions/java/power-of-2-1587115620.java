

//User function Template for Java

class Solution{
    
    // Function to check if given number n is a power of two.
    public static boolean isPowerofTwo(long n){
        
        // Your code here
           
         if(n==0)
         return false;
        int count=0;
      while(n!=0){
          
          if(n%2==1)count++;
          if(count>1)return false;
          n/=2;
          
          
          
      }
      return true;
    }
    
}