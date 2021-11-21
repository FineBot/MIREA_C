#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Huffman {
public:
    struct item {
        char ch = NULL;
        int count = -1;
        string code = "";
    };
    struct Node {
        Node *rightChildren;
        Node *leftChildren;
        int count = 0;
        item Item;
    };

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

    int findInVectorByCode(vector<item> v, string target) {
        for (int i = 0; i < v.size(); i++) {
            if (v.at(i).code == target) {
                return i;
            }
        }
        return -1;
    }

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


    Huffman(string data) {
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

        qsortRecursive(&items, items.size());
        vector<Node> nodes;
        for (int i = 0; i < items.size(); i++) {
            cout << items.at(i).ch << ". count: " << items.at(i).count<<"; "<<(items.at(i).count*1.0)/(data.size()*1.0) << endl;
            Node node;
            node.Item = items.at(i);
            node.count = items.at(i).count;
            nodes.push_back(node);
        }

        createTree(&nodes);
        setCodes(&nodes.at(0), &items, "");

        for (int i = 0; i < items.size(); i++) {
            cout << endl << items.at(i).ch << ". code: " << items.at(i).code;
        }
        cout<<endl<<endl;
        for(int i=0;i<data.size();i++){
            cout<<items.at(findInVector(items,data[i])).code<<" ";
        }

    }

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

