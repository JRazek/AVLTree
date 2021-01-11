#include <bits/stdc++.h>

using namespace std;

struct AVLTree{
    struct BinaryNode{
        BinaryNode * parent = nullptr;
        BinaryNode * left = nullptr;
        BinaryNode * right = nullptr;

        int value;

        int leftHeight = 0;
        int rightHeight = 0;

        int leftSubtreeSize = 0;
        int rightSubtreeSize = 0;


        const int id;
        BinaryNode(int id): id(id){};
    };
    BinaryNode * root = nullptr;
    int treeSize = 0;
    vector<BinaryNode *> testContainer;

    int getValue(int index){
        stack<pair<BinaryNode *, bool>> postOrderStack;
        BinaryNode * p = getNodeAtIndex(root, index, postOrderStack);
        return (p->value);
    }
    void showStructure(){
        cout<<"\n";
        for(auto n : testContainer){
            cout<<n->id<<" subtrees = "<<n->leftSubtreeSize<<" | "<<n->rightSubtreeSize<<"\n";
            cout<<" heights = "<<n->leftHeight<<" | "<<n->rightHeight<<"\n\n";
        }
        cout<<"\n\n\n\n\n\n";
    }
    bool findUnbalanced(){
        cout<<"\n";
        bool found = false;
        for(auto n : testContainer){
            if(abs(n->leftHeight - n->rightHeight) > 1) {
                cout << n->id << " subtrees = " << n->leftSubtreeSize << " | " << n->rightSubtreeSize << "\n";
                cout << " heights = " << n->leftHeight << " | " << n->rightHeight << "\n\n";
                found  = true;
            }
        }
        return found;
    }
    int max(int x, int y){
        return x > y ? x : y;
    }
    void insert(int index, int value){
        if(root == nullptr){
            root = new BinaryNode(treeSize);
            ++ treeSize;
            testContainer.push_back(root);
            root->value = value;
        }
        else {
            vector<bool> directions;
            BinaryNode * newNode = new BinaryNode(treeSize);
            newNode->value = value;
            insert(root, index, newNode, directions);
            ++ treeSize;
            testContainer.push_back(newNode);
        }
    }
private:
    void insert(BinaryNode * node, int index, BinaryNode * insertedNode, vector<bool> &directions, bool forceUnbalanced = false){//node, <left/right, reachableHeight
        bool turnedLeft = true;
        if(index > treeSize ){
            cout<<"INVALID ENTRY!";
            return;
        }
        if(index <= node->leftSubtreeSize){

            if(node->left == nullptr) {
                node->left = insertedNode;
                insertedNode->parent = node;
                updateNode(node);
            }
            else {
                insert(node->left, index, insertedNode, directions, forceUnbalanced);
            }
        }
        else {
            if(node->right == nullptr) {
                node->right = insertedNode;
                insertedNode->parent = node;
                updateNode(node);
            }
            else {
                insert(node->right, index - node->leftSubtreeSize - 1, insertedNode, directions, forceUnbalanced);
            }
            turnedLeft = false;
        }
        updateNode(node);
        directions.push_back(turnedLeft);

        int balance = node->leftHeight - node->rightHeight;
        //if negative - left rotation as right is too big

        if(abs(balance) > 1 && !forceUnbalanced){
            int currDirectionIndex = directions.size() - 1;
            bool first = directions[currDirectionIndex ];
            bool second = first;
            if(directions.size() >= 2)
                second = directions[currDirectionIndex - 1];
            if(first && second) {
                //ll if too heavy
                leftRotation(node);
            }
            else if(first && !second){
                //lr if too heavy
                rightRotation(node->left);
                leftRotation(node);
            }
            else if(!first && !second){
                //rr if too heavy
                rightRotation(node);
            }
            else if(!first && second){
                //rl if too heavy
                leftRotation(node->right);
                rightRotation(node);
            }
            cout<<"";
        }
    }
    void rightRotation(BinaryNode * node){
        BinaryNode * parent = node->parent;
        BinaryNode * rightChild = node->right;

        if(parent != nullptr){
            (parent->left == node ? parent->left = rightChild : parent->right = rightChild);
        }
        node->parent = rightChild;
        node->right = nullptr;
        updateNode(node);

        if(rightChild->left != nullptr){
            vector<bool> dirs;
            insert(rightChild->left, rightChild->leftSubtreeSize, node, dirs);
        }else {
            rightChild->left = node;
        }
        updateNode(rightChild);

        rightChild->parent = parent;

        if(node == root)
            root = rightChild;
        cout<<"";
    }
    void leftRotation(BinaryNode * node){
        BinaryNode * parent = node->parent;
        BinaryNode * leftChild = node->left;

        if(parent != nullptr){
            (parent->left == node ? parent->left = leftChild : parent->right = leftChild);
        }
        node->parent = leftChild;
        node->left = nullptr;
        updateNode(node);

        if(leftChild->right != nullptr){
            vector<bool> dirs;
            insert(leftChild->right, 0, node, dirs);
        }else {
            leftChild->right = node;
        }
        updateNode(leftChild);
        leftChild->parent = parent;
        if(node == root)
            root = leftChild;
        cout<<"";
    }
    void updateNode(BinaryNode * n){
        int lH = 0, lT = 0;
        if(n->left != nullptr) {
            lH = 1, lT = 1;
            lH += max(n->left->leftHeight, n->left->rightHeight);
            lT += n->left->leftSubtreeSize + n->left->rightSubtreeSize;
        }
        n->leftHeight = lH;
        n->leftSubtreeSize = lT;

        int rH = 0, rT = 0;
        if(n->right != nullptr) {
            rH = 1, rT = 1;
            rH += max(n->right->leftHeight, n->right->rightHeight);
            rT += n->right->leftSubtreeSize + n->right->rightSubtreeSize;
        }
        n->rightHeight = rH;
        n->rightSubtreeSize = rT;


    }

    BinaryNode * getNodeAtIndex(BinaryNode * node, int index, stack<pair<BinaryNode *, bool>> &postOrderStack){
        BinaryNode * result = nullptr;
        bool turnedLeft = true;
        if(index > treeSize ){
            cout<<"INVALID ENTRY!";
            result = nullptr;
        }
        if(index < node->leftSubtreeSize){
            if(node->left == nullptr)
                result = node;
            else
                result = getNodeAtIndex(node->left, index, postOrderStack);
        }
        else if(index == node->leftSubtreeSize){
            result = node;
        }
        else{
            int rightIndex = index - node->leftSubtreeSize - 1;
            if(node->right == nullptr)
                result = node;
            else
                result = getNodeAtIndex(node->right, rightIndex, postOrderStack);
            turnedLeft = false;
        }
        postOrderStack.push(pair<BinaryNode *, bool>(node, turnedLeft));
        return result;
    }

};

int main() {
    AVLTree avlTree;
    for(int i = 0; i < 6; i ++) {
        avlTree.insert(0, i);
        if(avlTree.findUnbalanced()) {
            cout<<"";
            break;
        }
    }
    for(int i = 0; i < 0; i +=3) {
        avlTree.insert(i, -1);
        if(avlTree.findUnbalanced()) {
            cout<<"";
            break;
        }
    }
    cout<<"";
   for(int i = 0; i < avlTree.treeSize; i++){
       cout<<avlTree.getValue(i)<<" ";
   }
    cout<<"";
    return 0;
}
