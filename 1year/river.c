#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct node {
    uint32_t key;
    uint32_t value;

    uint64_t sum;
    uint64_t size;

    struct node* left;
    struct node* right;
} Node;

Node* CreateNode(uint32_t key, Node* left, Node* right) {
    Node* newNode = calloc(1, sizeof(Node));

    newNode->sum   = key;
    newNode->key   = key;
    newNode->value = rand();
    newNode->size  = 1;

    newNode->left  = left;
    newNode->right = right;

    return newNode;
}

uint64_t GetSize(Node* node) {
    return node ? node->size : 0; 
}

uint64_t GetSum(Node* node) {
    return node ? node->sum : 0;
}

void Recalc(Node* node) {
    node->size = (uint64_t)1 + GetSize(node->left) + GetSize(node->right);
    node->sum  = (uint64_t)node->key * (uint64_t)node->key + GetSum(node->left) + GetSum(node->right);
}

Node* Merge(Node* left, Node* right) {
    if (left == NULL)
        return right;

    if (right == NULL)
        return left;

    if (left->value > right->value) {
        left->right = Merge(left->right, right);

        Recalc(left);
        return left;
    }

    right->left = Merge(left, right->left);

    Recalc(right);
    return right;
}

void Split(Node* head, uint64_t idx, Node** left, Node** right) {
    if (head == NULL) {
        *left  = NULL;
        *right = NULL;

        return;
    }

    Node* newLeft  = NULL;
    Node* newRight = NULL;

    uint64_t leftSize = GetSize(head->left);
    if (leftSize < idx) {
        Split(head->right, idx - leftSize - 1, &newLeft, &newRight);
        
        head->right = newLeft;
        Recalc(head);

        *left  = head;
        *right = newRight;

        return;
    }

    Split(head->left, idx, &newLeft, &newRight);
    
    head->left = newRight;
    Recalc(head);

    *left  = newLeft;
    *right = head;

    return;
}

Node* Insert(Node* head, uint64_t idx, uint32_t key) {
    if (head == NULL) {
        return CreateNode(key, NULL, NULL);
    }

    Node* left  = NULL;
    Node* right = NULL;
    Split(head, idx - 1, &left, &right);

    Node* newNode = CreateNode(key, NULL, NULL);

    return Merge(Merge(left, newNode), right);
}

Node* Divide(Node* head, uint64_t idx) {
    if (head == NULL)
        return head;

    Node* left  = NULL;
    Node* right = NULL;
    Split(head, idx, &left, &right);

    Node* elemToErase = NULL;

    Split(left, idx - 1, &left, &elemToErase);

    Node* newLeft  = CreateNode(elemToErase->key / 2, NULL, NULL);
    Node* newRight = CreateNode(elemToErase->key - (elemToErase->key / 2), NULL, NULL);

    free(elemToErase);

    return Merge(Merge(left, newLeft), Merge(newRight, right));
}

Node* Erase(Node* head, uint64_t idx) {
    if (head == NULL)
        return head;

    Node* left  = NULL;
    Node* right = NULL;
    Split(head, idx, &left, &right);

    Node* elemToErase = NULL;

    Split(left, idx - 1, &left, &elemToErase);  

    Node* newLeft  = NULL;
    Node* newRight = NULL;

    if (left && right) {
        Split(left, idx - 2, &left, &newLeft);
        newLeft->key += elemToErase->key / 2;
        Recalc(newLeft);

        Split(right, 1, &newRight, &right);
        newRight->key += elemToErase->key - (elemToErase->key / 2); 
        Recalc(newRight);
    }
    else {
        if (left) {
            Split(left, idx - 2, &left, &newLeft);
            newLeft->key += elemToErase->key;
            Recalc(newLeft);
        }
        else {
            Split(right, 1, &newRight, &right);
            newRight->key += elemToErase->key;
            Recalc(newRight);
        }
    }

    free(elemToErase);

    return Merge(Merge(left, newLeft), Merge(newRight, right));
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
    srand(time(NULL));

    uint64_t factoriesAmount = 0;
    uint32_t trash           = 0;

    scanf("%lu %u", &factoriesAmount, &trash);

    Node* kuRevo = NULL;

    for (uint64_t curFact = 1; curFact <= factoriesAmount; curFact++) {
        uint32_t riverLength = 0;
        scanf("%u", &riverLength);

        kuRevo = Insert(kuRevo, curFact, riverLength);
    }
    printf("%lu\n", GetSum(kuRevo));

    uint32_t eventsAmount = 0;
    scanf("%u", &eventsAmount);

    for (uint32_t curEvent = 0; curEvent < eventsAmount; curEvent++) {
        uint32_t eventType = 0;
        scanf("%u", &eventType);

        switch (eventType) {
            case 1: {
                uint32_t factNum = 0;
                scanf("%u", &factNum);

                kuRevo = Erase(kuRevo, factNum);

                printf("%lu\n", GetSum(kuRevo));
            }
            break;

            case 2: {
                uint32_t factNum = 0;
                scanf("%u", &factNum);

                kuRevo = Divide(kuRevo, factNum);
                
                printf("%lu\n", GetSum(kuRevo));
            }
            break;
        }
    }

    kuRevo = DeleteTree(kuRevo);
}
