#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Shennon {
public:
    // структура для хранения символа
    struct item {
        char ch = NULL;
        int count = -1;
        string code = "";
    };

// функция поска в векторе по символу
    int findInVector(vector<item> v, char target) {
        for (int i = 0; i < v.size(); i++) {
            if (v.at(i).ch == target) {
                return i;
            }
        }
        return -1;
    }

// функция поиска в векторе по коду
    int findInVectorByCode(vector<item> v, string target) {
        for (int i = 0; i < v.size(); i++) {
            if (v.at(i).code == target) {
                return i;
            }
        }
        return -1;
    }

// функция разделения вектора на две разные группы по сумме
    int setMinDifferent(item *arrayData, int startIndex, int endIndex) {
        int delIndex = startIndex;
        int minAbs = -1;
        int lastDelIndex = -1;
        while (delIndex < endIndex) {
            int sumA = 0;
            int sumB = 0;
            for (int i = startIndex; i < endIndex; i++) {
                if (i <= delIndex)
                    sumA += arrayData[i].count;
                else
                    sumB += arrayData[i].count;
            }
            if (abs(sumA - sumB) < minAbs || minAbs == -1) {
                minAbs = abs(sumA - sumB);
                lastDelIndex = delIndex;
            }
            delIndex++;
        }
        return lastDelIndex;
    }
// функция быстрой сортировки
    void qsortRecursive(item *mas, int size) {
        int i = 0;
        int j = size - 1;
        item mid = mas[size / 2];
        do {
            while (mas[i].count > mid.count) {
                i++;
            }
            while (mas[j].count < mid.count) {
                j--;
            }
            if (i <= j) {
                item tmp = mas[i];
                mas[i] = mas[j];
                mas[j] = tmp;

                i++;
                j--;
            }
        } while (i <= j);
        if (j > 0) {
            qsortRecursive(mas, j + 1);
        }
        if (i < size) {
            qsortRecursive(&mas[i], size - i);
        }
    }

//    функция декодирования файла
    void decodeFile(string pathToFile) {
        string data;
        string params;
        ifstream fin(pathToFile);
        getline(fin, data);
        getline(fin, params);
        fin.close();

        vector<item> items;
        string buffCode = "";
        for (int i = 0; i < params.length(); i++) {

            if (buffCode == "" && params[i + 1] == ':') {
                item t;
                t.ch = params[i];
                items.push_back(t);
                i++;
            } else if (params[i] != ';') {
                buffCode += params[i];

            } else {
                items.at(items.size() - 1).code = buffCode;
                buffCode = "";
            }
        }

        buffCode = "";
        string decodedData = "";

        for (int i = 0; i < data.length(); i++) {
            buffCode += data[i];
            int j = findInVectorByCode(items, buffCode);
            if (j != -1) {
                buffCode = "";
                decodedData += items.at(j).ch;
            }
        }

        ofstream of(pathToFile);
        of << decodedData;
        of.close();
    }
// функция кодирования файла
    void encodeFile(string pathToFile) {

        string data;
        ifstream fin(pathToFile);
        getline(fin, data);
        fin.close();
        vector<item> items;
        for (int i = 0; i < data.length(); i++) {
            int findIndex = findInVector(items, (data[i]));
            if (findIndex != -1) {
                items.at(findIndex).count++;
            } else {
                item buff;
                buff.ch = (data[i]);
                buff.count = 1;
                items.push_back(buff);
            }
        }

        item *array = new item[items.size()];
        for (int i = 0; i < items.size(); i++) {
            array[i] = items.at(i);
        }
        qsortRecursive(array, items.size());
        int size = items.size();
        items.clear();
        for (int i = 0; i < size; i++) {
            items.push_back(array[i]);
        }

        setCodes(&items, array, 0, size);

        ofstream of(pathToFile);

        for (int i = 0; i < data.size(); i++) {
            of << items.at(findInVector(items, data[i])).code;
        }
        of << endl;
        for (int i = 0; i < items.size(); i++) {
            of << items.at(i).ch << ":" << items.at(i).code << ";";
        }
        of.close();
    }

    Shennon(){}

// в конструкторе кодируем строку
    Shennon(string
            data) {
        vector<item> items;
        for (int i = 0; i < data.length(); i++) {
            int findIndex = findInVector(items, tolower(data[i]));
            if (findIndex != -1) {
                items.at(findIndex).count++;
            } else {
                item buff;
                buff.ch = (data[i]);
                buff.count = 1;
                items.push_back(buff);
            }
        }
        item *array = new item[items.size()];
        for (int i = 0; i < items.size(); i++) {
            array[i] = items.at(i);
        }
        qsortRecursive(array, items.size());
        int size = items.size();
        items.clear();
        for (int i = 0; i < size; i++) {
            items.push_back(array[i]);
        }

        setCodes(&items, array, 0, size);
        int countBits = 0;
        for (int i = 0; i < items.size(); i++) {
            cout << endl << items.at(i).ch << " (" << items.at(i).count << ", "
                 << items.at(i).count * items.at(i).code.length() << ") " << ": " << items.at(i).code;
            countBits += items.at(i).count * items.at(i).code.length();
        }
        cout << endl << "Count of bits: " << countBits;

    }

    // функция установки кодов
    void setCodes(vector<item> *items, item *array, int startIndex, int endIndex) {
        int del = setMinDifferent(array, startIndex, endIndex);
        if (endIndex - del > 1) {
            for (int i = startIndex; i < endIndex; i++) {
                if (i <= del) {
                    items->at(i).code += "0";
                } else {
                    items->at(i).code += "1";
                }
            }
        }
        if (del > -1 && endIndex - startIndex > 1) {
            setCodes(items, array, startIndex, del + 1);
            setCodes(items, array, del + 1, endIndex);
        }


    }

};

