#pragma once
#include <string>

class TextFilterStrategy {
public:
    virtual ~TextFilterStrategy() = default;
    virtual std::string processText(const std::string& input) const = 0;
};