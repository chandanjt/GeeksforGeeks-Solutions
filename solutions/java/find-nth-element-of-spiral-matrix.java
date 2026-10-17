

class Solution
{
    /*You are required to complete this method*/
    int findK(int A[][], int n, int m, int k)
    {
		
	 int rowStart = 0;
int rowEnd = n-1;
int colStart = 0;
int colEnd = m-1;
int count=0;

while(rowStart <= rowEnd && colStart <= colEnd) {

for(int col=colStart; col<=colEnd; col++) {

count++;
if(count==k)
return A[rowStart][col];
}
rowStart++;

for(int row=rowStart; row<=rowEnd; row++) {

count++;
if(count==k)
return A[row][colEnd];
}
colEnd--;

for(int col=colEnd; col>=colStart; col--) {

count++;
if(count==k)
return A[rowEnd][col];
}
rowEnd--;

for(int row=rowEnd; row>=rowStart; row--) {

count++;
if(count==k)
return A[row][colStart];
}
colStart++;


}
return -1;
    }
}