#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

template<typename T>
T calculate(T a, T b, char op) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: throw invalid_argument("Invalid operator");
    }
}

bool isDouble(const string& s) {
    return s.find('.') != string::npos || 
           s.find('e') != string::npos || 
           s.find('E') != string::npos;
}

int main() {
    string input1, input2;
    char op;
    
    cout << "Enter first number: ";
    cin >> input1;
    cout << "Enter second number: ";
    cin >> input2;
    cout << "Enter operation (+, -, *, /): ";
    cin >> op;

    try {
        if (isDouble(input1) || isDouble(input2)) {
            double num1 = stod(input1);
            double num2 = stod(input2);
            double result = calculate<double>(num1, num2, op);
            cout << "Result: " << fixed << setprecision(2) << result << endl;
        } else {
            int num1 = stoi(input1);
            int num2 = stoi(input2);
            int result = calculate<int>(num1, num2, op);
            cout << "Result: " << result << endl;
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}