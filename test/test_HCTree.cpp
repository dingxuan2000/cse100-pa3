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

// TEST_F(SimpleHCTreeFixture, TEST_BUILD) {
//     ASSERT_EQ(tree->root->symbol, 'u');
//     ASSERT_EQ(tree.root->count, 22);
//     ASSERT_EQ(tree.root->c0->symbol, 'u');
//     ASSERT_EQ(tree.root->c1->symbol, 'h');
//     ASSERT_EQ(tree.root->c1->c0->symbol, 'h');
//     ASSERT_EQ(tree.root->c1->c0->count, 5);
//     ASSERT_EQ(tree.root->c1->c0->c0->symbol, 'h');
//     ASSERT_EQ(tree.root->c1->c0->c0->count, 2);
//     ASSERT_EQ(tree.root->c1->c0->c1->symbol, 'a');
//     ASSERT_EQ(tree.root->c1->c0->c1->count, 3);

// cout << tree.root->symbol << endl;
// cout << tree.root->count << endl;
// cout << tree.root->c0->symbol << endl;
// cout << tree.root->c1->symbol << endl;
// cout << tree.root->c1->c0->symbol << endl;
// cout << tree.root->c1->c0->count << endl;
// cout << tree.root->c1->c0->c0->symbol << endl;
// cout << tree.root->c1->c0->c0->count << endl;
// cout << tree.root->c1->c0->c1->symbol << endl;
// cout << tree.root->c1->c0->c1->count << endl;
// ASSERT_EQ(tree.root, parent);
//}
TEST_F(SimpleHCTreeFixture, TEST_ENCODE) {
    ostringstream os;
    tree.encode('o', os);
    // cout << os.str() << endl;
    ASSERT_EQ(os.str(), "11001");
    ostringstream os2;
    tree.encode('h', os2);
    ASSERT_EQ(os2.str(), "100");
    ostringstream os3;
    tree.encode('k', os3);
    ASSERT_EQ(os3.str(), "1111");
}

TEST_F(SimpleHCTreeFixture, TEST_DECODE) {
    istringstream is("11001");
    ASSERT_EQ(tree.decode(is), 'o');
    istringstream is2("100");
    ASSERT_EQ(tree.decode(is2), 'h');
    istringstream is3("1111");
    ASSERT_EQ(tree.decode(is3), 'k');
}
