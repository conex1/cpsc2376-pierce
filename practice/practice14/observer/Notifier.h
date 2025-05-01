#pragma once
#include "Observer.h"
#include <iostream>

class Notifier : public Observer {
    double threshold;
public:
    Notifier(double thresh) : threshold(thresh) {}
    void update(const std::vector<double>& grades) override {
        for (double grade : grades) {
            if (grade < threshold) {
                std::cout << "Email sent to student@example.com: Grade " << grade << " is below " << threshold << "%\n";
                return;
            }
        }
    }
};