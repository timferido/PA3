#include <iostream>

typedef unsigned char byte;

class BitOutputStream {
private:
    char buf;
    int nbits;
    std::ostream & out;
public:
    BitOutputStream(std::ostream & os);
    void flush();
    void writeBit(int i);
    byte setBit(byte b, int bit, int n);
};
