#include <iostream>

using namespace std;

class tree { // класс дерева
private:
    struct Node { // структура узла
        int id = -1;
        int weight=-1;
        Node *next = nullptr;
        Node *childrens = nullptr;
    };
    struct findNode {
        Node *node = nullptr;
        findNode *next = nullptr;
    };

public:
    Node *root = nullptr; // первый узел

    void add(int digit, int parent, int weight) { // функция добавления узла в дерево
        Node *buff = root;
        if (buff == nullptr) { // если корневой узел не существует, то создаем его
            root = new Node;
            root->id = digit;
            root->weight=weight;
        } else if (buff->childrens == nullptr) {
            Node *b = new Node;
            b->id = digit;
            b->weight=weight;
            root->childrens = b;
        } else {
            findNode *finds = new findNode;
            find(parent, root, finds);

            findNode *g = finds;
            while (g->node) {
                if (g->node == g->next->node)
                    g->next = g->next->next;
                g = g->next;
            }

            while (finds != NULL && finds->node != nullptr) {
                if (finds->node->childrens != nullptr) {
                    Node *bf = finds->node->childrens;
                    while (bf->next != nullptr) {
                        bf = bf->next;
                    }

                    bf->next = new Node;
                    bf->next->id = digit;
                    bf->next->weight=weight;
                } else {
                    Node *b = new Node;
                    b->id = digit;
                    b->weight=weight;
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
        if (cRoot->id == target) {
            buffNode->node = cRoot;
            findNode *b = new findNode;
            buffNode->next = b;
            buffNode = buffNode->next;
        }
        if (cRoot->childrens != nullptr) {
            Node *buff = cRoot->childrens;
            if (buff->id == target) {
                findNode *b = new findNode;
                buffNode->node = buff;
                buffNode->next = b;
                buffNode = buffNode->next;
            }
            if (buff->childrens != nullptr)
                buffNode = find(target, buff, buffNode);
            while (buff->next != nullptr) {
                buff = buff->next;
                if (buff->id == target) {
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
            cRoot->childrens = new Node;
            buffNode->node = cRoot->childrens;
            buffNode->next = new findNode;
            buffNode = buffNode->next;
        }
        return buffNode;
    }

    void echo(Node *buff, int i) {
        buff = buff->childrens;
        Node *nd = buff;
        if (nd == NULL)
            return;
        if (i == 0)
            cout << root->id << endl;
        i++;
        for (int j = 0; j < i; j++)
            cout << "--";
        cout << buff->id << endl;
        echo(buff, i);
        while (buff->next != nullptr) {
            buff = buff->next;
            for (int j = 0; j < i; j++)
                cout << "--";
            cout << buff->id << endl;
            echo(buff, i);
        }
    }
};
