#pragma once

#include "Structs.h"

extern struct Member_List* hash_table[TABLE_SIZE];

Icecream* create_icecream();

Customer* create_customer();

Icecream*** create_icecream_tb(int row, int col);

void transposed_icecream_tb();

void table_init();

void table_print();

void owner_init(Owner* ice_owner);

void cal_sales(Owner* ice_owner, int cupsize, int penalty);

int delivery_order(Customer* cus);

int prepare_order(Owner* ice_owner);

int get_order(Owner* ice_owner);

void rider_init(Rider* rider);

int rider_pickup(Owner* ice_owner, Rider* rider);

void delivery_order(Owner* ice_owner, Rider* rider);

const char* get_cook_way(int cook_number);

void pre_order(Customer* cus, TreeNode* root);

void in_order(Customer* cus, TreeNode* root);

void post_order(Customer* cus, TreeNode* root);

void bingsu_menu_init();

void init_hash_table(Member_List* hash_table[]);

void hash_chain_add(Member item, Member_List* hash_table[]);

int hash_chain_search(Member item, Member_List* hash_table[]);