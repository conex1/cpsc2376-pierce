#pragma once
#include <vector>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::vector<double>& grades) = 0;
};