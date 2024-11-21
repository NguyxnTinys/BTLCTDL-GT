#include <bits/stdc++.h>
#include "vector.cpp"
using namespace std;

class SpellChecker {
private:
    vector<string> dictionary;
    string filename;

    string removePunctuation(string word) {
        string cleanWord;
        for (char c : word) {
            if (isalpha(c)) {
                cleanWord += c;
            }
        }
        return cleanWord;
    }

    bool binarySearch(vector<string>& dictionary, string word) {
        int left = 0;
        int right = dictionary.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (dictionary[mid] == word) {
                return true;
            }

            if (dictionary[mid] < word) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return false;
    }

public:
    void loadDictionary(string file) {
        filename = file;
        dictionary.clear();

        ifstream inFile(file);
        if (!inFile.is_open()) {
            cout << "Error: Unable to open file " << file << endl;
            return;
        }

        string word;
        while (inFile >> word) {
            dictionary.push_back(toLower(word));
        }
        inFile.close();

        sort(dictionary.begin(), dictionary.end());
        cout << "Dictionary loaded and sorted successfully.\n";
    }

    string toLower(string str) {
        string result;
        for (char c : str) {
            result += tolower(c);
        }
        return result;
    }

    bool binarySearch(string word) {
        return binarySearch(dictionary, word);
    }

    void checkSpelling() {
        string text, line;
        vector<string> misspelled;
        cout << "Enter text to check for spelling errors: \n";
        cin.ignore();
        while (true) {
            getline(cin, line);
            if (line.empty()) {
                break;
            }
            text += line + " ";
        }

        string word;
        stringstream ss(text);

        while (ss >> word) {
            word = removePunctuation(word);
            word = toLower(word);
            if (!binarySearch(word)) {
                misspelled.push_back(word);
            }
        }

        if (misspelled.empty()) {
            cout << "No spelling errors found.\n";
        } else {
            cout << "Misspelled words:\n";
            for (string w : misspelled) {
                cout << w << endl;
            }
        }
    }

    void addWord(string word) {
        string lowerWord = toLower(word);

        auto it = lower_bound(dictionary.begin(), dictionary.end(), lowerWord);

        if (it != dictionary.end() && *it == lowerWord) {
            cout << "Word already exists in the dictionary.\n";
            return;
        }

        dictionary.insert(it, lowerWord);
        cout << "Word added successfully.\n";
    }

    void deleteWord(string word) {
        string lowerWord = toLower(word);

        auto it = lower_bound(dictionary.begin(), dictionary.end(), lowerWord);
        if (it != dictionary.end() && *it == lowerWord) {
            dictionary.erase(it);
            cout << "Word deleted successfully.\n";
        } else {
            cout << "Word not found in the dictionary.\n";
        }
    }

    void saveDictionary() {
        cout << "Enter the filename to save the dictionary: ";
        cin.ignore();
        getline(cin, filename);

        ofstream outFile(filename);
        if (!outFile.is_open()) {
            cout << "Error: Unable to open file for writing.\n";
            return;
        }

        for (string word : dictionary) {
            outFile << word << endl;
        }

        cout << "Dictionary (" << filename << ") saved successfully.\n";
        outFile.close();
    }
};

class Menu {
private:
    SpellChecker checker;

public:
    void displayMainMenu() {
        string filename;
        cout << "Enter dictionary file to load (press Enter for default: dictionary.txt): ";
        getline(cin, filename);

        if (filename.empty()) {
            filename = "dictionary.txt";
        }

        checker.loadDictionary(filename);

        while (true) {
            cout << "\nMenu:\n";
            cout << "1. Check Spelling\n";
            cout << "2. Fix Dictionary\n";
            cout << "3. Load/Save Dictionary\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;

            if (choice == 0) {
                break;
            } else if (choice == 1) {
                checker.checkSpelling();
            } else if (choice == 2) {
                displayFixMenu();
            } else if (choice == 3) {
                displayLoadSaveMenu();
            } else {
                cout << "Invalid choice. Try again.\n";
            }
        }
    }

    void displayFixMenu() {
        while (true) {
            cout << "\nFix Menu:\n";
            cout << "1. Add Word\n";
            cout << "2. Delete Word\n";
            cout << "0. Back to main menu\n";
            cout << "Enter your choice: ";
            int subChoice;
            cin >> subChoice;

            if (subChoice == 0) {
                break;
            } else if (subChoice == 1) {
                string newWord;
                cout << "Enter word to add: ";
                cin >> newWord;
                checker.addWord(newWord);
            } else if (subChoice == 2) {
                string word;
                cout << "Enter word to delete: ";
                cin >> word;
                checker.deleteWord(checker.toLower(word));
            } else {
                cout << "Invalid choice. Try again.\n";
            }
        }
    }

    void displayLoadSaveMenu() {
        while (true) {
            cout << "\nLoad/Save Menu:\n";
            cout << "1. Load Dictionary\n";
            cout << "2. Save Dictionary\n";
            cout << "0. Back to main menu\n";
            cout << "Enter your choice: ";
            int subChoice;
            cin >> subChoice;

            if (subChoice == 0) {
                break;
            } else if (subChoice == 1) {
                string file;
                cout << "Enter file name to load: ";
                cin >> file;
                checker.loadDictionary(file);
            } else if (subChoice == 2) {
                checker.saveDictionary();
            } else {
                cout << "Invalid choice. Try again.\n";
            }
        }
    }
};

int main() {
    Menu menu;
    menu.displayMainMenu();
    return 0;
}
