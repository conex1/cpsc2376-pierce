#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

class Employee {
protected:
    string name;
    int id;
public:
    Employee(string name, int id) : name(name), id(id) {}
    virtual double calculateSalary() const = 0;
    virtual void displayInfo() const {
        cout << "ID: " << id << ", Name: " << name;
    }
    virtual ~Employee() {}
};

class SalariedEmployee : public Employee {
    double monthlySalary;
public:
    SalariedEmployee(string name, int id, double monthlySalary)
        : Employee(name, id), monthlySalary(monthlySalary) {}
    double calculateSalary() const override {
        return monthlySalary;
    }
    void displayInfo() const override {
        Employee::displayInfo();
        cout << ", Type: Salaried, Monthly Salary: $" 
             << fixed << setprecision(2) << monthlySalary << endl;
    }
};

class HourlyEmployee : public Employee {
    double hourlyRate;
    int hoursWorked;
public:
    HourlyEmployee(string name, int id, double hourlyRate, int hoursWorked)
        : Employee(name, id), hourlyRate(hourlyRate), hoursWorked(hoursWorked) {}
    double calculateSalary() const override {
        return hourlyRate * hoursWorked;
    }
    void displayInfo() const override {
        Employee::displayInfo();
        cout << ", Type: Hourly, Hours Worked: " << hoursWorked 
             << ", Hourly Rate: $" << fixed << setprecision(2) << hourlyRate 
             << ", Salary: $" << calculateSalary() << endl;
    }
};

class CommissionEmployee : public Employee {
    double baseSalary;
    double salesAmount;
    double commissionRate;
public:
    CommissionEmployee(string name, int id, double baseSalary, double salesAmount, double commissionRate)
        : Employee(name, id), baseSalary(baseSalary), salesAmount(salesAmount), commissionRate(commissionRate) {}
    double calculateSalary() const override {
        return baseSalary + (salesAmount * commissionRate);
    }
    void displayInfo() const override {
        Employee::displayInfo();
        ios_base::fmtflags originalFlags = cout.flags();
        streamsize originalPrecision = cout.precision();
        cout << ", Type: Commission, Base Salary: $" << fixed << setprecision(2) << baseSalary 
             << ", Sales: $" << salesAmount 
             << ", Commission Rate: " << fixed << setprecision(0) << (commissionRate * 100) << "%"
             << fixed << setprecision(2) << ", Salary: $" << calculateSalary() << endl;
        cout.flags(originalFlags);
        cout.precision(originalPrecision);
    }
};

int main() {
    vector<Employee*> employees;
    ifstream file("employees.txt");
    if (!file.is_open()) {
        cerr << "Failed to open file." << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        vector<string> tokens = split(line, ' ');
        if (tokens.empty()) continue;

        string type = tokens[0];
        if (type == "Salaried") {
            if (tokens.size() != 4) {
                cerr << "Invalid Salaried employee data: " << line << endl;
                continue;
            }
            try {
                int id = stoi(tokens[1]);
                string name = tokens[2];
                double salary = stod(tokens[3]);
                employees.push_back(new SalariedEmployee(name, id, salary));
            } catch (...) {
                cerr << "Error parsing Salaried employee data: " << line << endl;
            }
        } else if (type == "Hourly") {
            if (tokens.size() != 5) {
                cerr << "Invalid Hourly employee data: " << line << endl;
                continue;
            }
            try {
                int id = stoi(tokens[1]);
                string name = tokens[2];
                double rate = stod(tokens[3]);
                int hours = stoi(tokens[4]);
                employees.push_back(new HourlyEmployee(name, id, rate, hours));
            } catch (...) {
                cerr << "Error parsing Hourly employee data: " << line << endl;
            }
        } else if (type == "Commission") {
            if (tokens.size() != 6) {
                cerr << "Invalid Commission employee data: " << line << endl;
                continue;
            }
            try {
                int id = stoi(tokens[1]);
                string name = tokens[2];
                double base = stod(tokens[3]);
                double sales = stod(tokens[4]);
                double rate = stod(tokens[5]);
                employees.push_back(new CommissionEmployee(name, id, base, sales, rate));
            } catch (...) {
                cerr << "Error parsing Commission employee data: " << line << endl;
            }
        } else {
            cerr << "Unknown employee type: " << type << endl;
        }
    }

    file.close();

    for (const auto& emp : employees) {
        emp->displayInfo();
    }

    for (auto& emp : employees) {
        delete emp;
    }
    employees.clear();

    return 0;
}