#include "BitOutputStream.h"

BitOutputStream::BitOutputStream(std::ostream & os) : out(os), buf(0), nbits(0) {}

void BitOutputStream::flush() {
    out.put(buf);
    out.flush();
    buf = nbits = 0;
}

void BitOutputStream::writeBit(int i) {
    
    //if the bit is full 
    if (nbits == 8) flush();

    //write the least significant bit of i into buffer at current index
    buf = setBit(buf, i, nbits);

    //increment index
    nbits++;
}

byte BitOutputStream::setBit(byte b, int bit, int n) {
    return ((b&~(1<<n))|(bit<<n));
}