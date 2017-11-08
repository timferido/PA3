#include "BitOutputStream.h"

BitOutputStream::BitOutputStream(std::ostream & os) : out(os), buf(0), nbits(0) {}

void BitOutputStream::flush() {
    out.put(buf);
    out.flush();
    buf = nbits = 0;
}

void BitOutputStream::writeBit(int i) {
    
}