#include "HCNode.h"

bool HCNode::operator<(const HCNode& other) {
    if (count != other.count) {
        return count > other.count;
    } else {
        //compare ascii values       
        return symbol < other.symbol;
    }
}