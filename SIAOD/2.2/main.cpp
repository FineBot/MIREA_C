#include <iostream>
#include <Windows.h>
#include "table.cpp";
using namespace std;

int main() {
    setlocale(LC_ALL,"rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    tableClass tb;
    tb.pushToArray(123,"Молоко",54);
    tb.pushToArray(124,"Хлеб",50);
    tb.pushToArray(125,"Кефир",70);
    tb.pushToArray(126,"Помидоры",82);
    tb.pushToArray(131,"Морковь",999999);
    tb.pushToArray(130,"Лук",3);

    cout <<"Исходный массив:\n";
    cout << tb.toString();

    cout <<"\nПосле удаления:\n";
    tb.del(124);
    cout << tb.toString();

    cout <<"\nПример поиска:\n";
    tableItem buff = tb.search(125);
    cout << buff.code<<". "<<buff.name<<": "<<buff.price;

    return 0;
}
