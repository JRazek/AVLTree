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
    BinaryNode * root;
    int treeSize = 0;

    void insert(int index, int value){
        if(root == nullptr){
            root = new BinaryNode(0);
            root->value = value;
            ++ treeSize;
            return;
        }
        vector<pair<BinaryNode *, bool>> postOrderStack;
        pair<BinaryNode *, bool> p = findParentForInsert(root, index, postOrderStack);
        if(p.second){
            BinaryNode * left = new BinaryNode(treeSize);
            left->parent = p.first;
            left->value = value;
            ++treeSize;
            p.first->left = left;
        }else{
            BinaryNode * right = new BinaryNode(treeSize);
            right->parent = p.first;
            right->value = value;
            ++treeSize;
            p.first->right = right;
        }
        for(auto pair : postOrderStack){
            BinaryNode * n = pair.first;
            bool left = pair.second;
            left ? ++n->leftSubtreeSize : ++n->rightSubtreeSize;
            cout<<"";
        }
        for(auto it = postOrderStack.rbegin(); it != postOrderStack.rend(); ++it){
            BinaryNode * n = it->first;
            int balanceVal = n->leftSubtreeSize - n->rightSubtreeSize;
            ///todo balance to fix
            balance(it->first, balanceVal);
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
    void balance(BinaryNode * node, int move, bool force = false){
        if(move < -1 || (move < 0 && force)){
            //right is too big
            //check if right child has left child
            if(node->right->left != nullptr){
                //first move child
                balance(node->right, node->right->leftSubtreeSize, true);
            }

            BinaryNode * rightChild = node->right;
            if(node != root)
                if(node->parent->left == node)
                    node->parent->left = rightChild;
                else
                    node->parent->right = rightChild;

            rightChild->parent = node->parent;
            rightChild->left = node;
            rightChild->leftSubtreeSize = node->leftSubtreeSize + 1;

            node->parent = rightChild;
            node->right = nullptr;
            node->rightSubtreeSize = 0;

            if(node == this->root){
                root = rightChild;
            }

            if(rightChild->leftSubtreeSize < 0){
                cout<<"WTF";
            }

            balance(rightChild, move + 1, force);
        }
        else if(move > 1 || (move > 0 && force)){
            if(node->left->right != nullptr){
                balance(node->left, -node->left->rightSubtreeSize, true);
            }

            BinaryNode * leftChild = node->left;
            if(node != root)
                if(node->parent->left == node)
                    node->parent->left = leftChild;
                else
                    node->parent->right = leftChild;

            leftChild->parent = node->parent;
            leftChild->right = node;
            leftChild->rightSubtreeSize = node->rightSubtreeSize + 1;

            node->parent = leftChild;
            node->left = nullptr;
            node->leftSubtreeSize = 0;

            if(node == this->root){
                root = leftChild;
            }

            balance(leftChild, move - 1, force);
        }

    }
};

int main() {
    AVLTree avlTree;

    avlTree.insert(0, 11);
    avlTree.insert(0, 10);
    avlTree.insert(0, 9);
    avlTree.insert(0, 8);
    avlTree.insert(0, 7);
    avlTree.insert(0, 6);
    avlTree.insert(0, 5);
    avlTree.insert(0, 4);
    avlTree.insert(0, 3);
    avlTree.insert(0, 2);
    avlTree.insert(0, 1);
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
