#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int key;
    int count; 
    long totalValue; 
    TreeNode* left;
    TreeNode* right;

    TreeNode(int k) : key(k), count(1), totalValue(k), left(nullptr), right(nullptr) {}

};

class BST {
private:
    TreeNode* root;
    bool isKEven;

    TreeNode* insert(TreeNode* node, int key) {
        if (node ==nullptr) {
            return new TreeNode(key);
        }

        node->count++;
        node->totalValue+=key;
        
        if (key < node->key) {
            node->left = insert(node->left, key);
        } else {
            node->right = insert(node->right, key);
        }

        return node;
    }

    int size(TreeNode* node){
        return (node == nullptr) ? 0 : node->count;
    }

    TreeNode* findMin(TreeNode* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    long sumValues(TreeNode* node){
        return (node == nullptr) ? 0 : node->totalValue;
    }

    TreeNode* deleteNode(TreeNode* node, int key) {
        if (node==nullptr) {
            return nullptr;
        }
        node->count--;
        node->totalValue-=key;

        if (key < node->key) {
            node->left = deleteNode(node->left, key);
        } else if(key > node->key){
            node->right = deleteNode(node->right, key);
        }  else{
             if (node->left == nullptr) {
                    return node->right;
                } else if (node->right == nullptr) {
                    return node->left;
                }
                TreeNode* temp = findMin(node->right);
                node->key = temp->key;
                node->right = deleteNode(node->right, temp->key);
        }
        
        return node;
    }

    TreeNode* search(TreeNode* node, int key) {
        if (!node || key == node->key) {
            return node;
        }

        if (key < node->key) {
            return search(node->left, key);
        }

        return search(node->right, key);
    }

public:
    BST(bool isKEven) {
        this->root=nullptr;
        this->isKEven=isKEven;
    }


    void insert(int key) {
        root = insert(root, key);
    }

    void deleteNode(int key) {
        root = deleteNode(root, key);
    }

    TreeNode* search(int key) {
        return search(root, key);
    }

    long getDistanceFromNode(long smallerSum, long biggerSum, TreeNode* root, int remainedIndex) {
            
            TreeNode* newRoot;
            if(size(root->left)==remainedIndex ){
                smallerSum+=sumValues(root->left);
                biggerSum+=sumValues(root->right);

                if(isKEven)
                    biggerSum+=root->key;

                return biggerSum-smallerSum;
            }

            else if(size(root->left)==0)
                return getDistanceFromNode(smallerSum+root->key, biggerSum, root->right, remainedIndex-1);

            else if(size(root->right)==0)
                return getDistanceFromNode(smallerSum, biggerSum+root->key, root->left, remainedIndex);
            
            else if (size(root->left) < remainedIndex) {
                remainedIndex -= root->left->count+1;
                smallerSum += sumValues(root->left)+root->key;
                newRoot = root->right;
                return getDistanceFromNode(smallerSum, biggerSum, newRoot, remainedIndex);
            }

            else {
                biggerSum+= sumValues(root->right)+root->key;
                newRoot=root->left;
                return getDistanceFromNode(smallerSum,biggerSum,newRoot,remainedIndex);
            }

        }

    long getDistanceFromMedian() {
            return getDistanceFromNode(0, 0, this->root, this->root->count / 2);
        }
};

int n,k;
vector <int> elements[200000];
BST* Tree=nullptr;

void get_inputs() {
        cin >> n >> k;

        int temp;
        for (int i = 0; i < n; i++) {
            cin >>temp;
            elements->push_back(temp);
        }
}

    void initializeTree() {
        Tree = new BST(k%2==0);
        for (int i = 0; i < k; i++) {
            Tree->insert(elements->at(i));
        }
    }

    void edit_tree(int step) {
        if(step==n-k)
            return;
        Tree->deleteNode(elements->at(step));
        Tree->insert( elements->at(step + k));
    }

    void get_answer(int i) {
        long operations_count = Tree->getDistanceFromMedian();
        cout << operations_count <<" ";
        edit_tree(i);
    }



int main() {
    ios::sync_with_stdio(false);
    get_inputs();

    initializeTree();

    for (int i = 0; i < n-k+1; i++)
        get_answer(i);

    return 0;
}