#include <iostream>
#include <memory>
#include "TextProcessor.h"
#include "ReverseFilter.h"
#include "UppercaseFilter.h"
#include "RemoveVowelsFilter.h"
#include "CensorBadWordsFilter.h"

int main() {
    std::string input;
    std::cout << "Enter a sentence: ";
    std::getline(std::cin, input);

    TextProcessor processor(input);

    while (true) {
        std::cout << "\nChoose a strategy:\n"
                  << "1. Reverse\n"
                  << "2. Uppercase\n"
                  << "3. Remove vowels\n"
                  << "4. Censor bad words\n"
                  << "5. Exit\n"
                  << "Choice: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 5) break;

        switch (choice) {
            case 1:
                processor.setStrategy(std::make_unique<ReverseFilter>());
                break;
            case 2:
                processor.setStrategy(std::make_unique<UppercaseFilter>());
                break;
            case 3:
                processor.setStrategy(std::make_unique<RemoveVowelsFilter>());
                break;
            case 4:
                processor.setStrategy(std::make_unique<CensorBadWordsFilter>());
                break;
            default:
                std::cout << "Invalid choice.\n";
                continue;
        }

        std::cout << "Processed text: " << processor.process() << "\n";
    }

    return 0;
}