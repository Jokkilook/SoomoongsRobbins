#include "Heap.h"
#include "stdlib.h"

Heap* createHeap() {
	return (Heap*)malloc(sizeof(Heap));
}

void init(Heap* h) {
	h->heap_size = 0;
}

//�ִ� �켱���� ť�� ����
void insert_max_heap(Heap* h, int item) {
	int i;
	//���� �ε����� �ִ� ũ�� + 1 - �߰��ϴ� �Ŵϱ�
	i = ++(h->heap_size);

	//i�� 1�� �ƴϰų� (ù��°�� �ƴϰų�)
	//�������� ���� �θ��� ���� ũ�ٸ�?
	while ((i != 1) && (item > h->heap[i / 2])) {
		//���� ������ �ߴ� ���ܿ� �θ� ��带 �ְ�
		h->heap[i] = h->heap[i / 2];
		//���� ���� �θ� ��� �ڸ��� ����
		i /= 2;
	}

	//���� �ڸ��� ������ �ֱ�
	h->heap[i] = item;
}

//�ִ� �켱���� ť���� ����
int delete_max_heap(Heap* h) {
	//�θ�� �ڽ��� �ε���
	int parent, child;
	//��ȯ�� ���� temp ��
	int item, temp;

	//���� ū �� 1�� �ε��� �� �ֱ�
	item = h->heap[1];
	//�� �ڸ��� ä�� ���� �� �������� �ִ� ������ --
	temp = h->heap[(h->heap_size)--];
	//�θ�� 1
	parent = 1;
	//�ڽ��� 2
	child = 2;

	//�ڽ� �ε����� �ִ� ������� �۰ų� ���ٸ�
	while (child <= h->heap_size) {
		//�ڽ� �ε����� �ִ� ������� �۰�,
		//�ڽ� �ε�����(���� �ڽ�) ���� �ڽ� �ε���+1(������ �ڽ�) ������ �۴ٸ�
		if ((child < h->heap_size) && (h->heap[child] < h->heap[child + 1])) {
			//�ڽ� �ε��� ++
			child++;
		}

		//���� ���� ���� �ڽ� �ε��� ������ ũ�ų� ������ ����������
		if (temp >= h->heap[child]) break;

		//�ƴϸ� �θ��� ���� �ڽ��� ������ �ְ�
		h->heap[parent] = h->heap[child];
		//�θ� �ε����� �ڽ� �ε����� �ٲٰ�
		parent = child;
		//�ڽ� �ε����� �ڱ� �ڽ� �ε����� �ٲٱ�
		child *= 2;
	}

	//������ �θ� �ε��� ���� ���� ������ �ٲٰ�
	h->heap[parent] = temp;

	//�ֻ��� �� item ��ȯ
	return item;
}

//�ּ� �켱���� ť�� ����
void insert_min_heap(Heap* h, int item) {
	//���� : ���ܿ� �߰��ϰ� �θ�� ���ؼ�
	//�ڱⰡ �� ������ �ٲٱ�
	int i = ++h->heap_size;

	while ((i != 1) && (h->heap[i] < h->heap[i / 2])) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}

	h->heap[i] = item;
}

//�ּ� �켱���� ť���� ����
int delete_min_heap(Heap* h) {
	//�� ���� �� ����
	//���� �� ������ �ø���
	//�ڽİ� ���ϸ鼭 �ڸ� �ٲٱ�
	//��������? - �ڽİ� ������ �� �ڱⰡ �� ���� �� ����
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