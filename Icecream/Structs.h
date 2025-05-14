#pragma once

#define ROW 2
#define COL 3
#define MAX_CUPSIZE 5
#define MAX_CUSTOMER_SIZE 5
#define MAX_DELIVERY_COUNT 10
#define MAX_COOK_BINGSU 3
#define NUM_OF_INGREDIENT 7

typedef struct stack Stack;
typedef struct customer Customer;
typedef struct icecream Icecream;
typedef struct queue Queue;
typedef struct owner Owner;
typedef struct ListNode ListNode;

typedef struct stack {
	int* icecream_number;
	int capacity;
	int top;
} Stack;

typedef struct customer {
	int order_num;
	int cup_size;
	int order[MAX_CUPSIZE];
	int vip;
	int onlyhome;
	int ingre_count;
	int bingsu_menu;
	char order_bingsu[NUM_OF_INGREDIENT][100];
	char bingsu_make[NUM_OF_INGREDIENT][100];
	Stack* icecream_cup;
} Customer;

typedef struct icecream {
	int number;
	char name[15];
	int stock;
} Icecream;

typedef struct queue {
	int front, rear;
	Customer* cus[MAX_CUSTOMER_SIZE];
} Queue;

typedef struct owner {
	int total_income;
	int price_of_cupsize[MAX_CUPSIZE];
	Queue* q;
	ListNode* tail;
} Owner;

typedef struct ListNode{
	Customer * cus;
	struct ListNode* link;
}ListNode;

typedef struct rider {
	int count;
	ListNode* tail;
}Rider;

typedef struct TreeNode{
	char name[100];
	struct TreeNode* left, * right;
}TreeNode;