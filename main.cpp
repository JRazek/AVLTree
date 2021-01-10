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
        stack<pair<BinaryNode *, bool>> postOrderStack;
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
            BinaryNode * n = postOrderStack.top().first;
            bool left = postOrderStack.top().second;
            postOrderStack.pop();
            left ? ++n->leftSubtreeSize : ++n->rightSubtreeSize;
            int balanceVal = n->leftSubtreeSize - n->rightSubtreeSize;
            cout<<"";
            balance(n, balanceVal);
            cout<<"";
        }
        cout<<"";
    }
    void remove(int index){
        stack<pair<BinaryNode *, bool>> postOrderStack;
        pair<BinaryNode *, bool> p = findParent(root, index, postOrderStack);
        delete p.first;
        p.first = nullptr;
        -- this->treeSize;

        while(!postOrderStack.empty()){
            BinaryNode * n = postOrderStack.top().first;
            bool left = postOrderStack.top().second;
            postOrderStack.pop();
            left ? --n->leftSubtreeSize : --n->rightSubtreeSize;

            int balanceVal = n->leftSubtreeSize - n->rightSubtreeSize;
            balance(n, balanceVal);
        }
    }
    int getValue(int index){
        stack<pair<BinaryNode *, bool>> postOrderStack;
        pair<BinaryNode *, bool> p = findParent(root, index, postOrderStack);
        return (p.first->value);
    }
private:
    //finds the parent of the node were looking for and the bool - if true - left child if false - right child
    pair<BinaryNode *, bool> findParent(BinaryNode * node, int index, stack<pair<BinaryNode *, bool>> &postOrderStack){
        pair<BinaryNode *, bool> result;
        bool turnedLeft = true;
        if(index > treeSize ){
            cout<<"INVALID ENTRY!";
            result = pair<BinaryNode *, bool>(nullptr, 0);
        }
        ///heres the invalid read //todo
        if(node->leftSubtreeSize >= index){
            if(node->left == nullptr){
                result = pair<BinaryNode *, bool>(node, true);
            }
            else
                result = findParent(node->left, index, postOrderStack);
        }
        else {
            if(node->right == nullptr){
                result = pair<BinaryNode *, bool>(node, false);
            }
            else
                result = findParent(node->right, index - node->leftSubtreeSize - 1, postOrderStack);
            turnedLeft = false;
        }
        postOrderStack.push(pair<BinaryNode *, bool>(node, turnedLeft));
        return result;
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

            if(rightChild->leftSubtreeSize < 0){
                cout<<"WTF";
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
    AVLTree avlTree;

    avlTree.insert(0, 5);
    avlTree.insert(0, 4);
    avlTree.insert(0, 3);
    avlTree.insert(0, 2);
    avlTree.insert(0, 1);
   // avlTree.insert(3, 3);
  //  avlTree.insert(4, 4);
   // avlTree.insert(5, 5);

   for(int i = 0; i < avlTree.treeSize; i++){
       cout<<avlTree.getValue(i)<<" ";
   }

    cout<<"";
    return 0;
}
