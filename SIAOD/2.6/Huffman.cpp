#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Huffman {
public:
    // Структура для хранения букв
    struct item {
        char ch = NULL;
        int count = -1;
        string code = "";
    };

    // структура для создания дерева
    struct Node {
        Node *rightChildren;
        Node *leftChildren;
        int count = 0;
        item Item;
    };

    // функция поиска в векторе по символу
    int findInVector(vector<item> *v, char target) {
        for (int i = 0; i < v->size(); i++) {
            if (v->at(i).ch == target) {
                return i;
            }
        }
        return -1;
    }

    int findInVector(vector<item> v, char target) {
        for (int i = 0; i < v.size(); i++) {
            if (v.at(i).ch == target) {
                return i;
            }
        }
        return -1;
    }

    // функция поиска в векторе по коду символа
    int findInVectorByCode(vector<item> v, string target) {
        for (int i = 0; i < v.size(); i++) {
            if (v.at(i).code == target) {
                return i;
            }
        }
        return -1;
    }

    // функция быстрой сортировки вектора
    void qsortRecursive(vector<Node> *mas, int size) {
        int i = 0;
        int j = size - 1;
        Node mid = mas->at(size / 2);
        do {
            while (mas->at(i).count > mid.count) {
                i++;
            }
            while (mas->at(j).count < mid.count) {
                j--;
            }
            if (i <= j) {
                Node tmp = mas->at(i);
                mas->at(i) = mas->at(j);
                mas->at(j) = tmp;

                i++;
                j--;
            }
        } while (i <= j);
        if (j > 0) {
            qsortRecursive(mas, j + 1);
        }
        if (i < size) {
            qsortRecursive(mas, size - i);
        }
    }

    // функция быстрой сортировки вектора
    void qsortRecursive(vector<item> *mas, int size) {
        int i = 0;
        int j = size - 1;
        item mid = mas->at(size / 2);
        do {
            while (mas->at(i).count > mid.count) {
                i++;
            }
            while (mas->at(j).count < mid.count) {
                j--;
            }
            if (i <= j) {
                item tmp = mas->at(i);
                mas->at(i) = mas->at(j);
                mas->at(j) = tmp;

                i++;
                j--;
            }
        } while (i <= j);
        if (j > 0) {
            qsortRecursive(mas, j + 1);
        }
        if (i < size) {
            qsortRecursive(mas, size - i);
        }
    }


    Huffman(){}

    void decodeString(string data, string params){
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
        cout<<decodedData;
    }

    // конструктор класса
    Huffman(string data) {
        vector<item> items;

        // читаем строку из консоли, заносим символы в массив и одновременно
        // подсчитываем их количество
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

        // сортируем вектор
        qsortRecursive(&items, items.size());
        vector<Node> nodes;

        // формируем новый вектор для создания дерева
        for (int i = 0; i < items.size(); i++) {
            cout << items.at(i).ch << ". count: " << items.at(i).count<<"; "<<(items.at(i).count*1.0)/(data.size()*1.0) << endl;
            Node node;
            node.Item = items.at(i);
            node.count = items.at(i).count;
            nodes.push_back(node);
        }

        // создаем дерево
        createTree(&nodes);
        // по этому дереву присваиваем символам коды
        setCodes(&nodes.at(0), &items, "");

        // выводим коды
        for (int i = 0; i < items.size(); i++) {
            cout << endl << items.at(i).ch << ". code: " << items.at(i).code;
        }
        cout<<endl<<endl;

        // кодируем строку
        for(int i=0;i<data.size();i++){
            cout<<items.at(findInVector(items,data[i])).code;
        }
        cout<<endl<<"Keys:"<<endl;
        for (int i = 0; i < items.size(); i++) {
            cout << items.at(i).ch << ":" << items.at(i).code<<";";
        }

    }

    // функция объединения символов в узлы
    void createTree(vector<Node> *data) {
        while (data->size() > 1) {
            Node *one = new Node;
            one->count = data->at(data->size() - 1).count;
            one->leftChildren = data->at(data->size() - 1).leftChildren;
            one->rightChildren = data->at(data->size() - 1).rightChildren;
            one->Item = data->at(data->size() - 1).Item;
            data->erase(data->cbegin() + data->size() - 1);

            Node *two = new Node;
            two->count = data->at(data->size() - 1).count;
            two->leftChildren = data->at(data->size() - 1).leftChildren;
            two->rightChildren = data->at(data->size() - 1).rightChildren;
            two->Item = data->at(data->size() - 1).Item;
            data->erase(data->cbegin() + data->size() - 1);

            Node sum;
            sum.count = one->count + two->count;
            sum.leftChildren = one;
            sum.rightChildren = two;
            data->push_back(sum);
            qsortRecursive(data, data->size());
        }
    }

    // функция установки кодов
    void setCodes(Node *node, vector<item> *items, string gen) {
        if (node->Item.count != -1) {
            int k = findInVector(items, node->Item.ch);
            items->at(k).code = gen;
        } else {
            if (node->leftChildren) {
                setCodes(node->leftChildren, items, gen + "0");
            }
            if (node->rightChildren) {
                setCodes(node->rightChildren, items, gen + "1");
            }
        }

    }

};

