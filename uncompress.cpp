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

using namespace std;

int main(int argc, char* argv[]) 
{
    //Declarations 
    ifstream in;
    ofstream out;
    int nextChar;
    vector<int> freqs(256,0);
    BitInputStream inBit(in);

    //Read the header
    in.open(argv[1]);
    for (int i = 0; i < 256; i++) 
    {
        string nextFreq;
        unsigned char digit;
        
        while (1) 
        {
            digit = in.get();
            if (digit == '\n') break;
            nextFreq += digit;
        }
        freqs[i] = stoi(nextFreq);
    }
    
    //Construct the huffman tree
    HCTree tree;
    tree.build(freqs);

    //Open output file
    out.open(argv[2]);

    //Decode the string from the input file using the huffman tree
    //Read the encoded string bit by bit
    do 
    {
        nextChar = tree.decode(inBit);
        
        if (in.eof()) break;
        
        out << (char)nextChar;
    }
    while (nextChar);

    //Close both input and output files
    in.close();
    out.close();

    return 0;
}