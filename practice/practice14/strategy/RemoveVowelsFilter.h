#pragma once
#include "TextFilterStrategy.h"
#include <string>
#include <cctype>

class RemoveVowelsFilter : public TextFilterStrategy {
public:
    std::string processText(const std::string& input) const override {
        std::string result;
        for (char c : input) {
            if (!isVowel(c)) {
                result += c;
            }
        }
        return result;
    }

private:
    bool isVowel(char c) const {
        c = std::tolower(c);
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
};