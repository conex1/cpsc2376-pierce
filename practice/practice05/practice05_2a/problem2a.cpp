#include <iostream>
#include <vector>
#include <numeric>  // For std::accumulate
#include <functional> // For std::multiplies

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

    // Calculate sum using std::accumulate
    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);

    // Calculate product using std::accumulate with std::multiplies
    int product = std::accumulate(numbers.begin(), numbers.end(), 1, std::multiplies<int>());

    // Print results
    std::cout << "Sum of all elements: " << sum << std::endl;
    std::cout << "Product of all elements: " << product << std::endl;

    return 0;
}
