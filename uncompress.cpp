/*
 *                                                        Tim Ferido
 *                                                        Kent Nguyen
 *                                                        CSE 100, Fall 2017
 *                                                        November 9, 2017
 *                                                        A12880086 
 *                                                        A12164917
 *                        Programming Assignment Three
 * File Name:    uncompress.cpp
 * Description:  Unompresses an input file to an output file using a Huffman
 *               Code Tree.
 */ 
#include <fstream>
#include <vector>
#include <iostream>
#include "HCTree.h"
#include <string>
#include <bitset>

using namespace std;

int main(int argc, char* argv[]) 
{
    //Declarations 
    ifstream in;
    ofstream out;
    int nextChar;
    vector<int> freqs(256,0);
    BitInputStream inBit(in);
    long charCount = 0;
    byte nextByte;

    //Read the header
    in.open(argv[1]);

    while (1) {
        //declarations
        string freqBin;
        int symbolInt, freqInt;

        //read the line number byte
        nextByte = in.get();
        symbolInt = (int)nextByte; //this is the index of freqs[]

        if ((nextByte == '\0' && charCount )) break; //delimiter
        
        //read the freq number (3 bytes)
        for (int i = 0; i < 3; i++) {
            freqBin += std::bitset<8>((int)in.get()).to_string();
        }
        freqInt = stoi(freqBin, nullptr, 2); // convert the binary string to int
        charCount += freqInt; //update the amount of characters to write

        //update freqs vector
        freqs[symbolInt] = freqInt;
    }

    //Construct the huffman tree
    HCTree tree;
    tree.build(freqs);

    //Open output file
    out.open(argv[2]);

    //Decode the string from the input file using the huffman tree
    //Read the encoded string bit by bit
    while (1)
    {
        nextChar = tree.decode(inBit);
        
        if (in.eof() || !charCount) break;
        
        out << (char)nextChar;

        charCount--;
    }

    //Close both input and output files
    in.close();
    out.close();

    return 0;
}