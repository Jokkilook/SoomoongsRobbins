#pragma once

#include "Structs.h"

void init_queue(Queue* q);

int is_empty_queue(Queue* q);

int is_full_queue(Queue* q);

int enqueue(Queue* q, Customer* cus);

void print_queue(Queue* q);

Customer* dequeue(Queue* q);