#include <iostream>
#include <string>

using namespace std;

class tree { // ����� ������
private:
    struct Node { // ��������� ����
        int id = -1;
        int weight = -1;
        Node *next = nullptr;
        Node *childrens = nullptr;
    };
    struct findNode { // ��������� ���� ��� ������
        Node *node = nullptr;
        findNode *next = nullptr;
    };

    int searchResult = -1;
    string resultPath = "";
public:
    Node *root = nullptr; // ������ ����

    void add(int digit, int parent, int weight) { // ������� ���������� ���� � ������
        Node *buff = root;
        if (buff == nullptr) { // ���� �������� ���� �� ����������, �� ������� ���
            root = new Node;
            root->id = digit;
            root->weight = weight;
        } else if (buff->childrens == nullptr) { // ���� �� ����� �������� ���������
            Node *b = new Node;
            b->id = digit;
            b->weight = weight;
            root->childrens = b;
        } else {
            findNode *finds = new findNode; // ���� ��� �������� � ������, id ������� ����� ���������
            find(parent, root, finds);

            findNode *g = finds;
            while (g->node) { // ������� �������
                if (g->node == g->next->node)
                    g->next = g->next->next;
                g = g->next;
            }

            while (finds != NULL && finds->node != nullptr) {   // ���������� �� ���������� ������ � ���������
                if (finds->node->childrens != nullptr) {        // �������� ��������
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

    findNode *find(int target, Node *cRoot, findNode *buffNode) { // ������� ������ �������� � ������
        if (buffNode == NULL)
            return nullptr;
        if (cRoot->id == target) { // ���� ������� �������� ���, ��� ����, ��������� ��� � ������
            buffNode->node = cRoot;
            findNode *b = new findNode;
            buffNode->next = b;
            buffNode = buffNode->next;
        }
        if (cRoot->childrens != nullptr) { // ���� � �������� ���� ��������, �� ������� �������� ��� ������ ������ ���
            Node *buff = cRoot->childrens;
            if (buff->id == target) { // ���� �����, �� ��������� ��� � ��� ������ ���������
                findNode *b = new findNode;
                buffNode->node = buff;
                buffNode->next = b;
                buffNode = buffNode->next;
            }
            if (buff->childrens != nullptr)
                buffNode = find(target, buff, buffNode);
            while (buff->next != nullptr) { // ���������� �� ��������
                buff = buff->next;
                if (buff->id == target) { // ��������� � ������
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
            cRoot->childrens = new Node; // ���� �������� ���, �� ������ ���������
            buffNode->node = cRoot->childrens;
            buffNode->next = new findNode;
            buffNode = buffNode->next;
        }
        return buffNode;
    }

    void echo(Node *buff, int i) { // ������� ������ ������
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

    void findWay(string path, int weight, Node *buff, int target) { // ������� ������ ����������� ����
        Node *currentBuff=buff;
        if (buff->id == target) { // ���� ����� �������
            if(weight<searchResult or searchResult==-1){ // ���� ������� ����� ������ ����, ��� ��� �����
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
            cout<<"���������� ����: "<<resultPath<<"\n�����: "<<searchResult;
        }
    }
};
