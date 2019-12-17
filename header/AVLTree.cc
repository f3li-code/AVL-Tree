#include "AVLTree.h"


AVLTree::AVLTree()
{
    root = nullptr;
}

void AVLTree::updateHeight(Node* n) {//leaf node's height is -1
    int leftHeight = -1;
    if (n->left != nullptr){
        leftHeight = n->left->height;
    }
    int rightHeight = -1;
    if (n->right != nullptr){
        rightHeight = n->right->height;
    }
    if (leftHeight > rightHeight){
        n->height = leftHeight + 1;
    }
    else {
        n->height = rightHeight + 1;
    }
}

void AVLTree::setChild(Node* par, const string& direction, Node* child){//Always update height when adding nodes
    if (direction != "left" && direction != "right"){
        return;
    }
    if (direction == "left"){
        par->left = child;
    }
    else {
        par->right = child;
    }
    if (child != nullptr){
        child->parent = par;
    }
    updateHeight(par);
    return;
}

void AVLTree::replaceChild(Node* par, Node* curChild, Node* newChild){
    if (par->left == curChild){
        return setChild(par, "left", newChild);
    }
    else if (par->right == curChild){
        return setChild(par, "right", newChild);
    }
    return;
}

int AVLTree::balanceFactor(Node* n) const{
    int leftHeight = -1;
    if (n->left != nullptr){
        leftHeight = n->left->height;
    }
    int rightHeight = -1;
    if (n->right != nullptr){
        rightHeight = n->right->height;
    }
    return leftHeight - rightHeight;
}

void AVLTree::rotateRight(Node* n) {
    //cout << "rotating node " << n->str << endl;
    Node* dangling = n->left->right;
    if (n->parent != nullptr){//n is not the root
        replaceChild(n->parent, n, n->left);
    }
    else{//n is the root
        root = n->left;
        root->parent = nullptr;
    }
    setChild(n->left, "right", n);
    setChild(n, "left", dangling);
    return;
}

void AVLTree::rotateLeft(Node* n) {
    Node* dangling = n->right->left;
    //if (dangling == nullptr) cout << "dangling is null" << endl;
    if (n->parent != nullptr){
        replaceChild(n->parent, n, n->right);
    }
    else {
        root = n->right;
        root->parent = nullptr;
    }
    //cout << "enter setchild (n->right, left, n)" << endl;
    setChild(n->right, "left", n);
    //cout << "enter setchild (n, right, dangling)" << endl;
    setChild(n, "right", dangling);

    return;
}

void AVLTree::rotate(Node* n) { //height will be updated in rotate(setChild)
    updateHeight(n);
    if (balanceFactor(n) == -2){//right side has too many nodes
        if (balanceFactor(n->right) == 1){// (-2, 1) structure, rotate right(right), rotate left(n)
            rotateRight(n->right);
            //cout << "rotateright (n->right)" << endl;
        }
        //cout << "enter rotateleft in rotate" << endl;
        rotateLeft(n);
        //cout << "rotateleft (n)" << endl;
    }
    else if (balanceFactor(n) == 2){
        if (balanceFactor(n->left) == 1){//-2, 1
            rotateLeft(n->left);
            //cout << "rotateleft (n->left)" << endl;
        }
        rotateRight(n);
        //cout << "rotate (n)" << endl;
    }
    return;
}

void AVLTree::insert(const string& key){
    Node* addNode = new Node(key);
    if (root == nullptr){
        root = addNode;
        //cout << "root->str: " << addNode->str << endl;
        return;
    }

    Node* cur = root;
    while (cur != nullptr){
        if (key == cur->str){
            return;
        }
        if (key < cur->str){
            if (cur->left == nullptr){
                cur->left = addNode;
                addNode->parent = cur;
                cur = nullptr;
            }
            else {
                cur = cur->left;
            }
        }
        else {
            if (cur->right == nullptr){
                cur->right = addNode;
                addNode->parent = cur;
                cur = nullptr;
            }
            else {
                cur = cur->right;
            }
        }
    }
    while (addNode != nullptr){
        rotate(addNode);
        addNode = addNode->parent;
    }
    /*
    cur = addNode;
    while (cur != nullptr){
        updateHeight(cur);
        if (cur->parent != nullptr)
        cout << "cur->parent->str: " << cur->parent->str << endl;
        if (balanceFactor(cur) == 2 || balanceFactor(cur) == -2){
            cout << "enter rotate in INSERT" << endl;
            rotate(cur);
            return;
        }
        cur = cur->parent;
    }
    */
    return;
}

void AVLTree::visualizeTree(const string &outputFilename) const{
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    outFS<<endl<<"//edges"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    /*
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
    */
}
/* BALANCE FACTOR IN VISUALIZE
void AVLTree::visualizeTreeBalance(ofstream& outFS, Node* n) const{
    if (n == nullptr){
        return;
    }
    visualizeTreeBalance(outFS, n->left);
    outFS << n->str << "[BF = " << balanceFactor(n) << "];" << endl;
    visualizeTreeBalance(outFS, n->right);
}
*/
void AVLTree::visualizeTree(ofstream& outFS, Node* n) const{
    if (n == nullptr){
        return;
    }
    if (n->left != nullptr) {
        outFS << n->str << " -> " << n->left->str << ";" << endl;
    }
    if (n->right != nullptr){
        outFS << n->str << " -> " << n->right->str << ";" << endl;
    }
    visualizeTree(outFS, n->left);
    visualizeTree(outFS, n->right);
}
/*//THIS IS ZYBOOKS CODE
void AVLTree::visualizeTree(ofstream & outFS, Node *n) const{
    if(n != nullptr){
        if(n->left != nullptr){
            visualizeTree(outFS,n->left);
            outFS<<n->str <<" -> " <<n->left->str<<";"<<endl;
        }

        if(n->right != nullptr){
            visualizeTree(outFS,n->right);
            outFS<<n->str <<" -> " <<n->right->str<<";"<<endl;
        }
    }
}
*/

void AVLTree::print() const{
    return print(root);
    cout << endl << endl;
}

void AVLTree::print(Node* n) const{
    if (n == nullptr){
        return;
    }
    print(n->left);
    n->print(); cout << "(" << balanceFactor(n) << "), ";
    print(n->right);
}
