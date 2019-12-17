#ifndef AVLTREE_H
#define AVLTREE_H
#include <string>
#include <iostream>
#include <fstream>
#include "Node.h"
using namespace std;


class AVLTree
{
    public:
        AVLTree();
        void insert(const string&);//
        int balanceFactor(Node*) const;//
        void print() const;
        void visualizeTree(const string&) const;//

    private:
        void rotate(Node*);//
        void rotateLeft(Node* n);//
        void rotateRight(Node* n);//
        //Node* findUnbalancedNode() const;
        void visualizeTree(ofstream&, Node*) const;//
        void visualizeTreeBalance(ofstream&, Node*) const;
        void print(Node*) const;

    private:
        void updateHeight(Node*);//
        void setChild(Node* par, const string& direction, Node* newChild);//
        void replaceChild(Node* par, Node* curChild, Node* newChild);//

    private:
        Node* root;
};

#endif // AVLTREE_H
