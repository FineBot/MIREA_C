#include <iostream>
using namespace std;
class tree { // класс дерева
private:
    struct Node { // структура узла
        float data = -1;
        Node *right = nullptr;
        Node *left = nullptr;
    };
    struct buffAverage { // структура узла для поиска среднего
        float sum = 0;
        int count = 0;
    };
public:
    Node *root = nullptr; // первый узел
    void add(float digit) { // функция добавления узла в дерево
        Node *buff = root;
        if (buff == nullptr) { // если корневой узел не существует, то
            root = new Node;
            root->data = digit;
        } else {
            Node *lastBuff = buff;
            while (buff->right != nullptr or buff->left != nullptr) { //
                lastBuff = buff;
                if (digit > buff->data) { // если данные в текущем узле
                    if (buff->right != nullptr)
                        buff = buff->right;
                    else
                        break;
                } else if (digit < buff->data) { // иначе идем в левую
                    if (buff->left != nullptr)
                        buff = buff->left;
                    else
                        break;
                } else { // если встречаем узел с такими же данными, то
                    buff= nullptr;
                    break;
                }
            }
            if(buff!=nullptr){
                if (buff->data < digit) { // если данные в узле больше, то
                    buff->right = new Node;
                    buff->right->data = digit;
                } else { // иначе добавляем слева
                    buff->left = new Node;
                    buff->left->data = digit;
                }
            }
        }
    }
    void echo(Node *node, int i = 0) { // функция вывода дерева
        for (int j = 0; j < i; j++) { // генерация отступов
            cout << " ";
        }
        cout << node->data << endl; // выводим значение узла
        i++;
        if (node->left != nullptr) { // проходимся по левой ветке
            echo(node->left, i); // вызываем рекурсию
        }
        if (node->right != nullptr) { // иначе по правой
            echo(node->right, i); // вызываем рекурсию
        }
    }
    float findAverageLogic(Node *node, buffAverage *buff) { // функция
        buff->sum += node->data; // суммирование с текущим узлом
        buff->count++; // подсчет количества узлов в дереве
        if (node->left != nullptr) { // проходимя по левой ветке
            buff->sum = findAverageLogic(node->left, buff); // рекурсия
        }
        if (node->right != nullptr) { // проходимся по правой ветке
            buff->sum = findAverageLogic(node->right, buff); // рекурсия
        }
        return buff->sum; // возврат
    }
    float findAverage() { // функция поиска среднего значения всех узлов
        buffAverage *bf = new buffAverage;
        findAverageLogic(this->root, bf);
        return bf->sum / bf->count;
    }
    int find(float target) { // функция поиска элемента в дереве
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
void createTree(tree* tr){ // функция создания дерева
    cout << "Формирование дерева осуществляется до ввода числа -100\nВводите числа: ";
    float buff;
    cin>>buff;
    while(buff!=-100){
        tr->add(buff);
        cin>>buff;
    }
}
void menu(tree* tr){ // функция вывода меню
    cout << "1. Заполнение дерева\n2. Вычисление среднего\n3. Поиск количества путей от корня\n4. Вывод дерева\n";
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
            cout<<"\nВведите число: ";
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