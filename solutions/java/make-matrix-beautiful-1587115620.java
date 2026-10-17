


class Solution {
    public static int findMinOperation(int N, int[][] matrix) {
      long row[] = new long[N];
        long col[] = new long[N];
        long sum = 0;
        long tar = 0;
        for(int i = 0 ; i < N ; i++)
        for(int j = 0 ; j < N ; j++){
            row[i]+=matrix[i][j];
            col[j]+=matrix[i][j];
            sum+=matrix[i][j];
            tar=Math.max(tar,row[i]);
            tar=Math.max(tar,col[j]);
        }
        return (int)(tar*N - sum);
    }
}
        