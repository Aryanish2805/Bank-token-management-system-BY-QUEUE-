#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE 100
#define NAME_LEN 50

typedef struct {
    int token;
    char name[NAME_LEN];
} Customer;

typedef struct {
    Customer items[MAX_QUEUE];
    int front;
    int rear;
    int size;
    int nextToken;
} Queue;

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
    q->nextToken = 1; 
}

int isFull(Queue *q) {
    return q->size == MAX_QUEUE;
}

int isEmpty(Queue *q) {
    return q->size == 0;
}

void clearStdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void enqueue(Queue *q, const char *name) {
    if (isFull(q)) {
        printf("Queue is full. Cannot add more customers.\n");
        return;
    }

    q->rear = (q->rear + 1) % MAX_QUEUE;
    q->items[q->rear].token = q->nextToken++;
    strncpy(q->items[q->rear].name, name, NAME_LEN - 1);
    q->items[q->rear].name[NAME_LEN - 1] = '\0';
    q->size++;

    printf("Token generated: %d\n", q->items[q->rear].token);
}

void dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("No customers to serve. Queue is empty.\n");
        return;
    }

    Customer served = q->items[q->front];
    q->front = (q->front + 1) % MAX_QUEUE;
    q->size--;

    printf("Serving token %d - %s\n", served.token,
           served.name[0] ? served.name : "(No name)");
}

void displayQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("No waiting customers.\n");
        return;
    }

    printf("Waiting customers (%d):\n", q->size);
    int idx = q->front;
    for (int i = 0; i < q->size; i++) {
        Customer *c = &q->items[idx];
        printf("%d. Token: %d  Name: %s\n", i + 1, c->token,
               c->name[0] ? c->name : "(No name)");
        idx = (idx + 1) % MAX_QUEUE;
    }
}

void waitingCount(Queue *q) {
    printf("Current waiting count: %d\n", q->size);
}

void showMenu(void) {
    printf("\n=== Bank Token Queue Management System ===\n");
    printf("1. Generate token and add customer\n");
    printf("2. Display all waiting customers\n");
    printf("3. Serve next customer\n");
    printf("4. Show waiting count\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int main(void) {
    Queue q;
    initQueue(&q);

    int choice;
    char name[NAME_LEN];

    while (1) {
        showMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearStdin();
            continue;
        }
        clearStdin();

        switch (choice) {
            case 1:
                printf("Enter customer name (press enter for no name): ");
                if (fgets(name, sizeof(name), stdin) == NULL) {
                    name[0] = '\0';
                } else {
                    
                    size_t ln = strlen(name) - 1;
                    if (name[ln] == '\n') name[ln] = '\0';
                }
                enqueue(&q, name);
                break;

            case 2:
                displayQueue(&q);
                break;

            case 3:
                dequeue(&q);
                break;

            case 4:
                waitingCount(&q);
                break;

            case 5:
                printf("Exiting...\n");
                exit(EXIT_SUCCESS);
                break;

            default:
                printf("Invalid choice. Please choose between 1-5.\n");
                break;
        }
    }

    return 0;
}
