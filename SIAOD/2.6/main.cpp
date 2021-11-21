#include "Shennon.cpp"
#include "Huffman.cpp"
using namespace std;

int main() {

//    // Читаем из консоли строку и кодируем ее Шенноном
    string data;
//    getline(cin,data);
//    Shennon *sh = new Shennon(data);
//
//    // Кодируем и декодируем файл Шенноном
//    Shennon *sh1 = new Shennon();
//    sh1->encodeFile("C:\\Users\\kiril\\CLionProjects\\MIREA\\SIAOD\\2.6\\test");
//    sh1->decodeFile("C:\\Users\\kiril\\CLionProjects\\MIREA\\SIAOD\\2.6\\test");

    // Читаем из консоли и кодируем строку алгоритмом Хаффмана
    getline(cin,data);
    string params;
    getline(cin,params);
    Huffman *hf = new Huffman();
    hf->decodeString(data,
                     params);

//    1100001100010111110110101101100101000101001001110110111110100000000101010001000011100111001
//"и:01;л:001;н:1010;в:1110; :1101;е:0000;г:10000;ь:10001;ч:11001;Е:1011;р:0001;К:1001;к:1111;а:110001;Б:110000;"

    return 0;
}