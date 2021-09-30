#include <iostream>
#include <Windows.h>
#include "table.cpp";
using namespace std;

int main() {
    setlocale(LC_ALL,"rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    tableClass tb;
    tb.pushToArray(123,"������",54);
    tb.pushToArray(124,"����",50);
    tb.pushToArray(125,"�����",70);
    tb.pushToArray(126,"��������",82);
    tb.pushToArray(131,"�������",999999);
    tb.pushToArray(130,"���",3);

    cout <<"�������� ������:\n";
    cout << tb.toString();

    cout <<"\n����� ��������:\n";
    tb.del(124);
    cout << tb.toString();

    cout <<"\n������ ������:\n";
    tableItem buff = tb.search(125);
    cout << buff.code<<". "<<buff.name<<": "<<buff.price;

    return 0;
}
