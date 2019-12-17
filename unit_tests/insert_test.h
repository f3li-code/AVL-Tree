#include "gtest/gtest.h"

#include "../header/AVLTree.h"

TEST(insert, t1) {
    AVLTree tree;
    tree.insert("abcd");
    tree.insert("ncdl");
    tree.insert("3");
    tree.print();
}