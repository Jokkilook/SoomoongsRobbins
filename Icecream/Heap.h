#pragma once

#include "Structs.h"

Heap* createHeap();

void init(Heap* h);

void insert_max_heap(Heap* h, int item);

int delete_max_heap(Heap* h);

void insert_min_heap(Heap* h, int item);

int delete_min_heap(Heap* h);