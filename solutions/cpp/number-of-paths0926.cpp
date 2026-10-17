class Solution
{
    public:
   
const long long MOD = 1e9 + 7;

    // Fast exponentiation with mod
    long long power(long long x, long long y) {
        long long result = 1;
        x %= MOD;
        while (y > 0) {
            if (y & 1) {
                result = (result * x) % MOD;
            }
            y >>= 1; 
            x = (x * x) % MOD;
        }
        return result;
    }
    
    long long modInverse(long long n) {
        return power(n, MOD - 2);
    }
    
    long long  numberOfPaths(int M, int N)
    {
        // Code Here
        long long answer = 1;
        for (int i = 0; i < M - 1; i++) {
            answer = (answer * (N + i)) % MOD;
            answer = (answer * modInverse(i + 1)) % MOD;
        }
        return answer;
    }
};