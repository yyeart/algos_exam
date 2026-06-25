#include <stdio.h>

typedef struct Node{
    int data;
    struct Node* left;
    struct Node* right;
} Node;

void preOrder(Node* root){
    if(!root) return;
    printf("%d ", root->data);
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(Node* root){
    if(!root) return;
    inOrder(root->left);
    printf("%d ", root->data);
    inOrder(root->right);
}

void postOrder(Node* root){
    if(!root) return;
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->data);
}