/*
 *                                                        Tim Ferido
 *                                                        Kent Nguyen
 *                                                        CSE 100, Fall 2017
 *                                                        November 9, 2017
 *                                                        A12880086 
 *                                                        A12164917
 *                        Programming Assignment Three
 * File Name:    BitInputStream.cpp
 * Description:  The BitInputStream takes an encoded file and reads the file
 *               bit by bit.
 */ 
#include "BitInputStream.h"

/** Initialize a BitInputStream that will use 
  * the given istream for input */
BitInputStream::BitInputStream(std::istream & is) : in(is), buf(0), nbits(8) {}

/** Fill the buffer from the input */
void BitInputStream::fill() {
    buf = in.get();
    nbits = 0;
}

/** Read the next bit from the bit buffer.
  * Fill the buffer from the input stream first if needed.
  * Return 1 if the bit read is 1 and 0 if 0 */
int BitInputStream::readBit() {
    //Temp return val
    int retVal;
    
    //If the buffer has been read completely
    if (nbits == 8) fill();

    //Get the bit at the appropriate location in buffer
    retVal = (int)bitVal(buf, nbits);

    //Increment index
    nbits++;

    return retVal;
}

/** Select the bit value of the nth bit from the right
  * and return the result */
byte BitInputStream::bitVal(byte b, int n) {
    return (b>>n)&1;
}

