#include <iostream>
#include <list>
#include <string>
#include <limits>

using namespace std;

int main() {
    list<string> texts;
    int choice;

    while (true) {
        cout << "\n1. Add Text\n2. Remove Text\n3. Show Texts\n4. Exit\nChoice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: { // Add Text
                string text;
                cout << "Enter text: ";
                getline(cin, text);
                texts.push_back(text);
                cout << "Text added!\n";
                break;
            }
            case 2: { // Remove Text
                if (texts.empty()) {
                    cout << "No texts to remove!\n";
                    break;
                }

                int index;
                cout << "Enter text number to remove: ";
                if (!(cin >> index)) {
                    cout << "Invalid input!\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                if (index < 1 || index > texts.size()) {
                    cout << "Invalid number!\n";
                    break;
                }

                auto it = texts.begin();
                advance(it, index - 1);
                texts.erase(it);
                cout << "Text removed!\n";
                break;
            }
            case 3: { // Show Texts
                if (texts.empty()) {
                    cout << "No texts stored!\n";
                    break;
                }

                cout << "Texts:\n";
                int count = 1;
                for (const auto& text : texts) {
                    cout << count++ << ". " << text << "\n";
                }
                break;
            }
            case 4: // Exit
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }
    return 0;
}