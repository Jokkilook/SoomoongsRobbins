#include "Heap.h"
#include "stdlib.h"

Heap* createHeap() {
	return (Heap*)malloc(sizeof(Heap));
}

void init(Heap* h) {
	h->heap_size = 0;
}

//최대 우선순위 큐에 삽입
void insert_max_heap(Heap* h, int item) {
	int i;
	//넣을 인덱스는 최대 크기 + 1 - 추가하는 거니까
	i = ++(h->heap_size);

	//i가 1이 아니거나 (첫번째가 아니거나)
	//넣으려는 값이 부모노드 보다 크다면?
	while ((i != 1) && (item > h->heap[i / 2])) {
		//원래 넣으려 했던 말단에 부모 노드를 넣고
		h->heap[i] = h->heap[i / 2];
		//넣을 곳을 부모 노드 자리로 변경
		i /= 2;
	}

	//넣을 자리에 아이템 넣기
	h->heap[i] = item;
}

//최대 우선순위 큐에서 삭제
int delete_max_heap(Heap* h) {
	//부모와 자식의 인덱스
	int parent, child;
	//반환할 값과 temp 값
	int item, temp;

	//가장 큰 값 1번 인덱스 값 넣기
	item = h->heap[1];
	//빈 자리를 채울 말단 값 가져오고 최대 사이즈 --
	temp = h->heap[(h->heap_size)--];
	//부모는 1
	parent = 1;
	//자식은 2
	child = 2;

	//자식 인덱스가 최대 사이즈보다 작거나 같다면
	while (child <= h->heap_size) {
		//자식 인덱스가 최대 사이즈보다 작고,
		//자식 인덱스의(왼쪽 자식) 값이 자식 인덱스+1(오른쪽 자식) 값보다 작다면
		if ((child < h->heap_size) && (h->heap[child] < h->heap[child + 1])) {
			//자식 인덱스 ++
			child++;
		}

		//만약 말단 값이 자식 인덱스 값보다 크거나 같으면 빠져나오고
		if (temp >= h->heap[child]) break;

		//아니면 부모의 값을 자식의 값으로 넣고
		h->heap[parent] = h->heap[child];
		//부모 인덱스를 자식 인덱스로 바꾸고
		parent = child;
		//자식 인덱스는 자기 자식 인덱스로 바꾸기
		child *= 2;
	}

	//설정된 부모 인덱스 값을 말단 값으로 바꾸고
	h->heap[parent] = temp;

	//최상위 값 item 반환
	return item;
}

//최소 우선순위 큐에 삽입
void insert_min_heap(Heap* h, int item) {
	//구상 : 말단에 추가하고 부모랑 비교해서
	//자기가 더 작으면 바꾸기
	int i = ++h->heap_size;

	while ((i != 1) && (h->heap[i] < h->heap[i / 2])) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}

	h->heap[i] = item;
}

//최소 우선순위 큐에서 삭제
int delete_min_heap(Heap* h) {
	//맨 위에 꺼 빼고
	//말단 걸 맨위로 올리고
	//자식과 비교하면서 자리 바꾸기
	//언제까지? - 자식과 비교했을 때 자기가 더 작을 때 멈춤
	int item, temp;
	item = h->heap[1];
	temp = h->heap[h->heap_size--];

	int parent = 1, child = 2;

	while (child <= h->heap_size) {

		if ((child < h->heap_size) && (h->heap[child] > h->heap[child + 1])) {
			child++;
		}

		if (temp <= h->heap[child]) break;

		h->heap[parent] = h->heap[child];

		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;

	return item;
}