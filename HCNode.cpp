/*
 *                                                        Tim Ferido
 *                                                        Kent Nguyen
 *                                                        CSE 100, Fall 2017
 *                                                        November 9, 2017
 *                                                        A12880086 
 *                                                        A12164917
 *                        Programming Assignment Three
 * File Name:    HCNode.h
 * Description:  Overloads the operator < to compare two HCNodes.
 */
#include "HCNode.h"

bool HCNode::operator<(const HCNode& other) {
    //Compare counts
    if (count != other.count)
        return count > other.count;   
    
    //Compare ascii values       
    return symbol < other.symbol;
}