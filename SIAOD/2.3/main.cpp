#include <iostream>

using namespace std;

int linearSearch(string first, string second) {
    int startIndex = 0; // ���������� ������
    while (startIndex + second.length() < first.length()) { // ���� ����� + ����� ��������� ������ ����� ����� ������
        bool find = true; // ����� �� �� �����

        for (int i = 0; i < second.length(); i++) { // ���������� �� ���������
            if (first[startIndex + i] != second[i]) { // ���������� ������ ��������� � ������ � ������ ������
                startIndex++; // ���� ������� �� ����� -- ����������� �����
                find = false; // �������������� ��������� �� �������
                break;
            }
        }
        if (find)
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
            if (text[i] == text[j]) // ���� ����������, �� ������ �������������� �������� ������
                lastEl = result[j];
        }
        if (lastEl >= 1)
            result[i] = lastEl;
    }
    bool set = false;
    for (int i = 0; i < text.length() - 2; i++) { // ����, ���������� �� ������ � ����� ������ � �����
        if (text[i] == text[text.length() - 1]) { // ���� ��, ������ ��������������� �����
            result[text.length() - 1] = result[i];
            set = true;
            break;
        }
    }
    if (!set) // ���� �� ����������, �� ������ ����� �����
        result[text.length() - 1] = text.length();
    return result;
}

int BMSearch(string first, string second) { // �������� ������ ������-����-��������
    int *shift = shiftArray(second); // ��������� ������
    int startIndex=0; // �����
    int lastIndex=-1;
    while (startIndex + second.length() < first.length()) { // ���� ����� + ����� ��������� ������ ����� ������
        bool find = true;

        for (int i = second.length()-1; i >=0; i--) { // ���������� ������ ������� � ����� ���������
            if (first[startIndex + i] != second[i]) { // ���� ������� �� ���������
                bool findShift=false;
                for(int k = 0;k<second.length();k++){ // ���� �� ������� ���������� ��������
                    if(second[k]==first[startIndex+i]){
                        startIndex+=shift[k]; // �������
                        findShift=true;
                        break;
                    }
                }
                if(!findShift) // ���� �� ����� ����� � ���������, �� ������� �� ����� ���� ���������
                    startIndex+=second.length();

                find = false;
                break;
            }
        }
        if (find){ // ���� �����, �� ��������� ��������� ��������� ������
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