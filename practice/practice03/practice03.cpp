#include <vector>
#include <stdexcept>

class MathUtils {
public:
    static int sumRange(int start, int end) {
        int sum = 0;
        for (int i = start; i <= end; ++i) {
            sum += i;
        }
        return sum;
    }

    static bool containsNegative(const std::vector<int>& v) {
        for (int num : v) {
            if (num < 0) {
                return true;
            }
        }
        return false;
    }

    static int findMax(const std::vector<int>& v) {
        if (v.empty()) {
            throw std::runtime_error("Vector is empty");
        }
        int max = v[0];
        for (int num : v) {
            if (num > max) {
                max = num;
            }
        }
        return max;
    }
};
