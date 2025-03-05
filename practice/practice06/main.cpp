#include <iostream>
#include <limits>
#include "Fraction.h"
#include "MixedFraction.h"

using namespace std;

void displayMenu(const Fraction& current) {
    cout << "\nCurrent Fraction: " << current << endl;
    cout << "Options:\n1. Enter a fraction manually\n2. Add a fraction\n3. Subtract a fraction\n4. Multiply by a fraction\n5. Divide by a fraction\n6. Display as Mixed Fraction\n7. Clear Fraction\n8. Exit\nEnter your choice: ";
}

Fraction getFractionFromUser() {
    int n, d;
    cout << "Enter numerator: ";
    while (!(cin >> n)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter numerator: ";
    }
    cout << "Enter denominator: ";
    while (!(cin >> d)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter denominator: ";
    }
    try {
        return Fraction(n, d);
    }
    catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << ". Using 1 as denominator.\n";
        return Fraction(n, 1);
    }
}

int main() {
    Fraction current;
    int choice;
    do {
        displayMenu(current);
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Try again.\n";
            continue;
        }
        try {
            switch (choice) {
            case 1: current = getFractionFromUser(); break;
            case 2: current = current + getFractionFromUser(); break;
            case 3: current = current - getFractionFromUser(); break;
            case 4: current = current * getFractionFromUser(); break;
            case 5: current = current / getFractionFromUser(); break;
            case 6: cout << "Mixed Fraction: " << MixedFraction(current) << endl; break;
            case 7: current = Fraction(); break;
            case 8: cout << "Exiting.\n"; break;
            default: cout << "Invalid choice.\n";
            }
        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    } while (choice != 8);
    return 0;
}