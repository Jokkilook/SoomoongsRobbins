#include "Queue.h"
#include "stdio.h"

void init_queue(Queue* q)
{
	q->front = q->rear = 0;
}

int is_empty_queue(Queue* q)
{
	return (q->front == q->rear);
}
int is_full_queue(Queue* q)
{
	return ((q->rear + 1) % MAX_CUSTOMER_SIZE == q->front);
}

int enqueue(Queue* q, Customer* cus)
{
	if (is_full_queue(q))
		return -1;
	q->rear = (q->rear + 1) % MAX_CUSTOMER_SIZE;
	q->cus[q->rear] = cus;
	return 0;
}

void print_queue(Queue* q)
{
	printf("front : %d | rear : %d\n", q->front, q->rear);
	if (!is_empty_queue(q))
	{
		int i = q->front;
		do {
			i = (i + 1) % (MAX_CUSTOMER_SIZE);
			printf("%d | ", q->cus);
			if (i == q->rear)
				break;
		} while (i != q->front);

	}
	printf("\n");
}

Customer* dequeue(Queue* q)
{
	if (is_empty_queue(q))
		return NULL;
	q->front = (q->front + 1) % MAX_CUSTOMER_SIZE;
	return q->cus[q->front];
}