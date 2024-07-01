#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

// Define a structure for skip list nodes
typedef struct Node {
    int value;
    struct Node *prev;
    struct Node *next;
    struct Node *up;  //null if not used
    struct Node *down; //null if not used
} Node;

typedef struct linkedlistnode{
    Node* n;
    struct linkedlistnode *next;
}LinkedListNode;

// Define a structure for the skip list
typedef struct skiplist {
    int level; //layers in our skip list
    Node *header;
} SkipList;
void printLayer(Node* n){
    while (n != NULL){
        printf("%d ", n->value);
        n=n->next;
    }
}
void freeLinkedList(LinkedListNode *l){
    LinkedListNode *a;
    while(l!=NULL){
        a=l;
        l=l->next;
        free(a);
    }
}

void printSL(SkipList* s){
    int layers=s->level;
    Node* n = s->header;
    
    while (layers >=0){
        printf("(S%d) ********* ", layers);
        printLayer(n);
        layers--;
        n=n->down;
        printf(" ********\n");
    }
    
}


int flipCoin(){
    //0= tails, 1=heads
    return rand()%2;
}
int levelAssignment(){
    int numHeads = 0;
    while (flipCoin()){
        numHeads++;
    }
    return numHeads;
}

Node* createNode(){
    Node* n = (Node*)malloc(sizeof(Node));
    n->prev = NULL;
    n->next = NULL;
    n->up = NULL;
    n->down = NULL;
    return n;
}
LinkedListNode* whereToAdd(Node* n,int x,LinkedListNode* whereToAddNew){
    LinkedListNode* ptr;
    if (n->next->value > x){
        ptr=(LinkedListNode*) malloc(sizeof(LinkedListNode));
        ptr->n = n;
        ptr->next = whereToAddNew;  //finish
       if (n->down == NULL){
           return ptr;
       }
       n=n->down;
       return whereToAdd(n, x, ptr);
    }
    else{
        n=n->next;
        return whereToAdd(n, x, whereToAddNew);
    }
}
Node* find(int x, Node* n){
    while(n->next->value <= x){
        n=n->next;
    }
    if (n->value == x){
        printf("Found.\n");
        return n;
    }
    if (n->down==NULL){
        printf("ERROR - not in list.\n");
        return NULL;
    }
    printf("at:%d\n", n->value);
    
    n=n->down;
    
    return find(x, n);
}

void deleteNode(SkipList* s){
    int x;
    Node* n=s->header;
    Node* f, prev,next, *z;
    printf("What do you want to delete:");
    scanf("%d", &x);
    f=find(x, n);
    while (f != NULL){
        f->prev->next = f->next;
        f->next->prev=f->prev;
        z=f;
        f=f->down;
        free(z);
    }
    
}
void add(SkipList* s){
    int x,numHeads;
    LinkedListNode* whereToAddNew=NULL, *orig;
    Node* n2, *n3, *n4;
    printf("What do you want to add:");
    scanf("%d", &x);
    
    numHeads = levelAssignment();
    if (numHeads > s->level ){ //add at most 1 new level
        numHeads=s->level;
    }
    printf("level = %d\n", numHeads);
    
    Node* n = s->header;
    while (numHeads >= s->level){
        n3 = createNode();
        n->up = n3;
        n3->value = n->value;
        n3->down = n;
        
        n4 = createNode();
        n4->value = INT_MAX;
        n3->next = n4;
        n4->prev = n3;
        n4->down = n->next;
        n->next->up = n4;
        s->level++;
        s->header = n3;
        n=n3;
    }
    //find where to add new item
    orig= whereToAddNew= whereToAdd(s->header, x,whereToAddNew);
    n2=createNode();
    //printf("n=%d\n", n2->value);
    n2->value = x;
    n2->prev = whereToAddNew->n;
    n2->next = whereToAddNew->n->next;
    whereToAddNew->n->next->prev = n2;
    whereToAddNew->n->next = n2;
    whereToAddNew = whereToAddNew->next;
    //Add to bottom layer
    while (numHeads >0) {
        n3=n2; //previos new node
        n2=createNode();
        n2->down = n3;
        n3->up = n2;
        //printf("n=%d\n", n2->value);
        n2->value = x;
        n2->prev = whereToAddNew->n;
        n2->next = whereToAddNew->n->next;
        whereToAddNew->n->next->prev = n2;
        whereToAddNew->n->next = n2;
        whereToAddNew = whereToAddNew->next;
        numHeads--;
    }
    printf(" ********\n");
    //free whereToAdd memory
    freeLinkedList(orig);
}


int main()
{
    int op=0;
    SkipList sl;
    
    srand(0);
    sl.level = 0;
    sl.header = createNode();
    sl.header->value = INT_MIN;
    
    sl.header->next = createNode();
    sl.header->next->value = INT_MAX;
    sl.header->next->prev = sl.header;
    
    printSL(&sl);
    while (op <5){
        printf("1= add node, 2= delete node, 3=print all\n");
        scanf("%d", &op);
        if (op ==1){
            add(&sl);
        }
        else if (op == 2)
            deleteNode(&sl);
        else if (op == 3)
            printSL(&sl);
    }
    
    return 0;
}
