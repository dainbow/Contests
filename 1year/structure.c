#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

typedef struct node {
    uint64_t sum;

    uint32_t key;
    uint32_t value;

    struct node* left;
    struct node* right;
} Node;

Node* CreateNode(uint32_t key, Node* left, Node* right) {
    Node* newNode = calloc(1, sizeof(Node));

    newNode->sum   = key;
    newNode->key   = key;

    newNode->value = rand();

    newNode->left  = left;
    newNode->right = right;

    return newNode;
}

uint64_t GetSum(Node* node) {
    return node ? node->sum : 0; 
}

void RecalcSum(Node* node) {
    node->sum = (uint64_t)node->key + GetSum(node->left) + GetSum(node->right);
}

Node* Merge(Node* left, Node* right) {
    if (left == NULL)
        return right;

    if (right == NULL)
        return left;

    if (left->value > right->value) {
        left->right = Merge(left->right, right);

        RecalcSum(left);
        return left;
    }

    right->left = Merge(left, right->left);

    RecalcSum(right);
    return right;
}

void Split(Node* head, const uint32_t key, Node** left, Node** right) {
    if (head == NULL) {
        *left  = NULL;
        *right = NULL;

        return;
    }

    Node* newLeft  = NULL;
    Node* newRight = NULL;

    if (head->key <= key) {
        Split(head->right, key, &newLeft, &newRight);
        
        head->right = newLeft;
        RecalcSum(head);

        *left  = head;
        *right = newRight;

        return;
    }

    Split(head->left, key, &newLeft, &newRight);
    
    head->left = newRight;
    RecalcSum(head);

    *left  = newLeft;
    *right = head;

    return;
}

Node* Insert(Node* head, uint32_t key) {
    if (head == NULL) {
        return CreateNode(key, NULL, NULL);
    }

    Node* left  = NULL;
    Node* right = NULL;
    Split(head, key - 1, &left, &right);

    Node* newNode = CreateNode(key, NULL, NULL);

    return Merge(Merge(left, newNode), right);
}

Node* Erase(Node* head, uint32_t key) {
    if (head == NULL)
        return head;

    Node* left  = NULL;
    Node* right = NULL;
    Split(head, key, &left, &right);

    Node* elemToErase = NULL;

    Split(left, key, &left, &elemToErase);

    free(elemToErase);

    return Merge(left, right);
}

Node* DeleteTree(Node* node) {
    if (node == NULL)
        return node;

    node->left  = DeleteTree(node->left);
    node->right = DeleteTree(node->right);

    free(node);

    return NULL;
}

int main() {
    uint32_t rqstAmount   = 0;

    scanf("%u", &rqstAmount);

    Node* kuRevo = NULL;
    
    for (uint32_t curRqst = 0; curRqst < rqstAmount; curRqst++) {
        char curCmd = 0;

        scanf("%c", &curCmd);

        switch (curCmd) {
            case '+': {
                uint32_t numToAdd = 0;
                scanf("%u", &numToAdd);

                kuRevo = Insert(kuRevo, numToAdd);
            }
            break;

            case '?': {
                uint32_t numToSplit = 0;
                scanf("%u", &numToSplit);

                Node* left  = NULL;
                Node* right = NULL;
                Split(kuRevo, numToSplit, &left, &right);

                printf("%lu\n", GetSum(left));

                kuRevo = Merge(left, right);
            }
            break;

            default:
                curRqst--;
                break;
        }
    }

    kuRevo = DeleteTree(kuRevo);
}
