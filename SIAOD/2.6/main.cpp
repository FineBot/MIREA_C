#include "Shennon.cpp"
#include "Huffman.cpp"
using namespace std;

int main() {

//    string data;
//    getline(cin,data);
//    Shennon *sh = new Shennon(data);

//    Shennon *sh1 = new Shennon();
//    sh1->decodeFile("C:\\Users\\kiril\\CLionProjects\\MIREA\\SIAOD\\2.6\\test");


    string data;
    getline(cin,data);
    Huffman *hf = new Huffman(data);


    return 0;
}