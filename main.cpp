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

    /*void insert(int index, int value){
        if(root == nullptr){
            root = new BinaryNode(0);
            root->value = value;
            ++ treeSize;
            testContainer.push_back(root);
            root->levelInTree = 0;
            return;
        }
        vector<pair<BinaryNode *, pair<bool, int>>> postOrderStack;
        pair<BinaryNode *, bool> p = insert(root, index, postOrderStack);
        if(p.second){
            BinaryNode * left = new BinaryNode(treeSize);
            left->parent = p.first;
            left->value = value;
            ++ treeSize;
            p.first->left = left;
            left->levelInTree = p.first->levelInTree + 1;

            testContainer.push_back(left);
        }else{
            BinaryNode * right = new BinaryNode(treeSize);
            right->parent = p.first;
            right->value = value;
            ++ treeSize;
            p.first->right = right;
            right->levelInTree = p.first->levelInTree + 1;

            testContainer.push_back(right);
        }
        for(auto pair : postOrderStack){
            BinaryNode * n = pair.first;
            bool left = pair.second.first;
            left ? ++n->leftSubtreeSize : ++n->rightSubtreeSize;
            if(pair.second.first){
                if(n->leftHeight < pair.second.second){
                    n->leftHeight = pair.second.second;
                }
            }
            else{
                if(n->rightHeight < pair.second.second){
                    n->rightHeight = pair.second.second;
                }
            }
            cout<<"";
        }
        for(auto it = postOrderStack.rbegin(); it != postOrderStack.rend(); ++it){
            BinaryNode * n = it->first;
            ///todo rotate to fix
            int type;
            auto tmpIT = it;
            if(tmpIT->second.first){
                //L
                type = 0;
                if((++ tmpIT) != postOrderStack.rend()){
                    if(!tmpIT->second.first){
                        type = 1;
                        //LR
                    }
                }
            }
            else{
                //R
                type = 2;
                if((++ tmpIT) != postOrderStack.rend()){
                    if(tmpIT->second.first){
                        type = 4;
                        //LR
                    }
                }
            }
            rotation(n, type);
        }
        //todo test the rotation type
        cout<<"";
    }
*/
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
    void insert(int index, int value){
        if(root == nullptr){
            root = new BinaryNode(treeSize);
            ++ treeSize;
            testContainer.push_back(root);
            root->value = value;
        }
        else {
            insert(root, index, value);
        }
    }
private:
    int insert(BinaryNode * node, int index, int value){//node, <left/right, reachableHeight
        int maxHeight = 0;
        bool turnedLeft = true;
        if(index > treeSize ){
            cout<<"INVALID ENTRY!";
            maxHeight = -1;
            return maxHeight;
        }
        if(index <= node->leftSubtreeSize){
            if(node->left == nullptr) {
                BinaryNode * left = new BinaryNode(treeSize);
                left->parent = node;
                left->value = value;
                ++ treeSize;
                node->left = left;

                testContainer.push_back(left);
                maxHeight = 1;
            }
            else {
                maxHeight = insert(node->left, index, value);
            }
        }
        else {
            if(node->right == nullptr) {
                BinaryNode * right = new BinaryNode(treeSize);
                right->parent = node;
                right->value = value;
                ++ treeSize;
                node->right = right;

                testContainer.push_back(right);
                maxHeight = 1;
            }
            else
                maxHeight = insert(node->right, index - node->leftSubtreeSize - 1, value);
            turnedLeft = false;
        }
        if(turnedLeft){
            node->leftSubtreeSize ++;
            if(node->leftHeight < maxHeight){
                node->leftHeight = maxHeight;
            }
        }else{
            node->rightSubtreeSize ++;
            if(node->rightHeight < maxHeight){
                node->rightHeight = maxHeight;
            }
        }
        //time to check for imbalances
        return maxHeight + 1;
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
