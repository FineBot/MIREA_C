#include <iostream>

using namespace std;

class tree { // ����� ������
private:
    struct Node { // ��������� ����
        float data = -1;
        Node *next;
        Node *childrens = nullptr;
    };
    struct findNode {
        Node *node = nullptr;
        findNode *next = nullptr;
    };

public:
    Node *root = nullptr; // ������ ����

    void add(float digit, float parent) { // ������� ���������� ���� � ������
        Node *buff = root;
        if (buff == nullptr) { // ���� �������� ���� �� ����������, �� ������� ���
            root = new Node;
            root->data = digit;
            cout<<1;
        } else {
            findNode *finds=new findNode;
            find(parent,root,finds);
            while(finds->node!= nullptr){
                if(finds->node->childrens!= nullptr){
                    Node *bf = finds->node->childrens;
                    cout<<endl<<bf->data;

                    while(bf->next!= nullptr)
                        bf=bf->next;
                    bf->next=new Node;
                    bf->next->data=digit;
                }
                finds=finds->next;
            }
        }
    }

    int find(float target, Node *cRoot, findNode *currentFindNode) { // ������� ������ �������� � ������
        int i = 0;
        if (cRoot->childrens != nullptr) {
            Node *buff=cRoot->childrens;
            if(buff->data==target){
                currentFindNode->next=new findNode;
                currentFindNode->node=buff;
                currentFindNode=currentFindNode->next;
            }
            if(buff->childrens!= nullptr)
                find(target,buff,currentFindNode);
            while(buff->next!= nullptr){
                buff=buff->next;
                if(buff->data==target){
                    currentFindNode->next=new findNode;
                    currentFindNode->node=buff;
                    currentFindNode=currentFindNode->next;
                }
                if(buff->childrens!= nullptr)
                    find(target,buff,currentFindNode);
            }
        }else{

        }

    }
};


