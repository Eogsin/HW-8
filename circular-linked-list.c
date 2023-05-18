/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  School of Computer Science
 *  at Chungbuk National University
 *
 */
#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){

	listNode* current = h->rlink; // 첫 번째 노드부터 시작합니다.
    listNode* temp;

    // 리스트를 순회하면서 각 노드를 해제합니다.
    while (current != h) {
        temp = current; // 현재 노드를 임시 변수에 저장합니다.
        current = current->rlink; // 다음 노드로 이동합니다.
        free(temp); // 임시 변수에 저장된 노드를 해제합니다.
    }

    // 헤드 노드를 해제합니다.
    free(h);

    return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	//새로운 노드 생성 및 메모리 할당
    listNode* newNode = (listNode*)malloc(sizeof(listNode));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return 0;
    }
    newNode->key = key;
	//새로운 노드를 마지막에 삽입
    newNode->rlink = h;
    newNode->llink = h->llink;
    h->llink->rlink = newNode;
    h->llink = newNode;

    return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {	
	//리스트가 비어 있는지 확인
    if (h->rlink == h) {
        printf("List is empty.\n");
        return 0;
    }
	//마지막 노드 삭제
    listNode* lastNode = h->llink;
    lastNode->llink->rlink = h;
    h->llink = lastNode->llink;
    free(lastNode);

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
    listNode* newNode = (listNode*)malloc(sizeof(listNode)); 		//동적할당
    if (newNode == NULL) {											//동적할당 실패시 memory allocation failed 출력
        printf("Memory allocation failed.\n");
        return 0;	
    }
    newNode->key = key;												//값을 넣고

    newNode->llink = h;												//새 노드의 llink에 h를 넣고
    newNode->rlink = h->rlink;										//새 노드의 rlinkd에 h의 r 링크 를 넣는다.
    h->rlink->llink = newNode;										//h - > rlink의 가서 link에 새로운 노드 주소 값으로 설정 
    h->rlink = newNode;												//h의 rlink 에 새로운 노드 주소값 설정 

    return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
    //리스트가 비어있는지 확인
    if (h->rlink == h) {
        printf("List is empty.\n");
        return 0;
    }
    //첫 번째 노드를 가리키는 포인터 선언 및 초기화
    listNode* firstNode = h->rlink;
    //헤드 노드의 오른쪽 링크를 두 번째 노드로 변경
    h->rlink = firstNode->rlink;
    //두 번째 노드의 왼쪽 링크를 헤드 노드로 변경
    firstNode->rlink->llink = h;
    //첫 번째 노드 메모리 해제
    free(firstNode);
	
    return 1;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
	// 리스트가 비어있는지 확인
    if (h->rlink == h) {
        printf("List is empty.\n");
        return 0;
    }
	// 현재 노드와 임시 노드를 가리키는 포인터 선언 및 초기화
    listNode* current = h->rlink;
    listNode* temp = NULL;
	//리스트를 역순으로 재배치
    do {
        temp = current->llink;
        current->llink = current->rlink;
        current->rlink = temp;
        current = current->llink;
    } while (current != h);

    return 1;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {
	//새로운 노드 생성 및 메모리 할당
	listNode* newNode = (listNode*)malloc(sizeof(listNode));	
	if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return 0;
    }
    newNode->key = key;
	//삽입할 위치 찾기
    listNode* current = h->rlink;
    listNode* previous = h;

    while (current != h && current->key < key) {
        previous = current;
        current = current->rlink;
    }
	//노드 삽입
    newNode->llink = previous;
    newNode->rlink = current;
    previous->rlink = newNode;
    current->llink = newNode;

    return 1;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	//리스트가 비어있는지 확인
    if (h->rlink == h) {
        printf("List is empty.\n");
        return 0;
    }
	//삭제할 노드 탐색
    listNode* current = h->rlink;
	
    while (current != h && current->key != key) {
        current = current->rlink;
    }
    //삭제할 노드가 없는 경우 처리
    if (current == h) {
        printf("Node with key %d not found.\n", key);
        return 0;
    }
	//노드 삭제
    current->llink->rlink = current->rlink;
    current->rlink->llink = current->llink;
    free(current);

    return 1;
}


