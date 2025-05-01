#pragma once
#include "TextFilterStrategy.h"
#include <cctype>

class UppercaseFilter : public TextFilterStrategy {
public:
    std::string processText(const std::string& input) const override {
        std::string result = input;
        for (auto& c : result) {
            c = std::toupper(c);
        }
        return result;
    }
};