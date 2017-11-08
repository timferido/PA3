/*
 *                                                        Tim Ferido
 *                                                        Kent Nguyen
 *                                                        CSE 100, Fall 2017
 *                                                        November 9, 2017
 *                                                        A12880086 
 *                                                        A12164917
 *                        Programming Assignment Three
 * File Name:    BitOutputStream.h
 * Description:  Contains methods and data fields of the BitOutputStream class.
 */ 
#include <iostream>

class BitOutputStream {
private:
    char buf;               //One byte buffer of bits
    int nbits;              //How many bits have been written to buf
    std::ostream & out;     //Reference to the output stream
    
public:
    /** Initialize a BitOutputStream that will use 
      * the given ostream for output */
    BitOutputStream(std::ostream & os);
    
    /** Send the buffer to the output, and clear it */
    void flush();
    
    /** Write the least significant bit of the argument to
      * the bit buffer, and increment the bit buffer index.
      * But flush the buffer first, if it is full. */
    void writeBit(int i)
    
    /** Sets a bit's value of the nth bit from the right of a byte argument,
      * and return the result. */
    void setBit(byte b, int bit, int n);
};
