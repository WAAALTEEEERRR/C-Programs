```c
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int position = 0;

// the node data struct
struct node {
    char val[50];
    int position;
    struct node* leftNode, * rightNode;
};

// A utility function to create a BST node
struct node* newNode(char item[50], int position) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    strcpy_s(temp->val, 50, item);
    temp->position = position;
    temp->leftNode = temp->rightNode = NULL;
    return temp;
}

// A utility function to do inorder traversal of BST
void preorder(struct node* root)
{
    if (root != NULL) {
        printf("<<value: %s ; position: %d>> \n", root->val, position);
        preorder(root->leftNode);
        preorder(root->rightNode);
    }
}

// Search element in the tree function
bool Search(struct node* root, char key[50]) {
    if (root == NULL) {
        // root is NULL the value isn't in the tree return false
        return false;
    }
    else {
        if (strcmp(root->val, key) < 0) {
            //key is smaller than the data, so we will search the left subtree
            Search(root->leftNode, key);
        }
        else if (strcmp(root->val, key) > 0) {
            // key is greater, so we will search the right subtree
            Search(root->rightNode, key);
        }
        else if (strcmp(root->val, key) == 0) {
            // found the value in the tree return true
            return true;
        }
    }
}

/* A utility function to
insert a new node with given key in
* BST */
struct node* insert(struct node* node, char key[50], int position) {
    /* If the tree is empty, return a new node */
    if (node == NULL) {  
        return newNode(key, position);
    }

    // value is smaller. should be inserted to left
    if (strcmp(key, node->val) < 0 && position < node->position)
        node->leftNode = insert(node->leftNode, key, position);
    else // value is greater. Should be inserted to right
        node->rightNode = insert(node->rightNode, key, position);

    /* return the (unchanged) node pointer */
    return node;
}



int main() {
    FILE* fptr;
    errno_t err;
    struct node* root = NULL;
    char word[50];
    char key[50] = "a";
    err = fopen_s(&fptr, ".\\TestUniAlg1-ASD3.txt", "r");

    if (err != 0) {
        printf("Error! File Opened");
        exit(1);
    }

    fscanf_s(fptr, "%s", word, 50);
    root = newNode(word, position);
    

    while (fscanf_s(fptr, "%s", word, 50) == 1) {
        position++;
        insert(root, word, position);    
    }

    preorder(root); // print the BFS in order

    //Search for a word in the BST
    if (Search(root, key)) 
        printf("the word already exists");
    else printf("the word doesn't exist");

    fclose(fptr);
    return 0;
}
```