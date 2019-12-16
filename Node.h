#ifndef NODE_H
#define NODE_H
#include <string>
#include <iostream>
using namespace std;


class Node {
    friend class AVLTree;
    public:
        Node(){
            left = nullptr;
            right = nullptr;
            parent = nullptr;
            height = -1;
            str = "";
        };
        Node(string key, int height = -1){
            left = nullptr;
            right = nullptr;
            parent = nullptr;
            str = key;
        };
    private:
        Node* left;
        Node* right;
        Node* parent;
        string str;
        int height;
        void print() const{
            cout << str;
        };
};

#endif // NODE_H
