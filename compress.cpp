/*
 *                                                        Tim Ferido
 *                                                        Kent Nguyen
 *                                                        CSE 100, Fall 2017
 *                                                        November 9, 2017
 *                                                        A12880086 
 *                                                        A12164917
 *                        Programming Assignment Three
 * File Name:    compress.cpp
 * Description:  Compresses an input file to an output file using a Huffman
 *               Code Tree.
 */ 
#include <fstream>
#include <vector>
#include <iostream>
#include "HCTree.h"

using namespace std;

int main(int argc, char* argv[]) 
{
    //Declarations 
    ifstream in;
    ofstream out;
    unsigned char charNext;
    vector<int> freqs(256,0);
    BitOutputStream outBit(out);
    

    //Read the bytes from the file
    in.open(argv[1]);
    while (1) 
    {
      charNext = in.get();
      if (in.eof()) break;

      //Update frequency vector
      freqs[(int)charNext]++;

      cout << charNext << "#";
    }
    cout << endl;
    in.close();
    
    //Construct the huffman tree
    HCTree tree;
    tree.build(freqs);

    //Open output file
    out.open(argv[2]);

    //Write header to output file
    for (int i = 0; i < freqs.size(); i++) {
        out << freqs[i] << endl;
    }

    //Open input file again
    in.open(argv[1]);

    //Encode each byte and append to output file
    while (1) 
    {
        charNext = in.get();
        
        if (in.peek() == -1) 
        {
            
        }

        tree.encode(charNext, outBit);
    }

    outBit.flush();
    
    //Close both input and output files
    in.close();
    out.close();

    return 0;
}