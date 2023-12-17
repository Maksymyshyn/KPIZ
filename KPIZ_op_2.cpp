#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct TRAIN {
    string NAZV;
    int NUMR;
    string DATE;
    string TIME;
};

void addRecord(vector<TRAIN>& database) {
    TRAIN newRecord;
    cout << "Введіть назву пункту призначення: ";
    cin >> newRecord.NAZV;
    cout << "Введіть номер поїзда: ";
    cin >> newRecord.NUMR;
    cout << "Введіть дату відправлення (день місяць рік): ";
    cin >> newRecord.DATE;
    cout << "Введіть час відправлення: ";
    cin >> newRecord.TIME;
    database.push_back(newRecord);
}

void editRecord(vector<TRAIN>& database) {
    int number;
    cout << "Введіть номер поїзда для редагування: ";
    cin >> number;
    for (TRAIN& item : database) {
        if (item.NUMR == number) {
            cout << "Введіть нову інформацію для цього поїзда: ";
            cin >> item.NAZV >> item.NUMR >> item.DATE >> item.TIME;
            return;
        }
    }
    cout << "Поїзд не знайдений." << endl;
}

void searchRecord(const vector<TRAIN>& database) {
    int number;
    cout << "Введіть номер поїзда для пошуку: ";
    cin >> number;
    for (const TRAIN& item : database) {
        if (item.NUMR == number) {
            cout << "Знайдено поїзд: " << item.NAZV << ", " << item.NUMR << ", "
                << item.DATE << ", " << item.TIME << std::endl;
            return;
        }
    }
    cout << "Поїзд не знайдений." << endl;
}

void deleteRecord(vector<TRAIN>& database) {
    int number;
    cout << "Введіть номер поїзда для видалення: ";
    cin >> number;
    for (size_t i = 0; i < database.size(); ++i) {
        if (database[i].NUMR == number) {
            database.erase(database.begin() + i);
            cout << "Поїзд видалений." << endl;
            return;
        }
    }
    cout << "Поїзд не знайдений." << endl;
}

void saveToFile(const vector<TRAIN>& database, const string& filename) {
    ofstream file(filename);
    for (const auto& item : database) {
        file << item.NAZV << "," << item.NUMR << "," << item.DATE << "," << item.TIME << std::endl;
    }
    file.close();
}

void loadFromFile(vector<TRAIN>& database, const string& filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        TRAIN item;
        getline(iss, item.NAZV, ',');
        string token;
        getline(iss, token, ',');
        item.NUMR = stoi(token);
        getline(iss, item.DATE, ',');
        getline(iss, item.TIME);
        database.push_back(item);
    }
    file.close();
}

int main() {
    setlocale(LC_ALL, "ukr");
    vector<TRAIN> database;
    string filename = "train_database.txt";
    loadFromFile(database, filename);
    int choice;
    while (true) {
        cout << "\n1. Додати запис\n2. Редагувати запис\n3. Видалити запис\n4. Пошук запису\n5. Показати всі записи\n0. Вихід\nВаш вибір : ";
        cin >> choice;
        switch (choice) {
        case 1:
            addRecord(database);
            break;
        case 2:
            editRecord(database);
            break;
        case 3:
            deleteRecord(database);
            break;
        case 4:
            searchRecord(database);
            break;
        case 5:
            for (const auto& item : database) {
                cout << item.NAZV << ", " << item.NUMR << ", "
                    << item.DATE << ", " << item.TIME << endl;
            }
            break;
        case 0:
            saveToFile(database, filename);
            return 0;
        default:
            cout << "Неправильний вибір. Спробуйте знову." << endl;
        }
    }
    return 0;
}
