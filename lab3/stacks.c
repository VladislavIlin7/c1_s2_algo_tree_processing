#include "stacks.h"

#include <stdio.h>
#include <stdlib.h>

stack *createStack() {
    stack *s = malloc(sizeof(stack));
    if (s == NULL) {
        return NULL;
    }

    s->size = 2;
    s->data = malloc(s->size * sizeof(node *));
    if (s->data == NULL) {
        free(s);
        return NULL;
    }

    s->top = -1;
    return s;
}

int isEmptyStack(stack *s) {
    if (s->top == -1) {
        return 1;
    }
    return 0;
}

int isFullStack(stack *s) {
    if (s->top == s->size - 1) {
        return 1;
    }
    return 0;
}

void push(stack *s, node *value) {
    if (isFullStack(s)) {
        s->size *= 2;
        node **tmp = realloc(s->data, s->size * sizeof(node *));
        if (tmp == NULL) {
            printf("realloc error\n");
            return;
        }
        s->data = tmp;
    }

    s->data[++s->top] = value;
}

node *pop(stack *s) {
    if (isEmptyStack(s)) {
        printf("Stack is empty\n");
        return NULL;
    }
    return s->data[s->top--];
}

void freeStack(stack *s) {
    if (s == NULL) {
        return;
    }
    if (s->data != NULL) {
        free(s->data);
    }
    free(s);
    printf("stack free\n");
}




stackOperator *createStackOperator() {
    stackOperator *s = malloc(sizeof(stackOperator));
    if (s == NULL) {
        return NULL;
    }

    s->size = 2;
    s->data = malloc(s->size * sizeof(char));
    if (s->data == NULL) {
        free(s);
        return NULL;
    }

    s->top = -1;
    return s;
}

int isEmptyStackOperator(stackOperator *s) {
    if (s->top == -1) {
        return 1;
    }
    return 0;
}

int isFullStackOperator(stackOperator *s) {
    if (s->top == s->size - 1) {
        return 1;
    }
    return 0;
}

char peekOperator(stackOperator *s) {
    if (isEmptyStackOperator(s)) {
        return '\0';
    }
    return s->data[s->top];
}

void pushOperator(stackOperator *s, char value) {
    if (isFullStackOperator(s)) {
        s->size *= 2;
        char *tmp = realloc(s->data, s->size * sizeof(char));
        if (tmp == NULL) {
            printf("realloc error\n");
            return;
        }
        s->data = tmp;
    }

    s->data[++s->top] = value;
}

char popOperator(stackOperator *s) {
    if (isEmptyStackOperator(s)) {
        printf("Stack is empty\n");
        return '\0';
    }
    return s->data[s->top--];
}

void freeStackOperator(stackOperator *s) {
    if (s == NULL) {
        return;
    }
    if (s->data != NULL) {
        free(s->data);
    }
    free(s);
    printf("stack operator free\n");
}
