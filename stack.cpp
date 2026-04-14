#include "stack.h"

void init(Stack *s){
    s -> top = s -> data - 1;
}

bool isEmpty(const Stack* s){
    return s -> top == s -> data - 1;
}

bool isFull(const Stack* s){
    return s -> top == s -> data + MAX - 1;
}

void push(Stack *s, int value){
    if (isFull(s)) throw "Stack Overflow";
    else {
        s -> top++;
        *(s -> top) = value;
    }
}

void pop(Stack* s){
    if (isEmpty(s)) throw "Stack Underflow";
    else {
        s -> top--;
    }
}

int peek(const Stack* s){
    if (isEmpty(s)) throw "Stack is empty";
    else return *(s -> top);
}