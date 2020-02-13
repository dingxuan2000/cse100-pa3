/**
 * TODO: file header
 *
 * Author:Xuan Ding, xding@ucsd.edu
 *        Qilong Li, qil009@ucsd.edu
 * HCTree class provides the build() to build the HCTree from the given
 * frequency vector. and use encode() and decode() to compress and decompress
 * the input file. Implemented HCTree.hpp.
 *
 */
#include "HCTree.hpp"

/* TODO */
HCTree::~HCTree() {
    deleteAll(this->root);
    // leaves.clear();
    // for (int i = 0; i < (leaves.size()); i++) {
    //     delete leaves.at(i);
    // }
    this->leaves.clear();
}

/* TODO
 * Parameter: frequency vector with unsigned int
 * this function takes the frequency vector to build the HCTree, using the
 * ascii value and its corresponding frequency in the frequency vector to
 * build the HCTree. Using a "leaves" vector to store each HCNode pointer, and
 * using priority_queue to help build the HCTree from bottom to up with Huffman
 * algorithm.
 */
void HCTree::build(const vector<unsigned int>& freqs) {
    // this vector size is 256, index from 0 to 255. Each index stores each
    // ascii value's frequency.
    // First, create a HCNode pointer for each non-freq, then put in the pq
    // after creating each node.
    pq queue;
    HCNode* c0ptr;
    HCNode* c1ptr;
    HCNode* pptr;
    for (int i = 0; i < freqs.size(); i++) {
        // if freq is not 0, create a new HCNode with symbol and count
        if (freqs.at(i) != 0) {
            HCNode* newNode = new HCNode(freqs.at(i), (byte)i, 0, 0, 0);
            leaves.push_back(newNode);
        } else {
            leaves.push_back((HCNode*)0);
        }
    }
    // then, push the leaves vector into pq, then pq will sort the newNodes
    // automatically
    for (int i = 0; i < leaves.size(); i++) {
        if (leaves.at(i) != nullptr) queue.push(leaves.at(i));
    }
    // next, build the HCTree:
    // 1. the smallest count of the node will be poped first, so pq needs to pop
    // the first two nodes, the first to be poped node will be c0, the latter
    // poped one will be c1. Then create a parent node(symbol is c0's symbol,
    // count is the the sum of two children's counts.)
    while (queue.size() != 1) {  // how to check queue has at least two HCNodes?

        c0ptr = queue.top();
        queue.pop();
        c1ptr = queue.top();
        queue.pop();
        HCNode* new_parent = new HCNode(c0ptr->count + c1ptr->count,
                                        c0ptr->symbol, c0ptr, c1ptr, 0);
        c0ptr->p = new_parent;
        c1ptr->p = new_parent;
        queue.push(new_parent);
    }
    this->root = queue.top();
    queue.pop();
    if (queue.size() == 0) return;
}

/* TODO */
// void HCTree::encode(byte symbol, BitOutputStream& out) const {}

/* TODO
 * byte is unsigned char,
 * According to leaves vector, we can determine the symbol node in the tree.
 * Then traverse its parent until hit the root. Then we can get the encoding
 * bits for this symbol.
 */
void HCTree::encode(byte symbol, ostream& out) const {
    // if the tree is empty, means the inputfile is also empty
    // if only one node in the tree, means root node has no c0 and c1

    if ((this->root->c0 == nullptr) && (this->root->c1 == nullptr))
        out << "0";
    else {
        HCNode* ptr = leaves.at(symbol);
        string en_string = "";
        while (ptr->p != nullptr) {
            if (ptr == ptr->p->c0) {  // check if is 0 side
                en_string = "0" + en_string;
                ptr = ptr->p;

            } else if (ptr == ptr->p->c1) {
                en_string = "1" + en_string;
                ptr = ptr->p;
            }  // check if is 1 side
        }

        out << en_string;
    }
}

/* TODO */
// byte HCTree::decode(BitInputStream& in) const { return ' '; }

/* TODO
 * pass in the whole encoding string, using get() function to go through
 * this string, once get one byte, then decode into a symbol by traverse the
 * HCTree.
 */
byte HCTree::decode(istream& in) const {
    HCNode* ptr = this->root;
    char c = ' ';
    if (ptr == nullptr) return 0;
    // if only one node in the tree, just return the root's symbol
    if (ptr->c0 == nullptr && ptr->c1 == nullptr) {
        in.get(c);
        return ptr->symbol;
    } else {
        while (in.get(c)) {
            // if (ptr->c0 == nullptr && ptr->c1 == nullptr) return ptr->symbol;
            if (c == '1') ptr = ptr->c1;
            if (c == '0') ptr = ptr->c0;
            // when reached leaf node
            if (ptr->c0 == nullptr && ptr->c1 == nullptr) return ptr->symbol;
        }
    }
}
void HCTree::deleteAll(HCNode* n) {
    if (n == 0) return;
    deleteAll(n->c0);
    deleteAll(n->c1);
    delete n;
}
