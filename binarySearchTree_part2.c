// YouTube video  https://youtu.be/1Qk6if4pl6s?si=_bZmtBlu7Mo71xVS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BinaryTreeNode{
    int highScore;
    char username[100];
    struct BinaryTreeNode* leftChild;
    struct BinaryTreeNode* rightChild;
}bst;

bst* add(bst* root, bst*node){
    if (root == NULL){ //empty tree
        root = node;
    }
    else if (strcmp(root->username, node->username) < 0){
        //new user name goes on right side of tree
        if (root->rightChild == NULL){
            root->rightChild = node;
        }
        else{
            add(root->rightChild, node);
        }
    }
     else if (strcmp(root->username, node->username) > 0){
        //new user name goes on left side of tree
        if (root->leftChild == NULL){
            root->leftChild = node;
        }
        else{
            add(root->leftChild, node);
        }
    }
    else{
        printf("A user with that name already exists.  Select a new name.\n");
         free(node);
    }
    return root;
}
void updateTree(bst* root){
    char user[100];
    bst* r=root;
    printf("Enter username to update: ");
    scanf("%s", user);
    while (r != NULL){
        if (strcmp(r->username, user)==0){
            printf("Enter new high score: ");
            scanf("%d", &r->highScore);
            return;
        }
        else if (strcmp(r->username, user) > 0){
            //user on left side of the tree
            if (r->leftChild != NULL){
                r=r->leftChild;
            }
        }
        else if (strcmp(r->username, user) < 0){
            //user on right side of the tree
            if (r->rightChild != NULL){
                r=r->rightChild;
            }
        }
    }
    printf("User does not exist.\n");
   
}

void printTree(bst* root){
    if (root != NULL){
        //in order traversal
        printTree(root->leftChild);
        printf("%s - %d\n", root->username, root->highScore);
        printTree(root->rightChild);
    }
}

bst* findMin(bst* root) {
    while (root->leftChild != NULL) {
        root = root->leftChild;
    }
    return root;
}

bst* delete(bst* root, char username[]) {
    if (root == NULL) {
        printf("User not found.\n");
        return root;
    }
    if (strcmp(username, root->username) < 0) {
        root->leftChild = delete(root->leftChild, username);
    } else if (strcmp(username, root->username) > 0) {
        root->rightChild = delete(root->rightChild, username);
    } else {
        // Node to be deleted found
        if (root->leftChild == NULL) {
            bst* temp = root->rightChild;
            free(root);
            return temp;
        } else if (root->rightChild == NULL) {
            bst* temp = root->leftChild;
            free(root);
            return temp;
        } else {
            // Node with two children
            bst* temp = findMin(root->rightChild);
            strcpy(root->username, temp->username);
            root->highScore = temp->highScore;
            root->rightChild = delete(root->rightChild, temp->username);
        }
    }
    return root;
}

void freeTree(bst* root) {
    if (root != NULL) {
        freeTree(root->leftChild);
        freeTree(root->rightChild);
        free(root);
    }
}

int main(){
    bst* root=NULL;
    bst* node;
    int op;
    char user[100];
    
    do{
        printf("1=add 2=update 3=delete 4=list all 5=exit : ");
        scanf("%d", &op);
        if (op == 1){
            node = (bst*) malloc(sizeof(bst));
            printf("Enter a new username: ");
            scanf("%s", node->username);
            printf("Enter a high score: ");
            scanf("%d", &node->highScore);
            node->leftChild = NULL;
            node->rightChild = NULL;
            root = add(root, node);
        }
        else if (op==2){
            updateTree(root);
        }
        else if (op==3){
            printf("Enter the username to delete: ");
            scanf("%s", user);
            root = delete(root, user);
        }
        else if (op==4){
            printTree(root);
        }
       
    } while (op < 5);
    
    // Free all allocated memory before exiting
    freeTree(root);


  return 0;
}
