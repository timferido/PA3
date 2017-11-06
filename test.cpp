#include "HCTree.h"

#include <queue>
#include <vector>
#include <fstream>
#include "HCNode.h"

using namespace std;

int main() {

    HCTree tree;

    std::vector<int>freqs (256, 0);

    for (int i = 0;i < 256; i++) {
        if (i==20||i==124||i==255) {
            freqs[i] = 10;
        }
    }

    tree.build(freqs);

    


    return 0;
}