#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int key){
    Node* n = (Node*)malloc(sizeof(Node));
    if(!n) return;
    n->key = key;
    n->left = n->right = NULL;
    return n;
}

Node* insertNode(Node* root, int key){
    if(!root) return createNode(key);
    if (key < root->key) root->left = insertNode(root->left, key);
    else if(key > root->key) root->right = insertNode(root->right, key);
    return root;
}

Node* searchNode(Node* root, int key){
    if(!root || root->key == key) return root;
    if(key < root->key) return search(root->left, key);
    return search(root->right, key);
}

Node* findMin(Node* root){
    Node* curr = root;
    while (curr && curr->left) curr = curr->left;
    return curr;
}

Node* deleteNode(Node* root, int key){
    if(!root) return root;
    if(key < root->key) root->left = deleteNode(root->left, key);
    else if(key > root->key) root->right = deleteNode(root->right, key);
    else {
        if(!root->left){
            Node* tmp = root->right;
            free(root);
            return tmp;
        }
        else if(!root->right){
            Node* tmp = root->left;
            free(root);
            return tmp;
        }
        Node* tmp = findMin(root->right);
        root->key = tmp->key;
        root->right = deleteNode(root->right, tmp->key);
    }
    return root;
}

void freeTree(Node* root){
    if(!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}