#include <iostream>
#include <bitset>
#include <cstdlib>
#include <fstream>

#include <string>
using namespace std;


int a1() {
    unsigned int x = 255; //8-��������� �������� ����� 11111111
    unsigned int maska = 1; //1=00000001 � 8-��������� �����
    x = x & (~(maska << 4)); //��������� x=239
    return x;
}

int b1() {
    unsigned int maska = 1; // ������ �����
    unsigned int digit = 128; // �����, 7 ��� �������� ���� ���������� � 1
    return (maska << 7) | digit; // ��������������� ����� � ���� 100000000 � ������ ��������� <<���>>
}

void c1() {
    unsigned int x = 25;
    const int n = sizeof(int) * 8;
    unsigned maska = (1 << n - 1);
    cout << "��������� ��� �����: " << bitset<n>(maska) << endl;
    cout << "���������: ";
    for (int i = 1; i <= n; i++) {
        cout << ((x & maska) >> (n - i));
        maska = maska >> 1;
    }
    cout << endl; // ��������� -- �����, �������������� � �������� ��
}

void a2() {
    cout << "\n������� 2.a";
    unsigned bitArray = 0; // ������� ������
    ifstream fin("C:\\Users\\kiril\\CLionProjects\\MIREA\\SIAOD\\2.1\\2.a.txt"); // ������� ���� ��� ������
    for (int i = 0; i < 8; i++) { // ������ ���� �� ������
        int buff;
        fin >> buff;
        bitArray = bitArray | (1 << buff); // ������������� �������� ������� � �������������� ������
    }
    cout << "\n��������������� ������: ";
    for (int i = 0; i < 8; i++) { // ��������� ������, ������ ������� �� �������� �������
        if (bitset<8>(bitArray)[i])
            cout << i << " ";
    }
}

void b2() {
    cout << "\n\n������� 2.�";

    ofstream o("C:\\Users\\kiril\\CLionProjects\\MIREA\\SIAOD\\2.1\\2.�.txt"); // ��������� ����...
    for (int i = 0; i < 64; i++) {
        o << rand() % 64 << " "; // ...���������� �������
    }
    o.close();

    unsigned long long bitArray = 0;
    ifstream fin("C:\\Users\\kiril\\CLionProjects\\MIREA\\SIAOD\\2.1\\2.�.txt"); // ������ �� �����
    cout << "\n�������� ������: ";

    for (int i = 0; i < 64; i++) {
        int buff;
        fin >> buff;
        cout << buff << " ";
        unsigned long long b = 1; // ���������� ��� ��������� �������
        bitArray = bitArray | (b << (buff)); // ������������� �������� ������� � �������������� ������
    }
    cout << "\n��������������� ������: ";
    fin.close();
    for (int i = 0; i < 64; i++) {
        if (bitset<64>(bitArray)[i] == 1)
            cout << i << " ";
    }
}

void c2() {
    cout << "\n\n������� 2.�";

    ofstream o("C:\\Users\\kiril\\CLionProjects\\MIREA\\SIAOD\\2.1\\2.�.txt"); // ��������� ���� ����������
    for (int i = 0; i < 64; i++) {                                                      // �������
        o << rand() % 64 << " ";
    }
    o.close();

    int *bitArray = new int[2];
    ifstream fin("C:\\Users\\kiril\\CLionProjects\\MIREA\\SIAOD\\2.1\\2.�.txt"); // ������ ����
    cout << "\n�������� ������: ";

    for (int i = 0; i < 64; i++) {
        int buff;
        fin >> buff;
        cout << buff << " ";
        bitArray[buff/32] = (bitArray[buff/32] | (1<<(32-buff%32)));
    }
    fin.close();
    cout << "\n��������������� ������: ";
    for (int i = 0; i < 2; i++) {
        for(int j =0;j<32;j++){
            if (bitset<32>(bitArray[i])[j]==1){
                cout<< to_string((32*i+j)) << " ";
            }
        }
    }
}

void a3() {
    cout<<"\n\n������� 3.�\n��������� ���� ���������� �������.";
//    ofstream o("C:\\Users\\kiril\\CLionProjects\\MIREA\\SIAOD\\2.1\\3.�.txt"); // ��������� ����
//    for (int i = 0; i < pow(10,7); i++) {
//        o << abs((rand()*1000000)%9999999) << " "; // ��������� ��������� �����
//    }
//    o.close();

    cout << "\n�������� ����������.";
    int startTime = time(0); // ���������� ����� ������ ����������
    int *bitArray = new int[312500]; // �������������� ������� ������, �������� 10^7
    ifstream in("C:\\Users\\kiril\\CLionProjects\\MIREA\\SIAOD\\2.1\\3.�.txt"); // ������ ����
    string buff = ""; //  ���������� ��� ������ ������ �����
    int bfint=0;
    getline(in,buff); // ������ ���� ����
    for (int i = 0; i < buff.length(); i++) {
        if(buff[i]==' '){ // ���������� �� ������. ���� ��������� ������, �� � ���������� bfint ���������� ������ �����
            bitArray[bfint/32] = (bitArray[bfint/32] | (1<<(32-bfint%32)));

            bfint=0;
        }
        else{ // ���� ������ �� �������� ����������, �� ��������� ����� ������
            if(bfint==0)
                bfint=buff[i]-48;
            else
                bfint=bfint*10+buff[i]-48;
        }
    }
    in.close();
    cout<< "\n��������� ���� �� "<<time(0)-startTime<<"�.";
    ofstream of("C:\\Users\\kiril\\CLionProjects\\MIREA\\SIAOD\\2.1\\3.�.sort.txt"); // ���������� ��������� � ����
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
    cout << "\n���������� ��������. ����� ����������: "<<time(0)-startTime<<"�.";
    cout<<"\n������ �������� �������: "<<(4*312500)/1024/1024<<" ��.";
}

int main() {
    srand(time(0));
    setlocale(LC_ALL, "rus");
    cout << "1.�: " << a1() << "\n";
    cout << "\n1.�: " << b1() << "\n";
    cout << "\n1.�:\n";
    c1();
    a2();
    b2();
    c2();
    a3();


    return 0;
}



