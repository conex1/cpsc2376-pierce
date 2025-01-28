#include <iostream>
#include <vector>

// Function to print the vector
void printVector(const std::vector<int>& vec) {
    std::cout << "Vector elements: ";
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// Function to double the vector elements
void doubleVector(std::vector<int>& vec) {
    for (int& num : vec) {
        num *= 2;
    }
}

// Function to calculate the sum of the vector elements
int calculateSum(const std::vector<int>& vec) {
    int sum = 0;
    for (int num : vec) {
        sum += num;
    }
    return sum;
}

// Function to print multiples of a user-defined value
void printMultiples(const std::vector<int>& vec, int multiple) {
    std::cout << "Multiples of " << multiple << ": ";
    for (int num : vec) {
        if (num % multiple == 0) {
            std::cout << num << " ";
        }
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> numbers;
    int choice;

    do {
        // Display menu
        std::cout << "\nMenu:\n";
        std::cout << "1. Add an item to the vector\n";
        std::cout << "2. Print the vector\n";
        std::cout << "3. Double the vector\n";
        std::cout << "4. Find the sum of the vector\n";
        std::cout << "5. Print multiples of a user-defined value\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int num;
                std::cout << "Enter a number to add: ";
                std::cin >> num;
                numbers.push_back(num);
                break;
            }
            case 2:
                printVector(numbers);
                break;
            case 3:
                doubleVector(numbers);
                std::cout << "Vector has been doubled.\n";
                break;
            case 4: {
                int sum = calculateSum(numbers);
                std::cout << "Sum of the vector: " << sum << std::endl;
                break;
            }
            case 5: {
                int multiple;
                std::cout << "Enter a number to find multiples: ";
                std::cin >> multiple;
                printMultiples(numbers, multiple);
                break;
            }
            case 6:
                std::cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 6);

    return 0;
}