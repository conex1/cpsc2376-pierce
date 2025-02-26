#include <iostream>
#include <vector>
#include <iterator>

int main() {
    std::vector<int> numbers;
    int n, value;

    // Get user input for the number of elements
    std::cout << "Enter the number of elements: ";
    std::cin >> n;

    // Input the values into the vector
    std::cout << "Enter " << n << " integers: ";
    for (int i = 0; i < n; ++i) {
        std::cin >> value;
        numbers.push_back(value);
    }

    // Print the numbers using iterators
    std::cout << "You entered: ";
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Find and print the sum of even numbers using iterators
    int evenSum = 0;
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        if (*it % 2 == 0) {
            evenSum += *it;
        }
    }

    std::cout << "Sum of even numbers: " << evenSum << std::endl;

    return 0;
}
