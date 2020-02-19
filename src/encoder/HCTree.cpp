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
// return the length of each symbol's encoding
// bits,便于我们计算一共需要多少的bits 这是放在header
// file的第一个信息（32个bit),
unsigned int HCTree::encodeSize(byte symbol) {
    // pass a symbol in, traverse the tree根据leaves vector, 然后return the
    // string length
    HCNode* ptr;
    ptr = findSymbol(leaves, symbol);
    if (ptr == this->root) return 1;
    unsigned int count = 0;
    while (ptr->p != nullptr) {
        count++;
        ptr = ptr->p;
    }
    return count;
}
HCNode* HCTree::findSymbol(vector<HCNode*>& leaves, byte symbol) {
    //根据symbol和leaves vector找到HCNode, then return
    return leaves.at((unsigned int)symbol);
}

/* TODO */
void HCTree::encode(byte symbol, BitOutputStream& out) const {
    if ((this->root->c0 == nullptr) && (this->root->c1 == nullptr))
        out.writeBit(0);
    else {
        HCNode* ptr = leaves.at(symbol);
        string en_string = "";
        while (ptr->p != nullptr) {
            if (ptr == ptr->p->c0) {  // check if is 0 side
                en_string = "0" + en_string;
                //这里writeBit是反着的进去的，因为是从下往上track
                // out.writeBit(0);
                ptr = ptr->p;

            } else if (ptr == ptr->p->c1) {
                // out.writeBit(1);
                en_string = "1" + en_string;
                ptr = ptr->p;
            }  // check if is 1 side
        }
        for (int i = 0; i < en_string.size(); i++) {
            if (en_string.at(i) == '1')
                out.writeBit(1);
            else
                out.writeBit(0);
        }
    }
}

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
byte HCTree::decode(BitInputStream& in) const {
    HCNode* ptr = this->root;
    unsigned int c;
    if (ptr == nullptr) return 0;
    // if only one node in the tree, just return the root's symbol
    if (ptr->c0 == nullptr && ptr->c1 == nullptr) {
        in.numBits--;
        return ptr->symbol;
    } else {
        while (!in.eof()) {
            c = in.readBit();
            if (c == 1) {
                ptr = ptr->c1;
                in.numBits--;
            }
            if (c == 0) {
                ptr = ptr->c0;
                in.numBits--;
            }
            // when reached leaf node
            if (ptr->c0 == nullptr && ptr->c1 == nullptr) return ptr->symbol;
        }
    }
}

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
//得到每个char的对应的int(1or0)
//然后用writeBit()去将每个bit写进buffer里面，
void HCTree::num_node(HCNode* ptr, BitOutputStream& out) {
    if (ptr->c0 == nullptr && ptr->c1 == nullptr) {
        out.writeBit(0);
        out.writeByte(ptr->symbol);
    } else {
        out.writeBit(1);
        num_node(ptr->c0, out);
        num_node(ptr->c1, out);
    }
}
HCNode* HCTree::getRoot() { return this->root; }
// void HCTree::node_path(HCNode* ptr, BitOutputStream& out) {
//     if (ptr == nullptr) return;
//     //需要root的信息吗？我觉得没有必要，在reconstruct
//     tree的时候，这个无关紧要 if (ptr == this->root) {
//         out.writeBit(0);
//         out.writeByte(ptr->symbol);
//     }

//     if (ptr->p != nullptr && ptr->p->c0 == ptr) {
//         out.writeBit(0);
//     }
//     if (ptr->p != nullptr && ptr->p->c1 == ptr) {
//         out.writeBit(1);
//     }
//     if (ptr->c0 == nullptr && ptr->c1 == nullptr) {
//         out.writeByte(ptr->symbol);
//     }
//     node_path(ptr->c0, out);
//     node_path(ptr->c1, out);
// }
HCNode* HCTree::rebuild(BitInputStream& in) {
    if (in.readBit() == 0) {
        byte symbol = in.readByte();
        HCNode* newNode = new HCNode(0, symbol, 0, 0);
        return newNode;
    } else {
        HCNode* newNode = new HCNode(0, 0, 0, 0);
        newNode->c0 = rebuild(in);
        newNode->c1 = rebuild(in);
    }
}