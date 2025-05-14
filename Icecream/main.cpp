#define _CRT_SECURE_NO_WARNINGS

#include"stdio.h"
#include "Icecream.h"
#include "time.h"
#include "Queue.h"
#include "windows.h"

int main()
{
	bool isPlaying = true;

	Owner ice_owner;
	owner_init(&ice_owner);

	table_init();
	table_print();

	Rider rider;
	rider_init(&rider);

	while (isPlaying) {
		char ans;
		getchar();
		printf("장사를 그만 둘까요? y/n: ");
		scanf("%c", &ans);

		switch (ans)
		{
		case 'y':
			isPlaying = false;
			continue;
			break;
		default:
			break;
		}

		int i = 0;

		//최대 손님 대기 큐 수 만큼만 반복해서
		for (i = 0; i < MAX_CUSTOMER_SIZE + 1; i++) {
			Sleep(300);
			//주문을 생성한다.
			if (get_order(&ice_owner) == -1) {
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
				printf("더 이상 주문을 받을 수 없어요. 다시 찾아와주세요.\n");
				printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
			}
		}
		//위 작업이 다 끝나면 오너의 손님 대기 큐에 손님이 MAX_CUSTOMER_SIZE 만큼 대기 중임

		printf("\n\n");

		//print_queue(ice_owner.q);

		//그럼 이제 대기 큐 수만큼 주문 준비
		for (i = 0; i < MAX_CUSTOMER_SIZE + 1; i++) {
			//주문을 준비한다.
			if (prepare_order(&ice_owner) == -1)
				printf("들어온 주문이 더 이상 없어요.\n");
		}

		//주문을 모두 준비하면 손님은 손님 대기 큐에서 배달 테이블 리스트로 옮겨진다.

		//손님 대기 줄 수만큼 반복하여
		for (i = 0; i < MAX_CUSTOMER_SIZE + 1; i++) {
			//라이더가 배달 테이블 리스트에서 자기 배달 리스트도 옮김
			//배달 테이블 리스트가 비었으면
			if (rider_pickup(&ice_owner, &rider) == -1)
				//안내 메시지 출력
				printf("더 이상 배달할 주문이 없어요.\n");
			else
				//라이더의 배달 리스트에 따라 배달
				delivery_order(&ice_owner, &rider);
		}

		//if (rand() % 100 < 10) {
		//	printf("!!!!!!!!!!!단속원 떴다!!!!!!!!!\n");
		//	transposed_icecream_tb();
		//}
	}

	printf("장사 끝~ 총 %d원 벌었다.", ice_owner.total_income);

	return 0;
}