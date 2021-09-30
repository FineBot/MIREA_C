#include <iostream>

using namespace std;

int linearSearch(string first, string second) {
    int startIndex = 0; // переменная сдвига
    while (startIndex + second.length() < first.length()) { // пока сдвиг + длина подстроки меньше длины самой строки
        bool find = true; // нашли ли мы слово

        for (int i = 0; i < second.length(); i++) { // проходимся по подстроке
            if (first[startIndex + i] != second[i]) { // сравниваем симолы подстроки и строки с учетом сдвига
                startIndex++; // если символы не равны -- увеличиваем сдвиг
                find = false; // соответственно подстрока не найдена
                break;
            }
        }
        if (find)
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
            if (text[i] == text[j]) // если встречался, то ставим соответсвующее значение сдвига
                lastEl = result[j];
        }
        if (lastEl >= 1)
            result[i] = lastEl;
    }
    bool set = false;
    for (int i = 0; i < text.length() - 2; i++) { // ищем, встречался ли первый с конца символ в слове
        if (text[i] == text[text.length() - 1]) { // если да, ставим соответствующий сдвиг
            result[text.length() - 1] = result[i];
            set = true;
            break;
        }
    }
    if (!set) // если не встречался, то ставим длину слова
        result[text.length() - 1] = text.length();
    return result;
}

int BMSearch(string first, string second) { // алгоритм поиска Бойера-Мура-Хорспула
    int *shift = shiftArray(second); // сдвиговый массив
    int startIndex=0; // сдвиг
    int lastIndex=-1;
    while (startIndex + second.length() < first.length()) { // пока сдвиг + длина подстроки меньше длины строки
        bool find = true;

        for (int i = second.length()-1; i >=0; i--) { // сравниваем строки начиная с конца подстроки
            if (first[startIndex + i] != second[i]) { // если символы не совпадают
                bool findShift=false;
                for(int k = 0;k<second.length();k++){ // ищем на сколько необходимо сместить
                    if(second[k]==first[startIndex+i]){
                        startIndex+=shift[k]; // смещаем
                        findShift=true;
                        break;
                    }
                }
                if(!findShift) // если не нашли букву в подстроке, то смещаем на длину всей подстроки
                    startIndex+=second.length();

                find = false;
                break;
            }
        }
        if (find){ // если нашли, то сохраняем последний найденный индекс
            lastIndex= startIndex;
            startIndex++;
        }

    }
    return lastIndex;
}

int main() {
    cout << linearSearch("Lorem ipsum dolor sit amet, consectetur adipiscing "
                         "elit, sed do eiusmod tempor incididunt "
                         "ut labore et dolore magna aliqua.", "sit");
    cout << endl<<endl;
    cout <<BMSearch("sit Lorem ipsum dolor sit amet, consectetur adipiscing "
                    "elit, sed do eiusmod tempor incididunt "
                    "ut labore et dolore magna aliqua.", "sit");
    return 0;
}