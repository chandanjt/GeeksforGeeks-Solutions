


class Solution
{
    public double[]  FindRoots(int A, int B, int C)
    {
        // code here
         double r=B*B-4*A*C;
        if(r<0)
            return new double[]{-1.0};// root is not real
        r=Math.sqrt(r);
        double x=(-B+r)/(2*A);
        double y=(-B-r)/(2*A);
        if(x>y){
            double temp=x;
            x=y;
            y=temp;
        }
        return new double[]{x,y};
    }
}