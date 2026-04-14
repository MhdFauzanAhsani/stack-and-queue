#include "queue.h"
#include <cstddef>

void init(Queue *q){
    q -> front = NULL;
    q -> rear = NULL;
}

bool isEmpty(const Queue* q){
    return q -> front == NULL;
}

bool isFull(const Queue* q){
    if (q -> front == q -> data && q -> rear == q -> data + MAX - 1){
        return true;
    }
    if (q -> rear + 1 == q -> front){
        return true;
    }
    else {
        return false;
    }
}

void enqueue(Queue *q, int value){
    if (isFull(q)) throw "Queue Overflow";
    
    if (isEmpty(q)){
        q -> front = q -> rear = q -> data;
    }
    else {
        if (q -> rear == q -> data + MAX - 1) q -> rear = q -> data;
        else q -> rear++;
    }
    *(q -> rear) = value;
}

void dequeue(Queue *q){
    if (isEmpty(q)) throw "Queue Underflow";
    
    if (q -> front == q -> rear) q -> front = q -> rear = NULL;
    else {
        if (q -> front == q -> data + MAX - 1) q -> front = q -> data;
        else q -> front++;
    }
}

int front(const Queue *q){
    if (isEmpty(q)) throw "Queue is Empty";
    return *(q -> front);
}

int back(const Queue *q){
    if (isEmpty(q)) throw "Queue is Empty";
    return *(q -> rear);
}