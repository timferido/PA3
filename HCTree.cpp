/*
 *                                                        Tim Ferido
 *                                                        Kent Nguyen
 *                                                        CSE 100, Fall 2017
 *                                                        November 9, 2017
 *                                                        A12880086 
 *                                                        A12164917
 *                        Programming Assignment Three
 * File Name:    HCTree.cpp
 * Description:  Builds the Huffman Code Tree from a file to encode and decode
 *               Huffman codes based on ASCII frequency in the file to best
 *               compress the file in order to save space.
 */ 
#include "HCTree.h"

#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include "HCNode.h"

using namespace std;


/** Use the Huffman algorithm to build a Huffman coding trie.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the trie,
 *  and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build(const vector<int>& freqs)
{
	//Priority queue
	std::priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;

	//Create HCNodes from the frequency vector
	for (int i = 0; i < freqs.size(); i++) 
    {
        //Avoid unneccessary nodes and potential memory leaks
        if (freqs[i] != 0)
        { 
            HCNode* tmp = new HCNode(freqs[i], (byte)i);
            leaves[i] = tmp;
        }
	}

	//Push all the nodes onto priority queue
	for (int i = 0; i < leaves.size(); i++) 
    {
		//Check if pointer points to node
		if (leaves[i]) 
        {
			//Push onto queue
			pq.push(leaves[i]);
		}
	}

	//Pop out first two and push in again
	//Loop the above process
	while(pq.size() > 1) 
    {
        //Create int for sum of childrens' counts
        int countSum = 0;

		//Create a new node to be the parent
		HCNode* parent = new HCNode(0,0);

        //Pop HCNode and set HCNode pointers
		parent->c1 = pq.top();	        //Pop node from pq to be c1 of parent
		countSum += parent->c1->count;
		pq.pop();
		parent->c1->p = parent;	        //Point child node to parent

        //Pop HCNode and set HCNode pointers
		parent->c0 = pq.top();	        //Pop next node from pq to be c0 of parent
		countSum += parent->c0->count;
		pq.pop();
		parent->c0->p = parent;		    //Point child node to parent

        //Update parent node count and push to pq
		parent->count = countSum;	    
		pq.push(parent);	            
	}

	//Assign last node in queue to the root
	root = pq.top();
	pq.pop();
}

/** Write to the given BitOutputStream
 *  the sequence of bits coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const
{
    //Find symbol in 'leaves' vector
    //Declarations
    HCNode* working = leaves[symbol];
    std::string codeR; 
        
    //Traverse all the way up keeping track if 0 or 1
	//Using parent nodes
	while (working->p) 
    {
		//Check if 0 or 1 child
		if (working->p->c0 == working) 
			//0 child
			codeR += '0';
        else 
			//1 child
			codeR += '1';
            
        working = working->p;
	}
    
    //Reverse code using reverse iterator
	auto itr = codeR.rbegin();
	auto end = codeR.rend();

    //Write bit in the correct way
	while (itr != end) 
    {
		if (*itr == '1')
            out.writeBit(1);
        else
            out.writeBit(0);
        
        itr++;
	}    
}

/** Write to the given ofstream
 *  the sequence of bits (as ASCII) coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR STEP 1-3 BUT SHOULD NOT 
 *  BE USED IN THE FINAL SUBMISSION.
 */
void HCTree::encode(byte symbol, ofstream& out) const 
{
	//Find symbol in 'leaves' vector
	//Declarations
	HCNode* working = leaves[symbol];
	std::string codeR, codeF; 

	//Traverse all the way up keeping track if 0 or 1
	//Using parent nodes
	while (working->p) 
    {
		//Check if 0 or 1 cild
		if (working->p->c0 == working) 
			//0 child
			codeR += '0';
        else 
			//1 child
			codeR += '1';
            
        working = working->p;
	}

	//Reverse code using reverse iterator
	auto itr = codeR.rbegin();
	auto end = codeR.rend();

	while (itr != end) 
    {
		codeF += *itr;
		itr++;
	}

	//Write to stream
	out << codeF;
}

/** Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
int HCTree::decode(BitInputStream& in) const
{    
    //Declarations
	HCNode* working = root;
    int bit;
    
    //Loop through the coded string
	while (1) 
    {
        // Get the "bit"
		bit = in.readBit();
        
        //Check eof
        
        //Go down the Huffman Tree until a leaf is reached
		if (bit == 1) 
        {    
            // Go down the 1 bit child
			if (working->c1)
				working = working->c1;
            // Return null to catch an error
			else 
				return 0;
        }
        
        else 
        {
            // Go down the 0 bit child
			if (working->c0) 
				working = working->c0;
            else
				return 0;
		}
		
        //Return symbol if a leaf
		if(working->c0 == 0 && working->c1 == 0) 
			return working->symbol;
	}
    
    return 0;
}

/** Return the symbol coded in the next sequence of bits (represented as 
 *  ASCII text) from the ifstream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR STEP 1-3 BUT SHOULD NOT BE USED
 *  IN THE FINAL SUBMISSION.
 */
int HCTree::decode(ifstream& in) const 
{
	//Declarations
	HCNode* working = root;
	unsigned char bit;

    //Loop through the coded string
	while (1) 
    {
        // Get the "bit"
		bit = in.get();
        
        // Check for eof to prevent errors
		if (in.eof()) break;
        
        //Go down the Huffman Tree until a leaf is reached
		if (bit == '1') 
        {    
            // Go down the 1 bit child
			if (working->c1)
				working = working->c1;
            // Return null to catch a possible error
			else 
				return 0;
        }
        
        else 
        {
            // Go down the 0 bit child
			if (working->c0)
				working = working->c0;
			else
				return 0;
		}
		
        // Return the symbol if a leaf
		if(working->c0 == 0 && working->c1 == 0) 
			return working->symbol;
	}
    
	return 0;
}

