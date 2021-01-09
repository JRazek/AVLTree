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
    int treeSize = 1;
    AVLTree(int firstVal){
        root = new BinaryNode(0);
    }

    void insert(int value, int index){
        stack<BinaryNode *> postOrderStack;
        pair<BinaryNode *, bool> p = findParent(root, index, postOrderStack);
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
        while(!postOrderStack.empty()){
            BinaryNode * n = postOrderStack.top();
            postOrderStack.pop();
            if(n->parent != nullptr){
                (n->parent->left == n ? n->parent->leftSubtreeSize ++ : n->parent->leftSubtreeSize --);
            }
            int balanceVal = n->leftSubtreeSize - n->rightSubtreeSize;
            balance(n, balanceVal);
        }
    }
    int getValue(int index){
        stack<BinaryNode *> postOrderStack;
        pair<BinaryNode *, bool> p = findParent(root, index, postOrderStack);
        return (p.first->value);
    }
private:
    //finds the parent of the node were looking for and the bool - if true - left child if false - right child
    pair<BinaryNode *, bool> findParent(BinaryNode * node, int index, stack<BinaryNode *> &postOrderStack){

        if(index > treeSize - 1){
            cout<<"INVALID ENTRY!";
            return pair<BinaryNode *, bool>(nullptr, 0);
        }
        if(node->leftSubtreeSize >= index){
            if(node->left == nullptr){
                return pair<BinaryNode *, bool>(node, true);
            }
            else
                return findParent(node->left, index, postOrderStack);
        }
        else {
            if(node->right == nullptr){
                return pair<BinaryNode *, bool>(node, false);
            }
            else
                return findParent(node->right, index - node->leftSubtreeSize - 1, postOrderStack);
        }
    }
    void insert(int val, BinaryNode * node, int index, stack<BinaryNode *> &balanceStack){
        node->rightSubtreeSize++;
        if(node->right == nullptr){
            BinaryNode * right = new BinaryNode(treeSize);
            right->parent = node;
            right->value = val;
            ++treeSize;
            node->right = right;
        }else{
            insert(val, node->right, index, balanceStack);
        }
        balanceStack.push(node);
    }


    void balance(BinaryNode * node, int move){
        if(move < -1){
            //right is too big
            //check if right child has left child
            if(node->right->left != nullptr){
                //first move child
                balance(node->right, node->right->leftSubtreeSize);
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

            balance(rightChild, move + 1);
        }
        else if(move > 1){
            if(node->left->right != nullptr){
                balance(node->left, -node->left->rightSubtreeSize);
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

            balance(leftChild, move - 1);
        }

    }
};

int main() {
    AVLTree avlTree(0);
    avlTree.insert(1, 0);
   // avlTree.insert(2, 2);
   // avlTree.insert(3, 3);
  //  avlTree.insert(4, 4);
   // avlTree.insert(5, 5);

    cout<<avlTree.getValue(0);
    //avlTree.insert(avlTree.treeSize);
    //avlTree.insert(avlTree.treeSize);
   // avlTree.insert(avlTree.treeSize);
  //  avlTree.insert(avlTree.treeSize);

    cout<<"";
    return 0;
}
