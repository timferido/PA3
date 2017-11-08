/*
 *                                                        Tim Ferido
 *                                                        Kent Nguyen
 *                                                        CSE 100, Fall 2017
 *                                                        November 9, 2017
 *                                                        A12880086 
 *                                                        A12164917
 *                        Programming Assignment Three
 * File Name:    BitInputStream.cpp
 * Description:  The
 */ 
#include "BitInputStream.h"

BitInputStream::BitInputStream(std::istream & is) : in(is), buf(0), nbits(8) {}

void BitInputStream::fill() {
    buf = in.get();
    nbits = 0;
}

int BitInputStream::readBit() {
    //temp return val
    int retVal;
    
    //if the buffer has been read completely
    if (nbits == 8) fill();

    //get the bit at the appropriate location in buffer
    retVal = (int)bitVal(buf, nbits);

    //increment index
    nbits++;

    return retVal;
}

byte BitInputStream::bitVal(byte b, int n) {
    return (b>>n)&1;
}

