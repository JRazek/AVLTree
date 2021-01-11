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
            testContainer.push_back(newNode);
            ++ treeSize;
        }
    }
private:
    void insert(BinaryNode * node, int index, BinaryNode * insertedNode, vector<bool> &directions){//node, <left/right, reachableHeight
        bool turnedLeft = true;
        if(index > treeSize ){
            cout<<"INVALID ENTRY!";
            return;
        }
        if(index <= node->leftSubtreeSize){
            node->leftSubtreeSize ++;

            if(node->left == nullptr) {
                node->left = insertedNode;
                insertedNode->parent = node;
                max(insertedNode->leftHeight, insertedNode->rightHeight) + 1;
            }
            else {
                insert(node->left, index, insertedNode, directions);
            }
        }
        else {
            node->rightSubtreeSize ++;

            if(node->right == nullptr) {
                node->right = insertedNode;
                insertedNode->parent = node;
                max(insertedNode->leftHeight, insertedNode->rightHeight) + 1;
            }
            else
                insert(node->right, index - node->leftSubtreeSize - 1, insertedNode, directions);
            turnedLeft = false;
        }
        updateNode(node);
        directions.push_back(turnedLeft);

        //time to check for imbalances
        int balance = node->leftHeight - node->rightHeight;
        if(abs(balance) > 1){
            int imbalanceType;
            if(directions.size() >= 2){
                int nodesIndex = directions.size() - 1;
                if(directions[nodesIndex - 1]){
                    //LL path
                    imbalanceType = 0;
                    if(directions.size() >= 3){
                        if(!directions[nodesIndex - 2]) {
                            imbalanceType = 1;
                            //LR path
                        }
                    }
                }else{
                    imbalanceType = 2;
                    //RR path
                    if(directions.size() >= 3){
                        if(directions[nodesIndex - 2]) {
                            imbalanceType = 3;
                            //RL path
                        }
                    }
                }
            }
            if(abs(balance) > 2){
                cout<<"WTF\n";
            }
            switch(imbalanceType){
                    case 0:
                        rightRotation(node);
                        break;
                    case 1:
                        rightRotation(node->left);
                        leftRotation(node);
                        break;
                    case 2:
                        leftRotation(node);
                        break;
                    case 3:
                        leftRotation(node->right);
                        rightRotation(node);
                        break;
            }
        }

    }
    void rightRotation(BinaryNode * node){
        BinaryNode * parent = node->parent;
        BinaryNode * leftChild = node->left;

        if(parent != nullptr){
            (parent->left == node ? parent->left = leftChild : parent->right = leftChild);
        }
        node->parent = leftChild;
        node->left = nullptr;
        node->leftHeight = 0;
        node->leftSubtreeSize = 0;

        if(leftChild->right != nullptr) {
            vector<bool> dirs;
            insert(node, 0, leftChild->right, dirs);
        }
        leftChild->right = node;
        leftChild->parent = parent;


        updateNode(node);
        updateNode(leftChild);
        if(parent != nullptr)
            updateNode(parent);

        if(node == root){
            root = leftChild;
        }
        cout<<"";
    }
    void leftRotation(BinaryNode * node){
        BinaryNode * parent = node->parent;
        BinaryNode * rightChild = node->right;

        if(parent != nullptr){
            (parent->left == node ? parent->left = rightChild : parent->right = rightChild);
        }
        node->parent = rightChild;
        node->right = nullptr;
        node->rightHeight = 0;
        node->rightSubtreeSize = 0;

        if(rightChild->left != nullptr) {
            vector<bool> dirs;
            insert(node, node->leftHeight + 1, rightChild->left, dirs);
        }
        rightChild->left = node;
        rightChild->parent = parent;

        updateNode(node);
        updateNode(rightChild);
        if(parent != nullptr)
            updateNode(parent);

        if(node == root){
            root = rightChild;
        }
    }
    void updateNode(BinaryNode * n){
        int lH = 0, lT = 0;
        if(n->left != nullptr) {
            lH++, lT++;
            lH += max(n->left->leftHeight, n->left->rightHeight);
            lT += n->left->leftSubtreeSize + n->left->rightSubtreeSize;
        }
        n->leftHeight = lH;
        n->leftSubtreeSize = lT;

        int rH = 0, rT = 0;
        if(n->right != nullptr) {
            rH++, rT++;
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
    avlTree.insert(0, 1);
    avlTree.insert(1, 2);
    avlTree.insert(2, 3);
    avlTree.insert(3, 4);
    avlTree.insert(4, 5);
    avlTree.insert(5, 6);
    cout<<"";
   for(int i = 0; i < avlTree.treeSize; i++){
       cout<<avlTree.getValue(i)<<" ";
   }
    cout<<"";
    return 0;
}
