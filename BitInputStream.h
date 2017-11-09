/*
 *                                                        Tim Ferido
 *                                                        Kent Nguyen
 *                                                        CSE 100, Fall 2017
 *                                                        November 9, 2017
 *                                                        A12880086 
 *                                                        A12164917
 *                        Programming Assignment Three
 * File Name:    BitOutputStream.h
 * Description:  Contains methods and data fields of the BitInputStream class.
 */ 
#include <iostream>

typedef unsigned char byte;

class BitInputStream {
private:
    char buf;               //One byte buffer of bits
    int nbits;              //How many bits have been written to buf
    std::istream & in;      //Reference to the input stream
    long byteTotal;         //Number of bytes total
    
public:

    /** Initialize a BitInputStream that will use 
      * the given istream for input */
    BitInputStream(std::istream & is);
    
    /** Fill the buffer from the input */
    void fill();
    
    /** Read the next bit from the bit buffer.
      * Fill the buffer from the input stream first if needed.
      * Return 1 if the bit read is 1 and 0 if 0 */
    int readBit();
    
    /** Select the bit value of the nth bit from the right
      * and return the result */
    byte bitVal(byte b, int n);
    
};
