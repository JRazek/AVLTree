#include <bits/stdc++.h>

using namespace std;

struct AVLTree{
    struct BinaryNode{
        BinaryNode * parent = nullptr;
        BinaryNode * left = nullptr;
        BinaryNode * right = nullptr;

        int value;

        int leftSubtreeSize = 0;
        int rightSubtreeSize = 0;

        const int id;
        BinaryNode(int id): id(id){};
    };
    BinaryNode * root = nullptr;
    int treeSize = 0;
    vector<BinaryNode *> testContainer;

    void insert(int index, int value){
        if(root == nullptr){
            root = new BinaryNode(0);
            root->value = value;
            ++ treeSize;
            testContainer.push_back(root);
            return;
        }
        vector<pair<BinaryNode *, bool>> postOrderStack;
        pair<BinaryNode *, bool> p = findParentForInsert(root, index, postOrderStack);
        if(p.second){
            BinaryNode * left = new BinaryNode(treeSize);
            left->parent = p.first;
            left->value = value;
            ++ treeSize;
            p.first->left = left;
            testContainer.push_back(left);
        }else{
            BinaryNode * right = new BinaryNode(treeSize);
            right->parent = p.first;
            right->value = value;
            ++ treeSize;
            p.first->right = right;
            testContainer.push_back(right);
        }
        for(auto pair : postOrderStack){
            BinaryNode * n = pair.first;
            bool left = pair.second;
            left ? ++n->leftSubtreeSize : ++n->rightSubtreeSize;
            cout<<"";
        }
        for(auto it = postOrderStack.rbegin(); it != postOrderStack.rend(); ++it){
            BinaryNode * n = it->first;
            ///todo rotate to fix
            balance(n);
        }
        cout<<"";
    }
    void remove(int index){
    }
    int getValue(int index){
        stack<pair<BinaryNode *, bool>> postOrderStack;
        BinaryNode * p = getNodeAtIndex(root, index, postOrderStack);
        return (p->value);
    }
    void showStructure(){
        for(auto n : testContainer){
            cout<<n->id<<" = "<<n->leftSubtreeSize<<" | "<<n->rightSubtreeSize<<"\n";
        }
        cout<<"\n\n\n\n\n\n";
    }
    void balance(BinaryNode * node){
        if(node == nullptr)
            return;
        int balanceVal = node->leftSubtreeSize - node->rightSubtreeSize;
        if(balanceVal > 1)
            rotate(node, balanceVal - 1);
        if(balanceVal < -1)
            rotate(node, balanceVal + 1);
    }
private:
    //finds the parent of the node were looking for and the bool - if true - left child if false - right child
    pair<BinaryNode *, bool> findParentForInsert(BinaryNode * node, int index, vector<pair<BinaryNode *, bool>> &postOrderStack){
        pair<BinaryNode *, bool> result;
        bool turnedLeft = true;
        if(index > treeSize ){
            cout<<"INVALID ENTRY!";
            result = pair<BinaryNode *, bool>(nullptr, 0);
        }
        if(index <= node->leftSubtreeSize){
            if(node->left == nullptr)
                result = pair<BinaryNode *, bool>(node, true);
            else
                result = findParentForInsert(node->left, index, postOrderStack);
        }
        else {
            if(node->right == nullptr)
                result = pair<BinaryNode *, bool>(node, false);
            else
                result = findParentForInsert(node->right, index - node->leftSubtreeSize - 1, postOrderStack);
            turnedLeft = false;
        }
        postOrderStack.push_back(pair<BinaryNode *, bool>(node, turnedLeft));
        return result;
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
    void rotate(BinaryNode * node, int move, bool force = false){
        
    }

};

int main() {
    AVLTree avlTree;
    for(int i = 0; i < 20; i ++) {
        avlTree.insert(0, i);
        avlTree.showStructure();
        cout<<"";
    }
   // avlTree.insert(3, 3);
  //  avlTree.insert(4, 4);
   // avlTree.insert(5, 5);
    cout<<"";
   for(int i = 0; i < avlTree.treeSize; i++){
       cout<<avlTree.getValue(i)<<" ";
   }
    cout<<"";
    return 0;
}
