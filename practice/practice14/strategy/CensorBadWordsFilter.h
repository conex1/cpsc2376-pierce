#pragma once
#include "TextFilterStrategy.h"
#include <vector>
#include <sstream>
#include <algorithm>

class CensorBadWordsFilter : public TextFilterStrategy {
public:
    std::string processText(const std::string& input) const override {
        std::vector<std::string> badWords = {"bad", "evil", "wrong", "naughty"};
        std::istringstream iss(input);
        std::string word;
        std::string result;

        while (iss >> word) {
            std::string lowerWord = toLower(word);
            if (std::find(badWords.begin(), badWords.end(), lowerWord) != badWords.end()) {
                result += "**** ";
            } else {
                result += word + " ";
            }
        }

        if (!result.empty()) {
            result.pop_back();
        }
        return result;
    }

private:
    std::string toLower(const std::string& s) const {
        std::string lower;
        for (char c : s) {
            lower += std::tolower(c);
        }
        return lower;
    }
};