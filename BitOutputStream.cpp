/*
 *                                                        Tim Ferido
 *                                                        Kent Nguyen
 *                                                        CSE 100, Fall 2017
 *                                                        November 9, 2017
 *                                                        A12880086 
 *                                                        A12164917
 *                        Programming Assignment Three
 * File Name:    BitOutputStream.cpp
 * Description:  The BitOutputStream deals with setting bits individually
 *               in a byte and then writes it into the output file.
 */ 
#include "BitOutputStream.h"

/** Initialize a BitOutputStream that will use 
  * the given ostream for output */
BitOutputStream::BitOutputStream(std::ostream & os) : out(os), buf(0), nbits(0), byteTotal(0) {}

/** Send the buffer to the output, and clear it */
void BitOutputStream::flush() {
    out.put(buf);
    out.flush();
    buf = nbits = 0;
}

/** Write the least significant bit of the argument to
  * the bit buffer, and increment the bit buffer index.
  * But flush the buffer first, if it is full. */
void BitOutputStream::writeBit(int i) {
    
    //If the bit is full 
    if (nbits == 8) flush();

    //Write the least significant bit of i into buffer at current index
    buf = setBit(buf, i, nbits);

    //Increment index
    nbits++;
}

/** Sets a bit's value of the nth bit from the right of a byte argument,
  * and return the result. */
byte BitOutputStream::setBit(byte b, int bit, int n) {
    return ((b&~(1<<n))|(bit<<n));
}

int getnbits()
{
    return nbits;
}