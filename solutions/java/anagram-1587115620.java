

class Solution
{    
    //Function is to check whether two strings are anagram of each other or not.
    public static boolean isAnagram(String a,String b)
    {
        a=a.toLowerCase();
        b=b.toLowerCase();
        
        if(a.length()!=b.length())
        return false;
        else
        {
            char[] str1ary=a.toCharArray();
            char[] str2ary=b.toCharArray();
            Arrays.sort(str1ary);
            Arrays.sort(str2ary);
            if(Arrays.equals(str1ary,str2ary))
{
    return true;

}
else{
   return false;
        }
        }
        
    }
}