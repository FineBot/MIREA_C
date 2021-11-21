#include <iostream>
using namespace std;
class tree { // ����� ������
private:
    struct Node { // ��������� ����
        float data = -1;
        Node *right = nullptr;
        Node *left = nullptr;
    };
    struct buffAverage { // ��������� ���� ��� ������ ��������
        float sum = 0;
        int count = 0;
    };
public:
    Node *root = nullptr; // ������ ����
    void add(float digit) { // ������� ���������� ���� � ������
        Node *buff = root;
        if (buff == nullptr) { // ���� �������� ���� �� ����������, ��
            root = new Node;
            root->data = digit;
        } else {
            Node *lastBuff = buff;
            while (buff->right != nullptr or buff->left != nullptr) { //
                lastBuff = buff;
                if (digit > buff->data) { // ���� ������ � ������� ����
                    if (buff->right != nullptr)
                        buff = buff->right;
                    else
                        break;
                } else if (digit < buff->data) { // ����� ���� � �����
                    if (buff->left != nullptr)
                        buff = buff->left;
                    else
                        break;
                } else { // ���� ��������� ���� � ������ �� �������, ��
                    buff= nullptr;
                    break;
                }
            }
            if(buff!=nullptr){
                if (buff->data < digit) { // ���� ������ � ���� ������, ��
                    buff->right = new Node;
                    buff->right->data = digit;
                } else { // ����� ��������� �����
                    buff->left = new Node;
                    buff->left->data = digit;
                }
            }
        }
    }
    void echo(Node *node, int i = 0) { // ������� ������ ������
        for (int j = 0; j < i; j++) { // ��������� ��������
            cout << " ";
        }
        cout << node->data << endl; // ������� �������� ����
        i++;
        if (node->left != nullptr) { // ���������� �� ����� �����
            echo(node->left, i); // �������� ��������
        }
        if (node->right != nullptr) { // ����� �� ������
            echo(node->right, i); // �������� ��������
        }
    }
    float findAverageLogic(Node *node, buffAverage *buff) { // �������
        buff->sum += node->data; // ������������ � ������� �����
        buff->count++; // ������� ���������� ����� � ������
        if (node->left != nullptr) { // ��������� �� ����� �����
            buff->sum = findAverageLogic(node->left, buff); // ��������
        }
        if (node->right != nullptr) { // ���������� �� ������ �����
            buff->sum = findAverageLogic(node->right, buff); // ��������
        }
        return buff->sum; // �������
    }
    float findAverage() { // ������� ������ �������� �������� ���� �����
        buffAverage *bf = new buffAverage;
        findAverageLogic(this->root, bf);
        return bf->sum / bf->count;
    }
    int find(float target) { // ������� ������ �������� � ������
        Node *buff = root;
        int i = 0;
        while (buff->right != nullptr or buff->left != nullptr) {
            i++;
            if (target > buff->data) {
                if (buff->right != nullptr)
                    buff = buff->right;
                else
                    break;
            } else if (target < buff->data) {
                if (buff->left != nullptr)
                    buff = buff->left;
                else
                    break;
            } else {
                break;
            }
        }
        return i;
    }
};
void createTree(tree* tr){ // ������� �������� ������
    cout << "������������ ������ �������������� �� ����� ����� -100\n������� �����: ";
    float buff;
    cin>>buff;
    while(buff!=-100){
        tr->add(buff);
        cin>>buff;
    }
}
void menu(tree* tr){ // ������� ������ ����
    cout << "1. ���������� ������\n2. ���������� ��������\n3. ����� ���������� ����� �� �����\n4. ����� ������\n";
    int a;
    cin >> a;
    switch (a) {
        case 1:
            createTree(tr);
            break;
        case 2:
            cout << endl <<"Average: "<< tr->findAverage()<<endl;
            break;
        case 3:
            float buff;
            cout<<"\n������� �����: ";
            cin>>buff;
            cout << endl <<"Count: "<< tr->find(buff)<<endl;
            break;
        case 4:
            cout<<"___"<<endl;
            tr->echo(tr->root);
            cout<<"___"<<endl;
            break;
    }
}
int main() {

    for(char i='a';i<'z';i++){
        cout<<i;
    }

    setlocale(LC_ALL, "rus");
    tree tr;
    while(true)
        menu(&tr);
    return 0;
}