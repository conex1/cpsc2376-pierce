#pragma once
#include <vector>
#include <memory>
#include "Observer.h"

class GradeBook {
    std::vector<std::shared_ptr<Observer>> observers;
    std::vector<double> grades;

public:
    void addGrade(double grade) {
        grades.push_back(grade);
        notifyObservers();
    }

    void setGrade(int index, double grade) {
        if (index >= 0) {
            const auto idx = static_cast<std::vector<double>::size_type>(index);
            if (idx < grades.size()) {
                grades[idx] = grade;
                notifyObservers();
            }
        }
    }

    void attach(std::shared_ptr<Observer> observer) {
        observers.push_back(observer);
    }

private:
    void notifyObservers() {
        for (auto& observer : observers) {
            observer->update(grades);
        }
    }
};