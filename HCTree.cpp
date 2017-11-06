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
void HCTree::build(const vector<int>& freqs){


	//priority queue
	std::priority_queue<HCNode*> pq;

	//
	for (int i = 0; i < freqs.size(); i++) {
		HCNode* tmp = new HCNode(freqs[i], (byte)i);
		leaves[i] = tmp;
	}

	//push all the nodes onto priority queue
	for (int i = 0; i < leaves.size(); i++) {
		//check if pointer points to node
		if (leaves[i]) {
			//push onto queue
			pq.push(leaves[i]);
		}
	}

	//pop out first two and push in again
	//loop the above process
	while(pq.size()>1) {
		//create int for sum of childrens' counts
		int countSum = 0;

		//create a new node to be the parent
		HCNode* parent = new HCNode(0,0);

		parent->c1 = pq.top();	//pop node from pq to be c1 of parent
		countSum += pq.top()->count;
		pq.pop();
		parent->c1->p = parent;	//point child node to parent

		parent->c0 = pq.top();	//pop next node from pq to be c0 of parent
		countSum += pq.top()->count;
		pq.pop();
		parent->c0->p = parent;		//point child node to parent

		parent->count = countSum;	//update the parent node's count
		pq.push(parent);	//push parent node onto pq 
	}

	//assign last node in queue to the root
	root = pq.top();
	pq.pop();
}


/** Write to the given ofstream
 *  the sequence of bits (as ASCII) coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR STEP 1-3 BUT SHOULD NOT 
 *  BE USED IN THE FINAL SUBMISSION.
 */
void HCTree::encode(byte symbol, ofstream& out) const {
	//find symbol in 'leaves' vector
	//declarations
	HCNode* working = leaves[symbol];
	std::string codeR, codeF; 

	//traverse all the way up keeping track if 0 or 1
	//using parent nodes
	while (working->p) {
		//check if 0 or 1 child
		if (working->p->c0 == working) {
			//0 child
			codeR += '0';
		} else {
			//1 child
			codeR += '1';
		}
	}

	//reverse code 
	auto itr = codeR.rbegin();
	auto end = codeR.rend();

	while (itr != end) {
		codeF += *itr;
		itr++;
	}

	//write to stream
	out << codeF;
}

/** Return the symbol coded in the next sequence of bits (represented as 
 *  ASCII text) from the ifstream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR STEP 1-3 BUT SHOULD NOT BE USED
 *  IN THE FINAL SUBMISSION.
 */
int HCTree::decode(ifstream& in) const {

	//declarations
	HCNode* working = root;
	unsigned char bit;

	while (1) {
		bit = in.get();
		if (in.eof()) break;
		if (bit) {
			if (working->c1) {
				working = working->c1;
			} else {
				return 0;
			}
		} else {
			if (working->c0) {
				working = working->c0;
			} else {
				return 0;
			}
		}
		
		if(working->c0 == 0 && working->c1 == 0) {
			return working->symbol;
		}
	}
	return 0;
}



