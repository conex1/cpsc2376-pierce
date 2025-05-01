#pragma once
#include <memory>
#include <string>
#include "TextFilterStrategy.h"

class TextProcessor {
    std::string text;
    std::unique_ptr<TextFilterStrategy> strategy;
public:
    TextProcessor(const std::string& input) : text(input) {}
    void setStrategy(std::unique_ptr<TextFilterStrategy> newStrategy) {
        strategy = std::move(newStrategy);
    }
    std::string process() const {
        return strategy ? strategy->processText(text) : text;
    }
};