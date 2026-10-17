

// User function template for Java

class Solution {
    static String conRevstr(String S1, String S2) {
        // code here
        String res="";
        String temp=S1+S2;
        for(int i=temp.length()-1;i>=0;i--)
        {
            res +=temp.charAt(i);
        }
        return res;
    }
}