#include <iostream>
#include <bitset>
#include <cstdlib>
#include <fstream>

#include <string>
using namespace std;


int a1() {
    unsigned int x = 255; //8-разрядное двоичное число 11111111
    unsigned int maska = 1; //1=00000001 – 8-разрядная маска
    x = x & (~(maska << 4)); //результат x=239
    return x;
}

int b1() {
    unsigned int maska = 1; // шаблон маски
    unsigned int digit = 128; // число, 7 бит которого надо установить в 1
    return (maska << 7) | digit; // преобразовываем маску к виду 100000000 и делаем побитовое <<ИЛИ>>
}

void c1() {
    unsigned int x = 25;
    const int n = sizeof(int) * 8;
    unsigned maska = (1 << n - 1);
    cout << "Начальный вид маски: " << bitset<n>(maska) << endl;
    cout << "Результат: ";
    for (int i = 1; i <= n; i++) {
        cout << ((x & maska) >> (n - i));
        maska = maska >> 1;
    }
    cout << endl; // результат -- число, представленное в двоичной СС
}

void a2() {
    cout << "\nЗадание 2.a";
    unsigned bitArray = 0; // битовый массив
    ifstream fin("C:\\Users\\kiril\\CLionProjects\\MIREA\\SIAOD\\2.1\\2.a.txt"); // открыли файл для чтения
    for (int i = 0; i < 8; i++) { // читаем файл по словам
        int buff;
        fin >> buff;
        bitArray = bitArray | (1 << buff); // устанавливаем значение единицы в соответсвующую ячейку
    }
    cout << "\nОтсортированный массив: ";
    for (int i = 0; i < 8; i++) { // сортируем массив, просто проходя по битовому массиву
        if (bitset<8>(bitArray)[i])
            cout << i << " ";
    }
}

void b2() {
    cout << "\n\nЗадание 2.б";

    ofstream o("C:\\Users\\kiril\\CLionProjects\\MIREA\\SIAOD\\2.1\\2.б.txt"); // заполняем файл...
    for (int i = 0; i < 64; i++) {
        o << rand() % 64 << " "; // ...случайными числами
    }
    o.close();

    unsigned long long bitArray = 0;
    ifstream fin("C:\\Users\\kiril\\CLionProjects\\MIREA\\SIAOD\\2.1\\2.б.txt"); // читаем из файла
    cout << "\nИсходный массив: ";

    for (int i = 0; i < 64; i++) {
        int buff;
        fin >> buff;
        cout << buff << " ";
        unsigned long long b = 1; // переменная для установки единицы
        bitArray = bitArray | (b << (buff)); // устанавливаем значение единицы в соответсвующую ячейку
    }
    cout << "\nОтсортированный массив: ";
    fin.close();
    for (int i = 0; i < 64; i++) {
        if (bitset<64>(bitArray)[i] == 1)
            cout << i << " ";
    }
}

void c2() {
    cout << "\n\nЗадание 2.в";

    ofstream o("C:\\Users\\kiril\\CLionProjects\\MIREA\\SIAOD\\2.1\\2.с.txt"); // заполняем файл случайными
    for (int i = 0; i < 64; i++) {                                                      // числами
        o << rand() % 64 << " ";
    }
    o.close();

    int *bitArray = new int[2];
    ifstream fin("C:\\Users\\kiril\\CLionProjects\\MIREA\\SIAOD\\2.1\\2.с.txt"); // читаем файл
    cout << "\nИсходный массив: ";

    for (int i = 0; i < 64; i++) {
        int buff;
        fin >> buff;
        cout << buff << " ";
        bitArray[buff/32] = (bitArray[buff/32] | (1<<(32-buff%32)));
    }
    fin.close();
    cout << "\nОтсортированный массив: ";
    for (int i = 0; i < 2; i++) {
        for(int j =0;j<32;j++){
            if (bitset<32>(bitArray[i])[j]==1){
                cout<< to_string((32*i+j)) << " ";
            }
        }
    }
}

void a3() {
    cout<<"\n\nЗадание 3.а\nЗаполняем файл рандомными числами.";
//    ofstream o("C:\\Users\\kiril\\CLionProjects\\MIREA\\SIAOD\\2.1\\3.а.txt"); // заполняем файл
//    for (int i = 0; i < pow(10,7); i++) {
//        o << abs((rand()*1000000)%9999999) << " "; // генерация случайных чисел
//    }
//    o.close();

    cout << "\nНачинаем сортировку.";
    int startTime = time(0); // запоминаем время начала сортировки
    int *bitArray = new int[312500]; // инициализируем битовый массив, размером 10^7
    ifstream in("C:\\Users\\kiril\\CLionProjects\\MIREA\\SIAOD\\2.1\\3.а.txt"); // читаем файл
    string buff = ""; //  переменная для чтения чтения файла
    int bfint=0;
    getline(in,buff); // читаем весь файл
    for (int i = 0; i < buff.length(); i++) {
        if(buff[i]==' '){ // проходимся по словам. если встречаем пробел, то в переменной bfint содержится нужное число
            bitArray[bfint/32] = (bitArray[bfint/32] | (1<<(32-bfint%32)));

            bfint=0;
        }
        else{ // если символ не является пробельным, то считываем цифры дальше
            if(bfint==0)
                bfint=buff[i]-48;
            else
                bfint=bfint*10+buff[i]-48;
        }
    }
    in.close();
    cout<< "\nПрочитали файл за "<<time(0)-startTime<<"с.";
    ofstream of("C:\\Users\\kiril\\CLionProjects\\MIREA\\SIAOD\\2.1\\3.а.sort.txt"); // записываем результат в файл
    string bf = "";
    for (int i = 0; i < 312500; i++) {
        for(int j =0;j<32;j++){
            if (bitset<32>(bitArray[i])[j]==1){
                bf+= to_string((i*i+j)) + " ";
            }
        }
    }
    of<<bf;
    of.close();
    cout << "\nСортировка окончена. Время выполнения: "<<time(0)-startTime<<"с.";
    cout<<"\nРазмер битового массива: "<<(4*312500)/1024/1024<<" МБ.";
}

int main() {
    srand(time(0));
    setlocale(LC_ALL, "rus");
    cout << "1.а: " << a1() << "\n";
    cout << "\n1.б: " << b1() << "\n";
    cout << "\n1.в:\n";
    c1();
    a2();
    b2();
    c2();
    a3();


    return 0;
}



