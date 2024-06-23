//  For a tutorial of Binary Search Trees, watch 
//  https://youtu.be/MKxBOHLxeGg?si=zTkWieujex9Npm0F
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BinaryTreeNode{
    int highScore;
    char username[100];
    struct BinaryTreeNode* leftChild;
    struct BinaryTreeNode* rightChild;
}bst;

bst* add(bst* root, bst* node){

    if (root==NULL){ //empty binary tree
        root = node;
    }
    else if (strcmp(root->username, node->username) <0) {
         //new user name is greater than root aphabetically, move to rightChild
        if (root->rightChild == NULL){
            root->rightChild = node;
        }
        else{
            add(root->rightChild, node);
        }
    }
    else if (strcmp(root->username, node->username) >0) {
        //new user name is less than root aphabetically, move to leftChild
        if (root->leftChild == NULL){
            root->leftChild = node;
        }
        else{
            add(root->leftChild, node);
        }
       
    }
    else{
        printf("A user with this name already exists.  Select a different username.");
    }
    return root;
}

void printTree(bst* root){
    if (root != NULL){
        //in order traversal to print smallest to largest username
        printTree(root->leftChild);
        printf("%s - %d\n", root->username, root->highScore);
        printTree(root->rightChild);
    }
}

int main(){
    bst* root=NULL;
    bst* node; 
    int op;
    do{
        printf("1=add user, 2=update user, 3=delete user, 4=print users, 5=exit");
        scanf("%d", &op);
        if (op==1){
            node = (bst*)malloc(sizeof(bst));
            printf("Enter new user name:");
            scanf("%s", node->username);
            printf("Enter high score:");
            scanf("%d", &node->highScore);
            node->leftChild = NULL;
            node->rightChild = NULL;
            root = add(root, node);
        }
        else if (op==4){
            printTree(root);
        }
    } while (op != 5);
    //to-do release all allocated memory
    return 0;
}
