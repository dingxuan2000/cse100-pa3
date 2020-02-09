/**
 * TODO: file header
 *
 * Author:
 */
#include "HCTree.hpp"

/* TODO */
HCTree::~HCTree() {}

/* TODO
 * Build the HCTree from the given frequency vector.
 * 需要把每一个HCNode* 放进leaves vector里面，再讲每个vector放进pq里面，
 */
void HCTree::build(const vector<unsigned int>& freqs) {
    //这个vector.size是256, index from 0 to 255. 每一个index里存的是每个ascill
    // value的frequecy，首先给每个non-freq 的ascill value create HCNode,
    // 然后create一个后，立马放进pq里面
    pq queue;
    HCNode* c0ptr;
    HCNode* c1ptr;
    HCNode* pptr;
    // leaves = vector<HCNode*>(256, (HCNode*)0);
    for (int i = 0; i < 256; i++) {
        //如果freq不是0，create a new HCNode with symbol and count
        if (freqs.at(i) != 0) {
            HCNode* newNode = new HCNode(freqs.at(i), (byte)i, 0, 0, 0);
            leaves.push_back(newNode);
        } else {
            continue;
        }
    }
    // then, push the leaves vector into pq, then pq will sort the newNodes
    // automatically
    for (int i = 0; i < leaves.size(); i++) {
        queue.push(leaves.at(i));
    }
    // next, build the HCTree:
    // 1. 最小的count的node会被先pop出来，就是pq需要先pop出两个node,
    // 先pop出来的第一个node是c0, 第二个是c1，然后这两个node的parent将会被create
    // a newNode, symbol是c0's symbol, count是 两个孩子的count sum.
    while (queue.size() > 1) {  // how to check queue has at least two HCNodes?

        c0ptr = queue.top();
        queue.pop();
        c1ptr = queue.top();
        queue.pop();
        HCNode* new_parent = new HCNode(c0ptr->count + c1ptr->count,
                                        c0ptr->symbol, c0ptr, c1ptr, 0);
        c0ptr->p = new_parent;
        c0ptr->p = new_parent;
        queue.push(new_parent);
    }
    this->root = queue.top();
    if (queue.size() == 0) return;
}

/* TODO */
// void HCTree::encode(byte symbol, BitOutputStream& out) const {}

/* TODO
 * byte 就是unsigned char,
 * 根据leaves vector, we can determine the symbol node in the tree.
 * Then traverse its parent until hit the root
 */
void HCTree::encode(byte symbol, ostream& out) const {}

/* TODO */
// byte HCTree::decode(BitInputStream& in) const { return ' '; }

/* TODO */
byte HCTree::decode(istream& in) const { return ' '; }
