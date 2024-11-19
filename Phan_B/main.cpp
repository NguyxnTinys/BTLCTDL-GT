#include <bits/stdc++.h>

using namespace std;

class SpellChecker {
private:
    vector<string> dictionary;
    string filename;

    string removePunctuation(const string& word) {
        string cleanWord;
        for (char c : word) {
            if (isalpha(c)) { // Chỉ giữ lại các ký tự chữ cái
                cleanWord += c;
            }
        }
        return cleanWord;
    }

    bool binarySearch(const vector<string>& dictionary, const string& word) {
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
    // Load dictionary from file and sort it
    void loadDictionary(const string& file) {
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

    // Convert string to lowercase
    string toLower(const string& str) {
        string result;
        for (char c : str) {
            result += tolower(c);
        }
        return result;
    }

    bool binarySearch(const string& word) {
        return binarySearch(dictionary, word);
    }

    // Check spelling of input text
    void checkSpelling() {
        string text;
        cout << "Enter text to check for spelling errors: ";
        cin.ignore();
        getline(cin, text);

        string word;
        vector<string> misspelled;
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
            for (const string& w : misspelled) {
                cout << w << endl;
            }
        }
    }

    // Add a word to the dictionary
    void addWord(const string& word) {
        string lowerWord = toLower(word);
        if (binarySearch(lowerWord)) {
            cout << "Word already exists in the dictionary.\n";
            return;
        }
        dictionary.push_back(lowerWord);
        sort(dictionary.begin(), dictionary.end());
        saveDictionary();
        cout << "Word added successfully.\n";
    }

    // Search for a word in the dictionary
    bool searchWord(const string& word) {
        return binarySearch(word);
    }

    // Delete a word from the dictionary
    void deleteWord(const string& word) {
        auto it = lower_bound(dictionary.begin(), dictionary.end(), word);
        if (it != dictionary.end() && *it == word) {
            dictionary.erase(it);
            saveDictionary();
            cout << "Word deleted successfully.\n";
        } else {
            cout << "Word not found in the dictionary.\n";
        }
    }

    // Modify a word in the dictionary
    void modifyWord(const string& oldWord, const string& newWord) {
        auto it = lower_bound(dictionary.begin(), dictionary.end(), oldWord);
        if (it != dictionary.end() && *it == oldWord) {
            *it = toLower(newWord);
            sort(dictionary.begin(), dictionary.end());
            saveDictionary();
            cout << "Word modified successfully.\n";
        } else {
            cout << "Word not found in the dictionary.\n";
        }
    }

    // Save dictionary to file
    void saveDictionary() {
        ofstream outFile(filename);
        if (!outFile.is_open()) {
            cout << "Error: Unable to open file for writing.\n";
            return;
        }

        for (string word : dictionary) {
            outFile << word << endl;
        }

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
        cin.ignore(); // Xóa bất kỳ ký tự thừa nào còn lại trong bộ đệm
        getline(cin, filename); // Đọc toàn bộ dòng nhập từ người dùng

        if (filename.empty()) { // Kiểm tra nếu người dùng không nhập gì
            filename = "dictionary.txt"; // Gán tên file mặc định
        }

        checker.loadDictionary(filename);


        while (true) {
            cout << "\nMenu:\n";
            cout << "1. Check spelling\n";
            cout << "2. Fix dictionary\n";
            cout << "3. Load program\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;

            if (choice == 0) {
                checker.loadDictionary(filename);
                break;
            } else if (choice == 1) {
                checker.checkSpelling();
            } else if (choice == 2) {
                displayFixMenu();
            } else if (choice == 3) {
                cout << "Enter dictionary file to reload: ";
                cin >> filename;
                checker.loadDictionary(filename);
            } else {
                cout << "Invalid choice. Try again.\n";
            }
        }
    }

    void displayFixMenu() {
        cout << "Enter word to search: ";
        string word;
        cin >> word;

        word = checker.toLower(word);

        if (checker.binarySearch(word)) {
            cout << "\nWord found in the dictionary.\n";
            while (true) {
                cout << "\nFix Menu:\n";
                cout << "1. Add word\n";
                cout << "3. Delete word\n";
                cout << "0. Back to main menu\n";
                cout << "Enter your choice: ";
                int subChoice;
                cin >> subChoice;

                if (subChoice == 0) {
                    break; // Quay lại menu chính
                } else if (subChoice == 1) {
                    cout << "Enter word to add: ";
                    string newWord;
                    cin >> newWord;
                    checker.addWord(newWord);
                } else if (subChoice == 3) {
                    checker.deleteWord(word); // Xóa từ
                    break; // Quay lại menu sau khi xóa
                } else {
                    cout << "Invalid choice. Try again.\n";
                }
            }
        } else {
            cout << "The word '" << word << "' does not exist in the dictionary.\n";
            while (true) {
                cout << "\nFix Menu:\n";
                cout << "1. Add word\n";
                cout << "0. Back to main menu\n";
                cout << "Enter your choice: ";
                int subChoice;
                cin >> subChoice;

                if (subChoice == 0) {
                    break; // Quay lại menu chính
                } else if (subChoice == 1) {
                    checker.addWord(word); // Thêm từ vào từ điển
                } else {
                    cout << "Invalid choice. Try again.\n";
                }
            }
        }
    }
};

int main() {
    Menu menu;
    menu.displayMainMenu();
    return 0;
}
