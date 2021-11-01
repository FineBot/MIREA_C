#include <iostream>

using namespace std;

int linearSearch(string first, string second) {
    int startIndex = 0; // переменная сдвига
    while (startIndex + second.length() <= first.length()) { // пока сдвиг + длина подстроки меньше длины самой строки
        int i =0;
        while(first[startIndex + i] == second[i] && i<second.length()-1){ // проходимся по строке и сравниваем символы
            i++;
        }
        if (first[startIndex + i] != second[i]) { // сравниваем симолы подстроки и строки с учетом сдвига
            startIndex++; // если символы не равны -- увеличиваем сдвиг
        }else
            return startIndex; // если найдена, возвращаем индекс первого вхождения;
    }
    return -1;
}

int *shiftArray(string text) { // функция получения сдвигового массива
    int *result = new int[text.length()]; // наш массив

    for (int i = text.length() - 2; i >= 0; i--) { // проходимся по слову с конца
        result[i] = text.length() - i - 1; // устанавливаем номер символа от правого края
        int lastEl = -1;
        for (int j = i + 1; j < text.length() - 1; j++) { // если символ раньше встречался,
            if (text[i] == text[j]) // если встречался, то ставим соответствующее значение сдвига
                lastEl = result[j];
        }
        if (lastEl >= 1)
            result[i] = lastEl;
    }
    int i =0;
    while(i<text.length()-2 && text[i] != text[text.length() - 1]){ // проверяем, есть ли символ в нашей подстроке
        i++;
    }
    if (text[i] == text[text.length() - 1]) { // если есть, ставим соответствующий сдвиг
        result[text.length() - 1] = result[i];
    }else // если не встречался, то ставим длину слова
        result[text.length() - 1] = text.length();

    return result;
}

int BMSearch(string first, string second) { // алгоритм поиска Бойера-Мура-Хорспула
    int *shift = shiftArray(second); // сдвиговый массив
    int startIndex=0; // сдвиг
    int lastIndex=-1;
    while (startIndex + second.length() <= first.length()) { // пока сдвиг + длина подстроки меньше длины строки
        int i =second.length()-1;
        while(i >0 && first[startIndex + i] == second[i]){ // сравниваем строки начиная с конца подстроки
            i--;
        }
        if (first[startIndex + i] != second[i]) { // если символы не совпадают
            int k =0;
            while(k<second.length()-1 && second[k]!=first[startIndex+i]){ // ищем на сколько необходимо сместить
                k++;
            }
            if(second[k]==first[startIndex+i]){
                startIndex+=shift[k]; // смещаем
            } else // если не нашли букву в подстроке, то смещаем на длину всей подстроки
                startIndex+=second.length();

        }else{ // если нашли, то сохраняем последний найденный индекс
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
    cout << endl<<"Время работы: "<<time(0)-t;
    cout << endl<<endl;

    cin>>text;
    cin>>text2;
    t = time(0);
    cout <<BMSearch(text, text2);
    cout << endl<<"Время работы: "<<time(0)-t;

    return 0;
}