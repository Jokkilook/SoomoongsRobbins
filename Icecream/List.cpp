#include "List.h"
#include "stdlib.h"

ListNode* insert_last(ListNode* tail, Customer* cus) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->cus = cus;

	if (tail == NULL) {
		tail = node;
		node->link = tail;
	}
	else {
		node->link = tail->link;
		tail->link = node;
		tail = node;
	}

	return tail;
}

ListNode* insert_first(ListNode* tail, Customer* cus) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->cus = cus;

	if (tail == NULL) {
		tail = node;
		node->link = tail;
	}
	else {
		node->link = tail->link;
		tail->link = node;
	}

	return tail;
}

//**ptail은 tail의 포인터
//tail이 ListNode 주소를 가지는 포인터인데 그 tail의 포인터
//긘까 ListNode 주소를 가지는 포인터 변수의 주소를 저장하는 변수
// **ptail에서
//*ptail(tail의 주소값 저장)을 따라 가면 tail(ListNode의 주소값 저장)이 나오고,
//*tail(ListNode의 주소값 저장)을 하면 ListNode 값이 나온다.
Customer* delete_first(ListNode** ptail) {
	ListNode* removed;
	Customer* cus;

	//tail의 값이 NULL이면. 리스트가 텅텅 비었으면.
	if (*ptail == NULL) {
		return NULL;
	}
	//tail의 값이 tail의 link 값과 같으면 == 요소가 1개만 있으면.
	else if (*ptail == (*ptail)->link){
		//지울 건 tail. 1개밖에 없으니까
		removed = *ptail;
		*ptail = NULL;
	}
	//아니면
	else {
		//지울 건 tail의 link로 연결된 노드. 즉 첫번째.
		removed = (*ptail)->link;
		(*ptail)->link = removed->link;
	}

	cus = removed->cus;
	free(removed);

	return cus;
}

Customer* deletee(ListNode** ptail, ListNode* pre) {
	//지우는 건 pre의 link
	ListNode* removed;
	Customer* cus;

	if (*ptail == NULL) {
		removed = *ptail;
		*ptail = NULL;
	}
	else {
		if (pre->link == *ptail)
			*ptail = pre;
		removed = pre->link;
		pre->link = removed->link;
	}
	cus = removed->cus;
	free(removed);
	return cus;
}

ListNode* search_list(ListNode* tail) {
	ListNode* prev = tail;
	do {
		if (prev == NULL)
			return NULL;
		//한집배달 아닌 손님 찾기
		if (prev->link->cus->onlyhome == 0)
			return prev;
		prev = prev->link;
	} while (prev != tail);

	return NULL;
}