#include <iostream>
#include <iomanip>

using namespace std;

double convertTemperature(double temp, char scale = 'F') {
    if (scale == 'F') { // Celsius to Fahrenheit
        return (temp * 9.0/5.0) + 32;
    }
    else { // Fahrenheit to Celsius
        return (temp - 32) * 5.0/9.0;
    }
}

int main() {
    int choice;
    double temperature;
    
    cout << "1. Convert Celsius to Fahrenheit" << endl;
    cout << "2. Convert Fahrenheit to Celsius" << endl;
    cout << "Choose an option: ";
    cin >> choice;
    
    cout << "Enter temperature: ";
    cin >> temperature;
    
    cout << fixed << setprecision(2);
    
    if (choice == 1) {
        double converted = convertTemperature(temperature);
        cout << "Converted: " << converted << "°F" << endl;
    }
    else if (choice == 2) {
        double converted = convertTemperature(temperature, 'C');
        cout << "Converted: " << converted << "°C" << endl;
    }
    else {
        cout << "Invalid option!" << endl;
    }
    
    return 0;
}