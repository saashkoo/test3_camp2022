#include <stdio.h>
#include <stdlib.h>

struct Node{
	int data;
	struct Node *next;
};

struct Node *generate(int n){
	if(n==1){
		struct Node *a = malloc(sizeof(struct Node));
		scanf("%d", &(a->data));
		a->next = a;
		return a;
	}
	struct Node *first = malloc(sizeof(struct Node));
	struct Node *prev = first;
	scanf("%d", &(first->data));
	struct Node *curr;
	for(int i = 1;i<n;i++){
		curr = malloc(sizeof(struct Node));
		scanf("%d", &(curr->data));
		prev->next = curr;
		prev = prev->next;
	}
	curr->next = first;
	return first;
	
}

void print(struct Node *cll){
	if(NULL == cll){printf("emty list\n"); return;}
	struct Node *it = cll;
	printf("data: %d  next: %p  curr: %p\n", it->data, it->next, it);
	it = it->next;
	if(cll->data == it->data && it->next == cll->next){return;}
	while(!(cll->data == it->data && it->next == cll->next)){
		printf("data: %d  next: %p  curr: %p\n", it->data, it->next, it);
		it = it->next;
	}
}

struct Node* insertAfter(struct Node *cll, int skipCount, int newElem){
	struct Node *it = cll;
	for(int i = 0;i < skipCount;i++){
		it = it->next;
	}
	struct Node *a = malloc(sizeof(struct Node));
	a->data = newElem;
	a->next = it->next;
	it->next = a;
	return a;
}

void del(struct Node *cll){
	struct Node *it = cll;
	if(cll == NULL){return;}
	if(cll == cll->next){free(cll);return;}
	it = it->next;
	while(!(cll->data == it->data && it->next == cll->next)){
		struct Node* a = it;
		it = it->next;
		free(a);
	}
	free(cll);
}

int main(){
	int n;
	scanf("%d", &n);
	struct Node * a = generate(n);
	print(a);
	insertAfter(a, 0, 7);
	insertAfter(a, 3, 6);
	insertAfter(a, 4, 90);
	printf("\n");
	print(insertAfter(a, 4, 91));
	del(a);

	
	return 0;
}
