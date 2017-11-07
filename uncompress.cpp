#include <fstream>
#include <vector>
#include <iostream>
#include "HCTree.h"

using namespace std;

int main(int argc, char* argv[]) {

    //declarations 
    ifstream in;
    ofstream out;
    int nextChar;
    vector<int> freqs(256,0);

    //read the bytes from the file
    in.open(argv[1]);
    for (int i = 0; i < 256; i++) {
        string nextFreq;
        unsigned char digit;
        while (1) {
            digit = in.get();
            if (digit == '\n') break;
            nextFreq += digit;
        }
        freqs[i] = stoi(nextFreq);
    }
    
    //construct the huffman tree
    HCTree tree;
    tree.build(freqs);

    //open output file
    out.open(argv[2]);

    //decode the string from the input file using the huffman tree
    //read the encoded string bit by bit
    do {
        nextChar = tree.decode(in);
        out << (char)nextChar;
    }
    while (nextChar);

    //close both input and output files
    in.close();
    out.close();

    return 0;
}