#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "HCTree.hpp"

using namespace std;
using namespace testing;

class SimpleHCTreeFixture : public ::testing::Test {
  protected:
    HCTree tree;
    // priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;

  public:
    SimpleHCTreeFixture() {
        // initialization code here
        vector<unsigned int> freqs(256);

        freqs['m'] = 2;
        freqs['n'] = 2;
        freqs['h'] = 2;
        freqs['k'] = 2;
        freqs['o'] = 1;
        freqs['p'] = 1;
        freqs['a'] = 3;
        freqs['u'] = 9;
        tree.build(freqs);
    }
};

TEST_F(SimpleHCTreeFixture, TEST_BUILD) {
    // HCNode* left = new HCNode(2, 'a', 0, 0, 0);
    // HCNode* right = new HCNode(3, 'b', 0, 0, 0);
    // HCNode* parent = new HCNode(5, 'a', left, right, 0);
    // left->p = parent;
    // right->p = parent;
    // while() {
    //     cout << i << " " << tree.leaves.at(i) << endl;
    // }
    cout << tree.root->symbol << endl;
    cout << tree.root->count << endl;
    cout << tree.root->c0->symbol << endl;
    cout << tree.root->c1->symbol << endl;
    cout << tree.root->c1->c0->symbol << endl;
    cout << tree.root->c1->c0->count << endl;
    cout << tree.root->c1->c0->c0->symbol << endl;
    cout << tree.root->c1->c0->c0->count << endl;
    cout << tree.root->c1->c0->c1->symbol << endl;
    cout << tree.root->c1->c0->c1->count << endl;
    // ASSERT_EQ(tree.root, parent);
}
TEST_F(SimpleHCTreeFixture, TEST_ENCODE) {
    ostringstream os;
    tree.encode('o', os);
    cout << os.str() << endl;
    // ASSERT_EQ(os.str(), "0");
}

TEST_F(SimpleHCTreeFixture, TEST_DECODE) {
    istringstream is("100");
    ASSERT_EQ(tree.decode(is), 'h');
}
