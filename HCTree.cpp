#include "HCTree.h"

#include <queue>
#include <vector>
#include <fstream>
#include "HCNode.h"

using namespace std;


/** Use the Huffman algorithm to build a Huffman coding trie.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the trie,
 *  and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build(const vector<int>& freqs){

	//loop through freqs vector
	//	for each iteration
	//		create a new Node 
	//		update the node's count field with corresponding
	//			value in freqs vector
	//		put pointer to new node inside 'leaves' vector

	for (int i = 0; i < freqs.size(); i++) {
		HCNode* pTmp = new HCNode(freqs[i], (byte)i);
		leaves[i] = pTmp;
	}

	
}


/** Write to the given ofstream
 *  the sequence of bits (as ASCII) coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR STEP 1-3 BUT SHOULD NOT 
 *  BE USED IN THE FINAL SUBMISSION.
 */
void HCTree::encode(byte symbol, ofstream& out) const {

}

/** Return the symbol coded in the next sequence of bits (represented as 
 *  ASCII text) from the ifstream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR STEP 1-3 BUT SHOULD NOT BE USED
 *  IN THE FINAL SUBMISSION.
 */
int HCTree::decode(ifstream& in) const {
	return 0;
}



