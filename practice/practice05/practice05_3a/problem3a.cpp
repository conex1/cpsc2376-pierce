#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    std::vector<int> numbers;
    int n, value;

    // Get user input for the number of elements
    std::cout << "Enter the number of elements: ";
    std::cin >> n;

    // Input values into the vector
    std::cout << "Enter " << n << " integers: ";
    for (int i = 0; i < n; ++i) {
        std::cin >> value;
        numbers.push_back(value);
    }

    // Print each element squared using std::for_each and lambda
    std::cout << "Squared elements: ";
    std::for_each(numbers.begin(), numbers.end(), [](int n) { 
        std::cout << n * n << " "; 
    });
    std::cout << std::endl;

    // Sum of squared elements using std::accumulate and lambda
    int sumOfSquares = std::accumulate(numbers.begin(), numbers.end(), 0, [](int sum, int n) {
        return sum + n * n;
    });

    // Print the sum of squares
    std::cout << "Sum of squared elements: " << sumOfSquares << std::endl;

    return 0;
}
