#include <bits/stdc++.h>
using namespace std;

class LoadFile {
private:
    static vector<string> dictionaryWords; // Biến tĩnh lưu từ điển
    static bool isLoaded; // Biến để kiểm tra xem đã load file hay chưa

public:
    static void loadWordsFromFile(const string& filename) {
        if (!isLoaded) { // Chỉ load file nếu chưa load
            ifstream file(filename);
            string word;

            if (file.is_open()) {
                while (file >> word) {
                    dictionaryWords.push_back(word);
                }
                file.close();
                // Sắp xếp từ sau khi load
                sort(dictionaryWords.begin(), dictionaryWords.end());
                isLoaded = true; // Đánh dấu đã load
            } else {
                cerr << "Could not open file: " << filename << endl;
            }
        }
    }

    static void saveWordsToFile(const string& filename) {
        ofstream file(filename);

        if (file.is_open()) {
            for (const auto& word : dictionaryWords) {
                file << word << endl;
            }
            file.close();
        } else {
            cerr << "Could not open file for writing: " << filename << endl;
        }
    }

    static const vector<string>& getWords() {
        return dictionaryWords; // Trả về tham chiếu tới danh sách từ
    }
};

// Khởi tạo biến tĩnh
vector<string> LoadFile::dictionaryWords;
bool LoadFile::isLoaded = false;
