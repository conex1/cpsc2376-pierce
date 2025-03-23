#include <iostream>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

int main() {
    float redPotion{0.0f};
    float bluePotion{0.0f};
    float* flask{nullptr};
    
    string input;
    
    while(true) {
        cout << "Which potion? (Red/Blue/Done): ";
        getline(cin, input);
        
        // Convert input to lowercase
        transform(input.begin(), input.end(), input.begin(), ::tolower);
        
        if(input == "done") {
            break;
        }
        else if(input == "red") {
            flask = &redPotion;
        }
        else if(input == "blue") {
            flask = &bluePotion;
        }
        else {
            cout << "Invalid choice! Try again.\n";
            continue;
        }
        
        cout << "Milliliters to add: ";
        float amount;
        cin >> amount;
        
        // Add using pointer
        *flask += amount;
        
        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        // Show status
        cout << "Red: " << redPotion << "mL, "
             << "Blue: " << bluePotion << "mL\n\n";
    }
    
    cout << "Final amounts - Red: " << redPotion 
         << "mL, Blue: " << bluePotion << "mL\n";
}