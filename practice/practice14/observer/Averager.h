#pragma once
#include "Observer.h"
#include <iostream>

class Averager : public Observer {
public:
    void update(const std::vector<double>& grades) override {
        double sum = 0.0;
        for (double g : grades) sum += g;
        double avg = grades.empty() ? 0 : sum / grades.size();
        std::cout << "Average: " << avg << "\n";
    }
};