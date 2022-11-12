#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct node {
    struct node* left;
    struct node* right;
} Node;

Node* CreateNode() {
    Node* newNode = calloc(1, sizeof(Node));

    return newNode;
}

Node* DeleteNode(Node* node) {
    if (node == NULL)
        return NULL;

    free(node);

    return NULL;
}

void Insert(Node* head, const uint32_t number, const uint32_t curDigit) {
    if (curDigit == 32)
        return;

    uint8_t curBit = ((number & (1 << (31 - curDigit))) != 0);

    if (curBit) {
        if (head->right == NULL)
            head->right = CreateNode();

        Insert(head->right, number, curDigit + 1);
    }
    else {
        if (head->left == NULL)
            head->left = CreateNode();

        Insert(head->left, number, curDigit + 1);
    }
}

Node* Erase(Node* head, const uint32_t number, const uint32_t curDigit) {
    if ((curDigit == 32) || (head == NULL)) {
        return DeleteNode(head);
    }

    uint8_t curBit = ((number & (1 << (31 - curDigit))) != 0);

    if (curBit) {
        head->right = Erase(head->right, number, curDigit + 1);
    }
    else {
        head->left  = Erase(head->left, number, curDigit + 1);
    }

    if (head->left || head->right) {
        return head;
    }
        
    return DeleteNode(head);
}

uint32_t MaxXor(Node* node, const uint32_t number, const uint32_t curDigit) {
    if (curDigit == 32) {
        return 0;
    }
    
    uint8_t curBit = ((number & (1 << (31 - curDigit)))) != 0;

    if (curBit) {
        if (node->left) {
            return 0 + MaxXor(node->left, number, curDigit + 1);
        }

        return (1 << (31 - curDigit)) + MaxXor(node->right, number, curDigit + 1);
    }
    else {
        if (node->right) {
            return (1 << (31 - curDigit)) + MaxXor(node->right, number, curDigit + 1);
        }

        return 0 + MaxXor(node->left, number, curDigit + 1);
    }
}

Node* DeleteTree(Node* head) {
    if (head->left) {
        head->left = DeleteTree(head->left);
    }

    if (head->right) {
        head->right = DeleteTree(head->right);
    }

    return DeleteNode(head);
}

int main() {
    uint32_t rqstAmount = 0;
    scanf("%u", &rqstAmount);

    Node* tree = CreateNode();

    for (uint32_t curRqst = 0; curRqst < rqstAmount; curRqst++) {
        uint32_t opId  = 0;
        uint32_t opArg = 0;

        scanf("%u %u", &opId, &opArg);

        switch (opId) {
            case 1: {
                Insert(tree, opArg, 0);
            }
            break;

            case 2: {
                Erase(tree, opArg, 0);
            }
            break;

            case 3: {
                printf("%u\n", MaxXor(tree, opArg, 0));
            }
            break;
        }
    }

    tree = DeleteTree(tree);
}