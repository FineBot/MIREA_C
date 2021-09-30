#include <iostream>
#include <string>

using namespace std;

struct tableItem {
    int code = NULL;
    string name;
    int price = NULL;
};

class tableClass {
private:

    int k = 32;
    double mod = 5, n = 0;
    tableItem *Table = new tableItem[mod];

    int h(int digit) {
        int buff = digit;
        int result = 0;
        int m = 1;
        while (buff > 0) {
            result = (result + m * (buff % 10)) % static_cast<int>(mod);
            m = (m * k) % static_cast<int>(mod);
            buff = buff / 10;
        }
        return result;
    }

    int reHash(int hash, int i) {
        return (hash + i * i * k) % static_cast<int>(mod);
    }

    void regenArray(int newMod) {
        int lastMod = mod;
        mod = newMod;
        tableItem *buff = new tableItem[newMod];
        for (int i = 0; i < lastMod; i++) {
            if (Table[i].code != NULL) {
                int hash = h(Table[i].code);
                int ijj = 1;
                while (buff[hash].code != NULL) {
                    hash = reHash(hash, ijj);
                    ijj++;
                }
                buff[hash] = Table[i];
            }
        }
        Table = buff;
    }

public:

    bool pushToArray(int code, string name, int price) {
        n++;
        if (n / mod > 0.75)
            regenArray(mod * 2);
        int hash = h(code);
        int i = 1;
        while (Table[hash].code != NULL) {
            hash = reHash(hash, i);
            i++;
        }
        Table[hash].price = price;
        Table[hash].name = name;
        Table[hash].code = code;
        return true;
    }

    bool del(int code) {
        n--;
        int hash = h(code);
        int i = 1;
        while (Table[hash].code != code && Table[hash].code != NULL) {
            hash = reHash(hash, i);
            i++;
        }
        Table[hash].code = NULL;
        Table[hash].price = NULL;
        Table[hash].name = "";
        if (n / mod < 0.25)
            regenArray((mod / 2) + 1);
        return true;
    }

    tableItem search(int code) {
        int hash = h(code);
        int i = 1;
        while (Table[hash].code != code && Table[hash].code != NULL) {
            hash = reHash(hash, i);
            i++;
        }
        return Table[hash];
    }

    string toString() {
        string buff = "";
        for (int i = 0; i < mod; i++)
            if (Table[i].code != NULL)
                buff = buff + "i: " + to_string(i) + "; " + to_string(Table[i].code) + ". " + Table[i].name + ": " +
                       to_string(Table[i].price) + "\n";
        return buff;
    }
};