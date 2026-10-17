// User function Template for C++

class Solution {
  public:
  
int countX(int start_range, int end_range, int target_digit) {
        int digit_count = 0;

        for (int num = start_range + 1; num < end_range; ++num) {
            digit_count += countDigit(num, target_digit);
        }

        return digit_count;
    }

private:
    int countDigit(int num, int target_digit) {
        int count = 0;
        std::string num_str = std::to_string(num);

        for (char digit : num_str) {
            if (digit - '0' == target_digit) {
                ++count;
            }
        }

        return count;
    }
    };