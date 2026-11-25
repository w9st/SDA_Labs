#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100


typedef struct {
    int data[MAX_SIZE];
    int front;
    int rear;
    int count;
} Queue;

void init_queue(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

bool is_empty(const Queue *q) {
    return q->count == 0;
}

bool is_full(const Queue *q) {
    return q->count == MAX_SIZE;
}

bool enqueue(Queue *q, int value) {
    if (is_full(q)) {
        printf("[Queue Error] Cannot enqueue %d: queue is full (max %d elements).\n", value, MAX_SIZE);
        return false;
    }
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->data[q->rear] = value;
    q->count++;
    return true;
}

bool dequeue(Queue *q, int *removed_value) {
    if (is_empty(q)) {
        printf("[Queue Error] Cannot dequeue: queue is empty.\n");
        return false;
    }
    if (removed_value != NULL) {
        *removed_value = q->data[q->front];
    }
    q->front = (q->front + 1) % MAX_SIZE;
    q->count--;
    return true;
}

bool peek_front(const Queue *q, int *front_value) {
    if (is_empty(q)) {
        printf("[Queue Error] Cannot peek: queue is empty.\n");
        return false;
    }
    if (front_value != NULL) {
        *front_value = q->data[q->front];
    }
    return true;
}


void solve_josephus(int n) {
    if (n <= 0) {
        printf("Error: number of people must be a positive integer (n >= 1).\n");
        return;
    }

    Queue q;
    init_queue(&q);

    for (int i = 1; i <= n; i++) {
        if (!enqueue(&q, i)) {
            printf("Cannot run simulation for n = %d due to queue capacity limit.\n", n);
            return;
        }
    }

    int eliminated_count = 0;
    int first_person_elim_order = 0;
    int last_person = 0;

    while (!is_empty(&q)) {
        int first;
        dequeue(&q, &first);

        if (is_empty(&q)) {
            last_person = first;
            break;
        }

        enqueue(&q, first);

        int eliminated;
        dequeue(&q, &eliminated);
        eliminated_count++;

        if (eliminated == 1) {
            first_person_elim_order = eliminated_count;
        }
    }

    printf("\n--- Result for n = %d ---\n", n);
    if (first_person_elim_order > 0) {
        printf("Person #1 (who started the count) was eliminated #%d.\n", first_person_elim_order);
    } else {
        printf("Person #1 (who started the count) was not eliminated (remained alone).\n");
    }
    printf("The last remaining person is #%d.\n", last_person);
}


void test_edge_cases(void) {
    printf("\n=== Testing Edge Cases ===\n");
    Queue test_q;
    init_queue(&test_q);

    int dummy;
    printf("1) Attempting dequeue and peek_front on an empty queue:\n   ");
    dequeue(&test_q, &dummy);
    printf("   ");
    peek_front(&test_q, &dummy);

    printf("2) Filling queue to MAX_SIZE (%d) and attempting overflow:\n   ", MAX_SIZE);
    for (int i = 1; i <= MAX_SIZE + 1; i++) {
        enqueue(&test_q, i);
    }

    while (!is_empty(&test_q)) {
        dequeue(&test_q, NULL);
    }
}

int main(void) {
    int n;
    printf("Enter the number of people n: ");
    if (scanf("%d", &n) != 1) {
        printf("Input error.\n");
        return 1;
    }

    solve_josephus(n);
    test_edge_cases();

    return 0;
}