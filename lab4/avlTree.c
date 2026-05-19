#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avlTree.h"

int isValidKey(const char *key) {
    int len = strlen(key);
    if (len == 0 || len > 6) {
        return 0;
    }
    for (int i = 0; i < len; i++) {
        if (!((key[i] >= 'a' && key[i] <= 'z') || (key[i] >= 'A' && key[i] <= 'Z'))) {
            return 0;
        }
    }
    return 1;
}

char *copyKey(const char *src) {
    char *copy = (char *)malloc(strlen(src) + 1);
    if (copy == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    strcpy(copy, src);
    return copy;
}

Node *createNode(const char *key, double data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    newNode->key = copyKey(key);
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(Node *node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int getBalance(Node *node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

void updateHeight(Node *node) {
    if (node == NULL) {
        return;
    }
    node->height = 1 + max(height(node->left), height(node->right));
}

Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *t = x->right;

    x->right = y;
    y->left = t;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *t = y->left;

    y->left = x;
    x->right = t;

    updateHeight(x);
    updateHeight(y);

    return y;
}

Node *insert(Node *root, const char *key, const double value) {
    if (root == NULL) {
        return createNode(key, value);
    }

    int cmp = strcmp(key, root->key);

    if (cmp < 0) {
        root->left = insert(root->left, key, value);
    } else if (cmp > 0) {
        root->right = insert(root->right, key, value);
    } else {
        root->data = value;
        return root;
    }

    updateHeight(root);

    int balance = getBalance(root);

    if (balance > 1 && strcmp(key, root->left->key) < 0) {
        return rightRotate(root);
    }

    if (balance < -1 && strcmp(key, root->right->key) > 0) {
        return leftRotate(root);
    }

    if (balance > 1 && strcmp(key, root->left->key) > 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && strcmp(key, root->right->key) < 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node *findMin(Node *root) {
    if (root == NULL) {
        return NULL;
    }
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

Node *deleteNode(Node *root, const char *key) {
    if (root == NULL) {
        return NULL;
    }

    int cmp = strcmp(key, root->key);

    if (cmp < 0) {
        root->left = deleteNode(root->left, key);
    } else if (cmp > 0) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL || root->right == NULL) {
            Node *temp = (root->left != NULL) ? root->left : root->right;

            free(root->key);
            free(root);

            return temp;
        }

        Node *temp = findMin(root->right);

        free(root->key);
        root->key = copyKey(temp->key);
        root->data = temp->data;

        root->right = deleteNode(root->right, temp->key);
    }

    updateHeight(root);

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node *search(Node *root, const char *key) {
    if (root == NULL) {
        return NULL;
    }

    int cmp = strcmp(key, root->key);

    if (cmp == 0) {
        return root;
    }
    if (cmp < 0) {
        return search(root->left, key);
    }
    return search(root->right, key);
}

void printTree(Node *root, int level) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < level; i++) {
        printf("    ");
    }
    printf("|-- %s : %.2lf (h=%d)\n", root->key, root->data, root->height);
    printTree(root->left, level + 1);
    printTree(root->right, level + 1);
}

void printTreeToFile(Node *root, int level, FILE *out) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < level; i++) {
        fprintf(out, "    ");
    }
    fprintf(out, "|-- %s : %.2lf (h=%d)\n", root->key, root->data, root->height);
    printTreeToFile(root->left, level + 1, out);
    printTreeToFile(root->right, level + 1, out);
}

void freeTree(Node *root) {
    if (root == NULL) {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);
    free(root->key);
    free(root);
}

char *readLineFile(FILE *file) {
    int ch;
    int size = 16;
    int len = 0;

    char *buffer = malloc(size);
    if (buffer == NULL) {
        return NULL;
    }

    while ((ch = fgetc(file)) != '\n' && ch != EOF) {
        buffer[len++] = ch;

        if (len >= size) {
            size *= 2;
            char *tmp = realloc(buffer, size);
            if (tmp == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = tmp;
        }
    }

    if (ch == EOF && len == 0) {
        free(buffer);
        return NULL;
    }

    buffer[len] = '\0';
    return buffer;
}

void processFile(Node **root, const char *inputFilename, const char *outputFilename) {
    FILE *in = fopen(inputFilename, "r");
    if (!in) {
        printf("%s - not found\n", inputFilename);
        return;
    }

    FILE *out = fopen(outputFilename, "w");
    if (!out) {
        printf("Cannot open %s\n", outputFilename);
        fclose(in);
        return;
    }

    char *line;

    while ((line = readLineFile(in)) != NULL) {
        fprintf(out, "%s\n", line);

        char *copy = copyKey(line);
        char *commandStr = strtok(copy, " ");

        if (commandStr == NULL) {
            fprintf(out, "Invalid command\n\n");
            free(copy);
            free(line);
            continue;
        }

        int command;
        if (sscanf(commandStr, "%d", &command) != 1) {
            fprintf(out, "Invalid command\n\n");
            free(copy);
            free(line);
            continue;
        }

        if (command == 1) {
            char *key = strtok(NULL, " ");
            char *valueStr = strtok(NULL, " ");
            double value;

            if (key == NULL || valueStr == NULL) {
                fprintf(out, "Invalid insert format\n\n");
            } else if (!isValidKey(key)) {
                fprintf(out, "Invalid key\n\n");
            } else if (sscanf(valueStr, "%lf", &value) != 1) {
                fprintf(out, "Invalid value\n\n");
            } else {
                *root = insert(*root, key, value);
                fprintf(out, "OK\n\n");
            }
        } else if (command == 2) {
            char *key = strtok(NULL, " ");

            if (key == NULL) {
                fprintf(out, "Invalid delete format\n\n");
            } else if (!isValidKey(key)) {
                fprintf(out, "Invalid key\n\n");
            } else if (search(*root, key) == NULL) {
                fprintf(out, "Key not found\n\n");
            } else {
                *root = deleteNode(*root, key);
                fprintf(out, "OK\n\n");
            }
        } else if (command == 3) {
            if (*root == NULL) {
                fprintf(out, "Tree is empty\n\n");
            } else {
                printTreeToFile(*root, 0, out);
                fprintf(out, "\n");
            }
        } else if (command == 4) {
            char *key = strtok(NULL, " ");
            Node *found;

            if (key == NULL) {
                fprintf(out, "Invalid search format\n\n");
            } else if (!isValidKey(key)) {
                fprintf(out, "Invalid key\n\n");
            } else {
                found = search(*root, key);
                if (found == NULL) {
                    fprintf(out, "Key not found\n\n");
                } else {
                    fprintf(out, "%.2lf\n\n", found->data);
                }
            }
        } else {
            fprintf(out, "Unknown command\n\n");
        }

        free(copy);
        free(line);
    }

    fclose(in);
    fclose(out);

    printf("Commands from %s processed. Results written to %s\n", inputFilename, outputFilename);
    printf("Current tree after file processing:\n");
    if (*root == NULL) {
        printf("Tree is empty\n");
    } else {
        printTree(*root, 0);
    }
}
