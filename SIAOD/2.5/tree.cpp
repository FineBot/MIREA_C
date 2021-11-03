#include <iostream>
#include <string>

using namespace std;

class tree { // класс дерева
private:
    struct Node { // структура узла
        int id = -1;
        int weight = -1;
        Node *next = nullptr;
        Node *childrens = nullptr;
    };
    struct findNode { // структура узла для поиска
        Node *node = nullptr;
        findNode *next = nullptr;
    };

    int searchResult = -1;
    string resultPath = "";
public:
    Node *root = nullptr; // первый узел

    void add(int digit, int parent, int weight) { // функция добавления узла в дерево
        Node *buff = root;
        if (buff == nullptr) { // если корневой узел не существует, то создаем его
            root = new Node;
            root->id = digit;
            root->weight = weight;
        } else if (buff->childrens == nullptr) { // если не имеет дочерних элементов
            Node *b = new Node;
            b->id = digit;
            b->weight = weight;
            root->childrens = b;
        } else {
            findNode *finds = new findNode; // ищем все элементы в дереве, id которых равен заданному
            find(parent, root, finds);

            findNode *g = finds;
            while (g->node) { // удаляем повторы
                if (g->node == g->next->node)
                    g->next = g->next->next;
                g = g->next;
            }

            while (finds != NULL && finds->node != nullptr) {   // проходимся по результату поиска и добавляем
                if (finds->node->childrens != nullptr) {        // дочерние элементы
                    Node *bf = finds->node->childrens;
                    while (bf->next != nullptr) {
                        bf = bf->next;
                    }
                    bf->next = new Node;
                    bf->next->id = digit;
                    bf->next->weight = weight;
                } else {
                    Node *b = new Node;
                    b->id = digit;
                    b->weight = weight;
                    finds->node->childrens = b;
                }
                if (finds->next != nullptr)
                    finds = finds->next;
                else
                    break;
            }
        }
    }

    findNode *find(int target, Node *cRoot, findNode *buffNode) { // функция поиска элемента в дереве
        if (buffNode == NULL)
            return nullptr;
        if (cRoot->id == target) { // если элемент является тем, что ищем, добавляем его в вектор
            buffNode->node = cRoot;
            findNode *b = new findNode;
            buffNode->next = b;
            buffNode = buffNode->next;
        }
        if (cRoot->childrens != nullptr) { // если у элемента есть дочерние, то создаем рекурсию для поиска внутри них
            Node *buff = cRoot->childrens;
            if (buff->id == target) { // если нашли, то добавляем его в наш вектор найденных
                findNode *b = new findNode;
                buffNode->node = buff;
                buffNode->next = b;
                buffNode = buffNode->next;
            }
            if (buff->childrens != nullptr)
                buffNode = find(target, buff, buffNode);
            while (buff->next != nullptr) { // проходимся по дочерним
                buff = buff->next;
                if (buff->id == target) { // добавляем в вектор
                    findNode *b = new findNode;
                    buffNode->node = buff;
                    buffNode->next = b;
                    buffNode = buffNode->next;
                }
                if (buff->childrens != nullptr) {
                    buffNode = find(target, buff, buffNode);
                }
            }
        } else {
            cRoot->childrens = new Node; // если дочерних нет, то просто добавляем
            buffNode->node = cRoot->childrens;
            buffNode->next = new findNode;
            buffNode = buffNode->next;
        }
        return buffNode;
    }

    void echo(Node *buff, int i) { // функция вывода дерева
        buff = buff->childrens;
        Node *nd = buff;
        if (nd == NULL)
            return;
        if (i == 0)
            cout << root->id << endl;
        i++;
        for (int j = 0; j < i; j++)
            cout << "--";
        cout << buff->id << " (" << buff->weight << ")" << endl;
        echo(buff, i);
        while (buff->next != nullptr) {
            buff = buff->next;
            for (int j = 0; j < i; j++)
                cout << "--";
            cout << buff->id << " (" << buff->weight << ")" << endl;
            echo(buff, i);
        }
    }

    void findWay(string path, int weight, Node *buff, int target) { // функция поиска кратчайшего пути
        Node *currentBuff=buff;
        if (buff->id == target) { // если нашли элемент
            if(weight<searchResult or searchResult==-1){ // если текущая длина меньше того, что уже нашли
                searchResult=weight;
                resultPath=path;
            }
        }
        if (buff->childrens != nullptr) {
            buff = buff->childrens;
            while (buff != nullptr) {
                findWay(path + "/" + std::to_string(buff->id), weight + buff->weight, buff, target);
                buff = buff->next;
            }
        }
        if(currentBuff==root){
            cout<<"Кратчайший путь: "<<resultPath<<"\nДлина: "<<searchResult;
        }
    }
};
