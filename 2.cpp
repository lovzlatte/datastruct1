#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100


typedef struct Node {
    char data;
    struct Node* next;
} Node;


typedef struct {
    Node* top;
} Stack;


void init(Stack* s) {
    s->top = NULL;
}


int isEmpty(Stack* s) {
    return s->top == NULL;
}


void push(Stack* s, char c) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->data = c;
    newNode->next = s->top;
    s->top = newNode;
}


char pop(Stack* s) {
    if (isEmpty(s)) return '\0';
    Node* temp = s->top;
    char data = temp->data;
    s->top = temp->next;
    free(temp);
    return data;
}


char peek(Stack* s) {
    if (isEmpty(s)) return '\0';
    return s->top->data;
}


int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}


void infixToPostfix(char* infix, char* postfix) {
    Stack s;
    init(&s);
    int i, j = 0;
    for (i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];
        if (isalnum(c)) {
            postfix[j++] = c;
        } else if (c == '(') {
            push(&s, c);
        } else if (c == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[j++] = pop(&s);
            }
            pop(&s); 
        } else {
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(c)) {
                postfix[j++] = pop(&s);
            }
            push(&s, c);
        }
    }
    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s);
    }
    postfix[j] = '\0';
}


void postfixToInfix(char* postfix, char* infix) {
    Stack s;
    init(&s);
    char temp[MAX];
    int i;
    for (i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];
        if (isalnum(c)) {
            push(&s, c);
        } else {
            char op2 = pop(&s);
            char op1 = pop(&s);
            sprintf(temp, "(%c%c%c)", op1, c, op2);
            for (int j = 0; temp[j] != '\0'; j++) {
                push(&s, temp[j]);
            }
        }
    }
    int j = 0;
    while (!isEmpty(&s)) {
        infix[j++] = pop(&s);
    }
    infix[j] = '\0';
    strrev(infix);
}

int main() {
    char infix[MAX], postfix[MAX], convertedInfix[MAX];
    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix: %s\n", postfix);

    postfixToInfix(postfix, convertedInfix);
    printf("Converted back to Infix: %s\n", convertedInfix);
    
    return 0;
}

