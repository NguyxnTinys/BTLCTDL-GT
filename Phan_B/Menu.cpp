#include <bits/stdc++.h>
#include "SpellChecker.cpp"

using namespace std;

class Menu {
private:
    SpellChecker spellChecker;

    void printMenuOptions() const {
        cout << "1. Check Spelling\n";
        cout << "2. Fix Dictionary\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
    }

    void handleCheckSpelling() {
        string text;
        cout << "Enter text to check for spelling errors: ";
        cin.ignore();
        getline(cin, text);
        spellChecker.checkSpelling(text);
    }

    void handleFixDictionary() {
        string word;
        cout << "Enter a new word to add to the dictionary: ";
        cin >> word;
        spellChecker.addWord(word);
    }

public:
    void run(const string& dictionaryFile) {
        LoadFile::loadWordsFromFile(dictionaryFile);

        while (true) {
            printMenuOptions();
            int choice;
            cin >> choice;

            if (choice == 0) {
                cout << "Exiting..." << endl;
                LoadFile::saveWordsToFile(dictionaryFile);
                break;
            }

            switch (choice) {
                case 1:
                    handleCheckSpelling();
                    break;
                case 2:
                    handleFixDictionary();
                    break;
                default:
                    cout << "Invalid choice. Try again." << endl;
            }
        }
    }
};
