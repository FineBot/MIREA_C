#include <iostream>

using namespace std;

int linearSearch(string first, string second) {
    int startIndex = 0; // ���������� ������
    while (startIndex + second.length() <= first.length()) { // ���� ����� + ����� ��������� ������ ����� ����� ������
        int i =0;
        while(first[startIndex + i] == second[i] && i<second.length()-1){ // ���������� �� ������ � ���������� �������
            i++;
        }
        if (first[startIndex + i] != second[i]) { // ���������� ������ ��������� � ������ � ������ ������
            startIndex++; // ���� ������� �� ����� -- ����������� �����
        }else
            return startIndex; // ���� �������, ���������� ������ ������� ���������;
    }
    return -1;
}

int *shiftArray(string text) { // ������� ��������� ���������� �������
    int *result = new int[text.length()]; // ��� ������

    for (int i = text.length() - 2; i >= 0; i--) { // ���������� �� ����� � �����
        result[i] = text.length() - i - 1; // ������������� ����� ������� �� ������� ����
        int lastEl = -1;
        for (int j = i + 1; j < text.length() - 1; j++) { // ���� ������ ������ ����������,
            if (text[i] == text[j]) // ���� ����������, �� ������ ��������������� �������� ������
                lastEl = result[j];
        }
        if (lastEl >= 1)
            result[i] = lastEl;
    }
    int i =0;
    while(i<text.length()-2 && text[i] != text[text.length() - 1]){ // ���������, ���� �� ������ � ����� ���������
        i++;
    }
    if (text[i] == text[text.length() - 1]) { // ���� ����, ������ ��������������� �����
        result[text.length() - 1] = result[i];
    }else // ���� �� ����������, �� ������ ����� �����
        result[text.length() - 1] = text.length();

    return result;
}

int BMSearch(string first, string second) { // �������� ������ ������-����-��������
    int *shift = shiftArray(second); // ��������� ������
    int startIndex=0; // �����
    int lastIndex=-1;
    while (startIndex + second.length() <= first.length()) { // ���� ����� + ����� ��������� ������ ����� ������
        int i =second.length()-1;
        while(i >0 && first[startIndex + i] == second[i]){ // ���������� ������ ������� � ����� ���������
            i--;
        }
        if (first[startIndex + i] != second[i]) { // ���� ������� �� ���������
            int k =0;
            while(k<second.length()-1 && second[k]!=first[startIndex+i]){ // ���� �� ������� ���������� ��������
                k++;
            }
            if(second[k]==first[startIndex+i]){
                startIndex+=shift[k]; // �������
            } else // ���� �� ����� ����� � ���������, �� ������� �� ����� ���� ���������
                startIndex+=second.length();

        }else{ // ���� �����, �� ��������� ��������� ��������� ������
            lastIndex= startIndex;
            startIndex++;
        }

    }
    return lastIndex;
}

int main() {
    setlocale(LC_ALL, "rus");

    string text="";
    cin>>text;
    string text2="";
    cin>>text2;
    double t = time(0);
    cout << linearSearch(text, text2);
    cout << endl<<"����� ������: "<<time(0)-t;
    cout << endl<<endl;

    cin>>text;
    cin>>text2;
    t = time(0);
    cout <<BMSearch(text, text2);
    cout << endl<<"����� ������: "<<time(0)-t;

    return 0;
}