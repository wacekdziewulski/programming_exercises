#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    void* left;
    void* right;
    int value;
} Node;

void deleteNode(Node* node) {
    free(node);
    node = NULL;
}

void printNodeValue(Node* node) {
    printf("%d", node->value);
}

Node* allocateNode(int value) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->value = value;
    return node;
}

/* @return -> indicates if the addition of the node was successful */
bool addNode(Node** root, int value) {

    Node** currentNode = root;
    Node* originalRoot = *root;
    Node* newNode = allocateNode(value);

    if (!newNode) {
        return false;
    }

    bool rootAdded = false;

    while (1) {
        if (!*currentNode) {
            *currentNode = newNode;
            rootAdded = true;
            break;
        }
        else if ((*currentNode)->value < value) {
            if (!(*currentNode)->left) {
                (*currentNode)->left = newNode;
                break;
            }
            else {
                *currentNode = (*currentNode)->left;
            }
        }
        else {// (root->value >= value) {
            if (!(*currentNode)->right) {
                (*currentNode)->right = newNode;
                break;
            }
            else {
                *currentNode = (*currentNode)->right;
            }
        }
    }

    if (!rootAdded) {
        *root = originalRoot;
    }

    return true;
}

bool addNodeInternal(Node** node, int value) {
}

void dfs(Node* node, void (action)(Node*)) {
    if (!node) {
        return;
    }

    dfs(node->left, action);

    if (action) {
        (*action)(node);
    }

    dfs(node->right, action);
}

int main (char** argv, int argc) {
    Node* tree = NULL;
    addNode(&tree, 3);
    addNode(&tree, 1);
    addNode(&tree, 2);
    addNode(&tree, 5);
    addNode(&tree, 4);
    addNode(&tree, 6);
    dfs(tree, &printNodeValue);

    return 0;
}
