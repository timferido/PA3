#include <fstream>
#include <vector>
#include <iostream>
#include "HCTree.h"

using namespace std;

int main(int argc, char* argv[]) {

    //declarations 
    ifstream in;
    ofstream out;
    unsigned char charNext;
    vector<int> freqs(256,0);

    //read the bytes from the file
    in.open(argv[1]);
    while (1) {
      charNext = in.get();
      if (in.eof()) break;

      //update frequency
      freqs[(int)charNext]++;

      cout << charNext << "#";
    }
    cout << endl;
    in.close();

    //construct the huffman tree
    HCTree tree;
    tree.build(freqs);

    //open output file
    out.open(argv[2]);

    //write header to output file
    for (int i = 0; i < freqs.size(); i++) {
        out << freqs[i] << endl;
    }

    //open input file again
    in.open(argv[1]);

    //encode each byte and append to output file
    while (1) {
        charNext = in.get();
        if (in.eof()) break;

        tree.encode(charNext, out);
    }

    //close both input and output files
    in.close();
    out.close();

    return 0;
}