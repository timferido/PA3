#include <iostream>

typedef unsigned char byte;

class BitInputStream {
private:
    char buf;
    int nbits;
    std::istream & in;
public:
    BitInputStream(std::istream & is);
    void fill();
    int readBit();
    byte bitVal(byte b, int n);
};
