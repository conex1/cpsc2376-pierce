#pragma once
#include "TextFilterStrategy.h"
#include <algorithm>

class ReverseFilter : public TextFilterStrategy {
public:
    std::string processText(const std::string& input) const override {
        std::string result = input;
        std::reverse(result.begin(), result.end());
        return result;
    }
};