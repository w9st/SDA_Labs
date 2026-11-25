#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    int count;
} Queue;

void init_queue(Queue *q) {
    q->head = NULL;
    q->tail = NULL;
    q->count = 0;
}

bool is_empty(const Queue *q) {
    return q->head == NULL;
}

bool is_full(const Queue *q) {
    (void)q;
    return false;
}

bool enqueue(Queue *q, int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("[Queue Error] Memory allocation failed for %d.\n", value);
        return false;
    }
    new_node->data = value;
    new_node->next = NULL;

    if (is_empty(q)) {
        q->head = new_node;
        q->tail = new_node;
    } else {
        q->tail->next = new_node;
        q->tail = new_node;
    }
    q->count++;
    return true;
}

bool dequeue(Queue *q, int *removed_value) {
    if (is_empty(q)) {
        printf("[Queue Error] Cannot dequeue: queue is empty.\n");
        return false;
    }
    Node *temp = q->head;
    if (removed_value != NULL) {
        *removed_value = temp->data;
    }
    q->head = q->head->next;
    if (q->head == NULL) {
        q->tail = NULL;
    }
    free(temp);
    q->count--;
    return true;
}

bool peek_front(const Queue *q, int *front_value) {
    if (is_empty(q)) {
        printf("[Queue Error] Cannot peek: queue is empty.\n");
        return false;
    }
    if (front_value != NULL) {
        *front_value = q->head->data;
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
            printf("Cannot run simulation for n = %d due to memory limit.\n", n);
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

    printf("2) Adding 150 elements dynamically (beyond array's 100-element limit):\n");
    for (int i = 1; i <= 150; i++) {
        enqueue(&test_q, i);
    }
    int front_val;
    peek_front(&test_q, &front_val);
    printf("   Successfully enqueued %d elements. Front element is #%d.\n", test_q.count, front_val);

    while (!is_empty(&test_q)) {
        dequeue(&test_q, NULL);
    }
    printf("   All nodes freed cleanly (is_empty = %s).\n", is_empty(&test_q) ? "true" : "false");
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