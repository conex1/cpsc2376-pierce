#include <iostream>
#include <sstream>
#include <memory>
#include "GradeBook.h"
#include "Averager.h"
#include "Notifier.h"

int main() {
    GradeBook gradeBook;
    auto averager = std::make_shared<Averager>();
    auto notifier = std::make_shared<Notifier>(60.0);

    gradeBook.attach(averager);
    gradeBook.attach(notifier);

    std::string command;
    while (true) {
        std::cout << "Enter command (add <grade>, set <index> <grade>, quit): ";
        std::getline(std::cin, command);
        if (command == "quit") break;

        std::istringstream iss(command);
        std::string cmd;
        iss >> cmd;
        if (cmd == "add") {
            double grade;
            if (iss >> grade) {
                gradeBook.addGrade(grade);
            } else {
                std::cout << "Invalid grade.\n";
            }
        } else if (cmd == "set") {
            int index;
            double grade;
            if (iss >> index >> grade) {
                gradeBook.setGrade(index, grade);
            } else {
                std::cout << "Invalid index or grade.\n";
            }
        } else {
            std::cout << "Unknown command.\n";
        }
    }

    return 0;
}