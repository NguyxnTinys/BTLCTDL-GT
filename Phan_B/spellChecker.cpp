#include <bits/stdc++.h>
#include "LoadFile.cpp"

using namespace std;

class SpellChecker {
public:
    void checkSpelling(const string& text) const {
        stringstream ss(text);
        string word;
        const auto& dictionaryWords = LoadFile::getWords(); // Lấy từ điển đã load
        bool noErrors = true;

        while (ss >> word) {
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            if (!binary_search(dictionaryWords.begin(), dictionaryWords.end(), word)) {
                cout << "Misspelled: " << word << endl;
                noErrors = false;
            }
        }

        if (noErrors) {
            cout << "No spelling errors found." << endl;
        }
    }

    void addWord(const string& word) {
        auto& dictionaryWords = const_cast<vector<string>&>(LoadFile::getWords()); // Lấy từ điển đã load (chỉnh sửa được)
        string lowerWord = word;
        transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), ::tolower);

        if (!binary_search(dictionaryWords.begin(), dictionaryWords.end(), lowerWord)) {
            dictionaryWords.push_back(lowerWord);
            sort(dictionaryWords.begin(), dictionaryWords.end());
            cout << "Word added successfully!" << endl;
        } else {
            cout << "Word already exists in the dictionary." << endl;
        }
    }
};
