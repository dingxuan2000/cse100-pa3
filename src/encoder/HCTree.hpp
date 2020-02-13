/**
 * TODO: file header
 *
 * Author: Xuan Ding, xding@ucsd.edu
 *        Qilong Li, qil009@ucsd.edu
 * HCTree class provides the build() to build the HCTree from the given
 * frequency vector. and use encode() and decode() to compress and decompress
 * the input file.
 */
#ifndef HCTREE_HPP
#define HCTREE_HPP

#include <fstream>
#include <map>
#include <queue>
#include <string>
#include <vector>
// #include "BitInputStream.hpp"
// #include "BitOutputStream.hpp"
#include "HCNode.hpp"

using namespace std;

/** TODO: class header */
class HCTree {
  private:
    HCNode* root;            // the root of HCTree
    vector<HCNode*> leaves;  // a vector storing pointers to all leaf HCNodes
    typedef priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;
    void deleteAll(HCNode* n);

  public:
    /* TODO: add function header and implement
     * Initialized a HCTree with root = 0
     */
    HCTree() : root(0) {}

    /* TODO: add function header
     * Delete all the nodes in the tree, and delelte all the pointers in vector
     */
    ~HCTree();

    /* TODO: add function header
     * Parameter: frequency vector with unsigned int
     * this function takes the frequency vector to build the HCTree, using the
     * ascii value and its corresponding frequency in the frequency vector to
     * build the HCTree. Using a "leaves" vector to store each HCNode pointer,
     * and using priority_queue to help build the HCTree from bottom to up with
     * Huffman algorithm.
     */
    void build(const vector<unsigned int>& freqs);

    /* TODO: add function header */
    // void encode(byte symbol, BitOutputStream& out) const;

    /* TODO: add function header
     * byte is unsigned char,
     * According to leaves vector, we can determine the symbol node in the tree.
     * Then traverse its parent until hit the root. Then we can get the encoding
     * bits for this symbol.
     */
    void encode(byte symbol, ostream& out) const;

    /* TODO: add function header */
    // byte decode(BitInputStream& in) const;

    /* TODO: add function header
     * pass in the whole encoding string, using get() function to go through
     * this string, once get one byte, then decode into a symbol by traverse the
     * HCTree.
     */
    byte decode(istream& in) const;
};

#endif  // HCTREE_HPP
