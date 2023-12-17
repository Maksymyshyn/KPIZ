#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct WordInfo {
    string word;
    int length;
};

void processFile(const string& inputFileName, const string& outputFileName) {
    setlocale(LC_ALL, "ukr");
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Помилка відкриття файлів." << endl;
        return;
    }

    vector<WordInfo> wordsWithMinLength;
    int uppercaseCount = 0;

    string line;
    while (getline(inputFile, line)) {
        outputFile << line << endl;

        for (char ch : line) {
            if (isupper(ch)) {
                uppercaseCount++;
            }
        }

        istringstream iss(line);
        string word;
        while (iss >> word) {
            wordsWithMinLength.push_back({ word, static_cast<int>(word.length()) });
        }
    }

    int minWordLength = -1;
    for (const auto& wordInfo : wordsWithMinLength) {
        if (minWordLength == -1 || wordInfo.length < minWordLength) {
            minWordLength = wordInfo.length;
        }
    }

    ifstream originalFile(inputFileName);
    ofstream modifiedFile(outputFileName + "_modified");

    while (getline(originalFile, line)) {
        istringstream iss(line);
        string word;
        while (iss >> word) {
            if (!islower(word[0])) {
                modifiedFile << word << " ";
            }
        }
        modifiedFile << std::endl;
    }

    cout << "Кількість великих літер: " << uppercaseCount << endl;
    cout << "Слова з мінімальною довжиною: ";
    for (const auto& wordInfo : wordsWithMinLength) {
        if (wordInfo.length == minWordLength) {
            cout << wordInfo.word << " ";
        }
    }
    cout << endl;

    inputFile.close();
    outputFile.close();
    originalFile.close();
    modifiedFile.close();
}

int main() {
    processFile("input.txt", "output.txt");

    return 0;
}
