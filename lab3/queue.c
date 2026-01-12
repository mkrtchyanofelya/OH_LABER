#include <stdio.h>
#include <stdlib.h>

struct Node {
  int val;
  struct Node* next;
};

struct Queue {
  struct Node* front;
  struct Node* rear;
};

void init_queue(struct Queue* q) {
  q->front = NULL;
  q->rear = NULL;
}

void enqueue(struct Queue* q, int val) {
  struct Node* node = (struct Node*)malloc(sizeof(struct Node));
  
  if (node == NULL) {
    printf("ERROR: Heap is full\n");
    exit(1);
  }
  
  node->val = val;
  node->next = NULL;

  if (q->front == NULL) {
    q->front = node;
    q->rear = node;
  } else {
    q->rear->next = node;
    q->rear = q->rear->next;
  }
}

void dequeue(struct Queue* q) {
  struct Node* tmp = q->front;
  
  if (tmp == NULL) {
    printf("ERROR: q is empty\n");
    exit(1);
  }

  q->front = q->front->next;
  free(tmp);

  if (q->front == NULL) {
    q->rear = NULL;
  }
}

struct Node* front(struct Queue* q) {
  return q->front;
}

int empty(struct Queue* q) {
  return q->front == NULL;
}

int main() {
  struct Queue q;

  init_queue(&q);

  for (int i = 0; i < 5; ++i) {
    enqueue(&q, i);
  }

  for (int i = 0; i < 5; ++i) {
    printf("val = %d\n", front(&q)->val);
    dequeue(&q);
  }

  printf("It is empty? = %d\n", empty(&q));

  return 0;
}
