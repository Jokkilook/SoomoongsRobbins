#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "stdlib.h"
#include "windows.h"
#include "time.h"
#include "Structs.h"
#include "Stack.h"
#include "Queue.h"
#include "Icecream.h"
#include "List.h"

Icecream*** icecream_tb;

int reverse;

int order_count = 0;

TreeNode* bingsu_num;

//
Icecream* create_icecream() {
	Icecream* ice = NULL;
	ice = (Icecream*)malloc(sizeof(Icecream));
	memset(ice, 0, sizeof(Icecream));
	return ice;
}

//고객 생성 함수
Customer* create_customer() {
	//고객 메모리 할당
	Customer* cus = (Customer*)malloc(sizeof(Customer));

	//고객 초기화 (모두 0바이트, int는 0 char는 빈 문자열로)
	memset(cus, 0, sizeof(Customer));

	//고객의 아이스크림 컵 스택 메모리 할당
	cus->icecream_cup = (Stack*)malloc(sizeof(Stack));

	//고객 빙수 재료 카운트 초기화
	cus->ingre_count = 0;
	return cus;
}

//아이스크림 데이터베이스 생성
Icecream*** create_icecream_tb(int row, int col) {
	int i;
	Icecream*** table;
	table = (Icecream***)malloc(sizeof(Icecream**) * row);
	for (i = 0; i < row; i++) {
		table[i] = (Icecream**)malloc(sizeof(Icecream*) * col);
	}
	return table;
}

//아이스크림 데이터베이스 변환
void transposed_icecream_tb() {
	int i, j;
	reverse = 1;
	Icecream*** table = create_icecream_tb(COL, ROW);
	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			table[j][i] = icecream_tb[i][j];
		}
	}
	free(icecream_tb);
	icecream_tb = table;

	for (i = 0; i < COL; i++) {
		for (j = 0; j < ROW; j++) {
			printf("[(%d): %15s]", icecream_tb[i][j]->number, icecream_tb[i][j]->name);
		}
		printf("\n");
	}
}

//아이스크림 이름 세팅
void table_init() {

	int i, j;
	int ice_num = 0;
	icecream_tb = create_icecream_tb(ROW, COL);
	reverse = 0;
	srand(time(NULL));
	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			Icecream* ice = create_icecream();
			char name[15];
			ice->number = ice_num++;
			ice->stock = rand() % MAX_CUPSIZE;
			printf("진열할 아이스크림 명을 입력하세요:");
			scanf("%s", name);
			strcpy(ice->name, name);
			icecream_tb[i][j] = ice;
		}
	}
}

//아이스크림 출력
void table_print() {
	int i, j;
	char print_temp[512];
	FILE* fp = fopen("./icecream_ASC.txt", "r");
	if (fp == NULL) {
		printf("file load failed");
	}
	while (fgets(print_temp, sizeof(print_temp), fp))
	{
		printf("%s", print_temp);
	}
	puts("");
	printf("\n");
	fclose(fp);
	for (i = 0; i < ROW; i++) {
		for (j = 0;j < COL;j++) {
			printf("[(%d): %15s]", icecream_tb[i][j]->number, icecream_tb[i][j]->name);
		}
		printf("\n");
	}
}

//주인 초기화
void owner_init(Owner *ice_owner) {
	int i;
	for (i = 0; i < MAX_CUPSIZE; i++) {
		ice_owner->price_of_cupsize[i] = (i + 1) * 100;
	}
	ice_owner->total_income = 0;

	//손님 큐 초기화
	Queue* q = (Queue *)malloc(sizeof(Queue));
	memset(q, 0, sizeof(Queue));
	init_queue(q);
	ice_owner->q = q;
	ice_owner->tail = NULL;
}

void cal_sales(Owner* ice_owner, int cupsize, int penalty) {
	int income = ice_owner->price_of_cupsize[cupsize-1];
	income -= penalty;
	ice_owner->total_income = ice_owner->total_income + income;

	if (ice_owner->total_income < 0) ice_owner->total_income = 0;

	printf("나 : 오케이! 이번 주문으로 %d원, 총 %d원 벌었다.!\n", income, ice_owner->total_income);
}

int delivery_order(Customer* cus) {
	int i, ice_num;
	int penalty = 0;

	for (i = cus->cup_size; i > 0;  i--) {
		ice_num = pop(cus->icecream_cup);
		if (ice_num == -1) {
			printf("고객 : 왜 주문한 아이스크림을 다 안주는 거야!!\n");
			penalty++;
		}
		else {
			if (ice_num == cus->order[i]) {
				printf("고객 : 음~ 내가 주문한 순서대로 쌓아줬네\n");
			}
			else {
				printf("고객 : 내가 주문한 아이스크림이 아니잖아!!!\n");
				penalty++;
			}
		}
	}
	if ((cus->icecream_cup->top) > -1) {
		penalty += ((cus->icecream_cup->top) + 1);
		printf("고객 : 왜 내가 시킨 것보다 더 주는거야? 돼지 되라는 거야???\n");
	}

	return penalty;
}

void delivery_order(Owner* ice_owner, Rider* rider) {
	int i, ice_num;
	int penalty = 0;
	Customer* cus;

	while (rider->count > 0) {
		cus = delete_first(&(rider->tail));

		printf("=======================================================\n");
		printf("[VIP %d ONLYHOME %d]주문번호 %d 고객님 빙수와 아이스크림 배달왔습니다.\n", cus->vip, cus->onlyhome, cus->order_num);

		//빙수 평가
		printf("빙수는 잘 만들었는지 볼까\n");
		for (i = 0; i < NUM_OF_INGREDIENT; i++) {
			if (strcmp(cus->bingsu_make[i], cus->order_bingsu[i]) != 0) {
				penalty++;
				printf("고객 : 왜 내가 주문한 방법으로 빙수를 안만들어 줬어!!\n");
			}
			else {
				printf("고객 : 굿 내가 원하는 빙수맛이야!!\n");
			}
		}

		//아이스크림 평가
		printf("그 다음 아이스크림 맛볼까?\n");
		for (i = cus->cup_size; i > 0;  i--) {
			ice_num = pop(cus->icecream_cup);
			if (ice_num == -1) {
				printf("고객 : 왜 주문한 아이스크림을 다 안주는 거야!!\n");
				penalty++;
			}
			else {
				if (ice_num == cus->order[i]) {
					printf("고객 : 음~ 내가 주문한 순서대로 쌓아줬네!\n");
				}
				else {
					printf("고객 : 내가 주문한 아이스크림이 아니잖아!!\n");
					penalty++;
				}
			}

			if ((cus->icecream_cup->top) > -1) {
				penalty += ((cus->icecream_cup->top) + 1);
				printf("고객 : 왜 내가 시킨 것보다 더 주는거야? 돼지 되라는 거야???\n");
			}
		}

		cal_sales(ice_owner, cus->cup_size, penalty);
		rider->count--;
	}
}

int prepare_order(Owner *ice_owner) {

	//손님 대기 큐에서 손님 하나 빼오기
	Customer* cus = dequeue(ice_owner->q);

	//만약 손님이 없으면 -1 반환
	if (cus == NULL)
	{
		return -1;
	}

	//빙수 준비
	printf("---------------------------------------------------------------------------------\n");
	printf("나 : 빙수부터 만들어야겠다. %s으로 빙수를 만들어 달라고 하셨네...\n", get_cook_way(cus->bingsu_menu));
	
	printf("나 : 빙수 재료는 우유, 딸기, 초코, 딸기청, 휘핑, 초코칩, 견과류가 있으니깐\n");
	int i = 0;
	//재료 수만큼 재료 넣기
	for (i = 0; i < NUM_OF_INGREDIENT; i++) {
		printf("재료 이름:");
		scanf("%s", cus->bingsu_make[i]);
	}

	printf("이 순서대로 재료를 넣으면 되겠다!!\n");
	
	//아이스크림 준비
	Stack* icecream_cup = cus->icecream_cup;
	//아이스크림 스택 초기화(배열 스택임)
	init_cup(icecream_cup);

	int cupsize = -1;
	printf("나 : 고객님이 고른 컵 사이즈가 뭐였지?\n");
	scanf("%d", &cupsize);

	int choice;

	for (i = 0; i < cupsize; i++) {
		printf("나 : 몇 번 아이스크림을 쌓아야 하지??\n");
		scanf("%d", &choice);
		push(choice, icecream_cup);
	}

	printf("---------------------------------------------------------------------------------\n");

	//tail이 배달 테이블 리스트(연결 리스트임)
	//insert_last가 put_rider_table
	ice_owner->tail = insert_last(ice_owner->tail, cus);

	//최종적으로 대기 -> 배달 대기 줄로

	//int penalty = delivery_order(cus);
	//cal_sales(ice_owner, cus->cup_size, penalty);
}

int get_order(Owner *ice_owner) {

	//대기 큐가 꽉 찼는 지 확인한다.
	int ret = is_full_queue(ice_owner->q);

	//꽉찼으면 -1 리턴
	if (ret == 1)
		return -1;

	//아니면 손님 만들고
	Customer* cus = create_customer();
	cus->order_num = order_count++;
	//손님 대기 큐에 넣고
	enqueue(ice_owner->q, cus);

	// 주문 받기 시퀀스 가동
	int i;
	Sleep(200);
	srand(time(NULL));

	printf("======================================================\n");
	printf("사장: 고객님 주문받겠습니다.\n");
	cus->cup_size = (rand() % MAX_CUPSIZE) + 1;
	cus->vip = (rand() % 2);
	cus->onlyhome = (rand() % 2);

	Sleep(200);

	//아이스크림
	printf("고객: 저 cupsize %d으로 ", cus->cup_size);

	for (i = 0; i < cus->cup_size; i++) {
		int ice_num = rand() % (ROW * COL);
		int row;
		int col;

		if (reverse == 0) {
			row = ice_num / COL;
			col = ice_num % COL;
		}
		else {
			row = ice_num % COL;
			col = ice_num / COL;
		}

		cus->order[i] = ice_num;
		printf("[%d]%s, ", icecream_tb[row][col]->number, icecream_tb[row][col]->name);
	}

	printf("순서로 쌓아주세요.\n");

	//빙수
	cus->bingsu_menu = rand() % MAX_COOK_BINGSU;
	Sleep(200);

	printf("고객 : 저 빙수 %s 만들어 주세요... \n", get_cook_way(cus->bingsu_menu));

	if (cus->bingsu_menu == 0)
		pre_order(cus, bingsu_num);
	if (cus->bingsu_menu == 1)
		in_order(cus, bingsu_num);
	if (cus->bingsu_menu == 2)
		post_order(cus, bingsu_num);

	printf("======================================================\n");
;
	return 0;
}

//라이더 초기화
void rider_init(Rider* rider) {
	rider->count = 0;
	rider->tail = NULL;
}

int rider_pickup(Owner* ice_owner, Rider* rider) {
	//배달 대기 리스트에서 첫번째 거를 가져온다.
	Customer* cus = delete_first(&(ice_owner->tail));
	ListNode* prev;

	//없으면 -1 반환
	if (cus == NULL) {
		return -1;
	}

	//라이더의 배달 리스트에 추가
	rider->tail = insert_last(rider->tail, cus);
	//배달 수 ++
	rider->count++;
	printf("=================================================\n");
	printf("배달 시작~~~~\n");
	
	//처음 넣은 배달이 한집 배달이 아니면
	if (cus->onlyhome == 0) {
		printf("엇! 한집 배달이 아니네!\n");
		//대기 줄에 모든 한집 배달이 아닌 것 추가
		while (rider->count < MAX_DELIVERY_COUNT) {
			//한집 배달이 아닌 손님의 전 노드
			prev = search_list(ice_owner->tail);
			//만약 있으면
			if (prev != NULL) {
				//한집 배달이 아닌 손님 가져오고 줄에서 지우기
				cus = deletee(&(ice_owner->tail), prev);
				//라이더 배달 리스트에 추가
				rider->tail = insert_last((rider->tail), cus);
				//배달 수 ++
				rider->count++;
				printf("오케이 하나 더 픽업!\n");
			}
			//만약 없으면 그만 찾고 나가기
			else {
				break;
			}
		}
	}

	return 1;
}

const char* get_cook_way(int cook_number) {
	switch (cook_number) {
	case 0:
		return "베이스 맛이 강하게";
	case 1:
		return "균형잡힌 맛으로";
	case 2:
		return "깊은 여운이 나게";
	default:
		return NULL;
	}
}

void pre_order(Customer* cus, TreeNode* root) {
	if (root) {
		strcpy(cus->order_bingsu[cus->ingre_count], root->name);
		printf("%s", cus->order_bingsu[cus->ingre_count]);
		cus->ingre_count++;
		pre_order(cus, root->left);
		pre_order(cus, root->right);
	}
}

void in_order(Customer* cus, TreeNode* root) {
	if (root) {
		in_order(cus, root->left);
		strcpy(cus->order_bingsu[cus->ingre_count], root->name);
		printf("%s", cus->order_bingsu[cus->ingre_count]);
		cus->ingre_count++;
		in_order(cus, root->right);
	}
}

void post_order(Customer* cus, TreeNode* root) {
	if (root) {
		post_order(cus, root->left);
		post_order(cus, root->right);
		strcpy(cus->order_bingsu[cus->ingre_count], root->name);
		printf("%s", cus->order_bingsu[cus->ingre_count]);
		cus->ingre_count++;
	}
}