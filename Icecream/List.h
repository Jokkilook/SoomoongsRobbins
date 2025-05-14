#pragma once

#include "Structs.h"

ListNode* insert_last(ListNode* tail, Customer* cus);

ListNode* insert_first(ListNode* tail, Customer* cus);

Customer* delete_first(ListNode **ptail);

Customer* deletee(ListNode** ptail, ListNode* pre);

ListNode* search_list(ListNode* tail);