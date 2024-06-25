#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEVEL 6

// Define a structure for skip list nodes
typedef struct Node {
    int value;
    struct Node **forward;
} Node;

// Define a structure for the skip list
typedef struct SkipList {
    int level;
    Node *header;
} SkipList;

// Function to create a new node
Node* createNode(int level, int value) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->forward = (Node**)malloc(sizeof(Node*) * (level + 1));
    for (int i = 0; i <= level; i++) {
        node->forward[i] = NULL;
    }
    return node;
}

// Function to create a new skip list
SkipList* createSkipList() {
    SkipList *list = (SkipList*)malloc(sizeof(SkipList));
    list->level = 0;
    list->header = createNode(MAX_LEVEL, 0);
    return list;
}

// Function to generate a random level for a new node
int randomLevel() {
    int level = 0;
    while (rand() % 2 && level < MAX_LEVEL) {
        level++;
    }
    return level;
}

// Function to insert a value into the skip list
void insert(SkipList *list, int value) {
    Node *update[MAX_LEVEL + 1];
    Node *current = list->header;

    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->value < value) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];

    if (current == NULL || current->value != value) {
        int newLevel = randomLevel();

        if (newLevel > list->level) {
            for (int i = list->level + 1; i <= newLevel; i++) {
                update[i] = list->header;
            }
            list->level = newLevel;
        }

        Node *newNode = createNode(newLevel, value);

        for (int i = 0; i <= newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }

        printf("Inserted value: %d\n", value);
    }
}

// Function to print the skip list
void printSkipList(SkipList *list) {
    printf("Skip List:\n");
    for (int i = list->level; i >= 0; i--) {
        Node *node = list->header->forward[i];
        printf("Level %d: ", i);
        while (node != NULL) {
            printf("%d ", node->value);
            node = node->forward[i];
        }
        printf("\n");
    }
}

// Main function
int main() {
    srand(time(NULL));

    SkipList *list = createSkipList();

    int choice, value;
    do {
        printf("1. Insert\n2. Print\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insert(list, value);
                break;
            case 2:
                printSkipList(list);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 3);
    //to-do free memory
    return 0;
}
