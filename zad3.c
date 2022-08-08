#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <errno.h>


char t[5] = {'A', 'B', 'C', 'D', '\0'};


char names[11][11] = {"kaima", "mlqko", "kufteta", "banica", "lutenica", "hlqb", "kafe", "voda", "morkov", "kufte"};


struct Product{
     double old_price;
     double new_price;
     unsigned int id;
     char product_type;
     char product_name[11];
};

int my_rand(int min, int max){
	return min + rand()%(max-min+1);
}


struct Product generate(){
	static int idd = 0;
	idd++;
	struct Product a;
	a.old_price = (double)(my_rand(499, 10045)/100.0);
	a.new_price = (double)(my_rand(499, 10045)/100.0);
	a.id = idd;
	a.product_type = t[my_rand(0,3)];
	strcpy(a.product_name, names[my_rand(0,9)]);
	return a;
}

void pr(struct Product *a, int s){
	for(int i =0;i<s;i++){
		printf("old_price: %5.2lf new_price: %5.2lf id: %2d type: %c name: %s\n", a[i].old_price, a[i].new_price, a[i].id, a[i].product_type, a[i].product_name);
	}
}

int cmp(const void *aa, const void*bb){
	struct Product a = *(struct Product*)aa;
	struct Product b = *(struct Product*)bb;
	if(fabs((a.new_price-a.old_price) - (b.new_price-b.old_price))<0.01){
		if(a.product_type == b.product_type){
			if(0 == strcmp(a.product_name, b.product_name)){
				return a.id-b.id;
			}
			else{
				return strcmp(a.product_name, b.product_name);
			}
		}
		else{
			return a.product_type - b.product_type;
		}
	}
	else{return (a.new_price-a.old_price) - (b.new_price-b.old_price);}

}


void save_to_bin(struct Product *a, int s){
	FILE *f = fopen("file", "w+b");
	for(int i =0; i < s; i++){
		fprintf(f, "%.2lf %.2lf %d %c %s ", a[i].old_price, a[i].new_price, a[i].id, a[i].product_type, a[i].product_name);
	}
	fclose(f);
}


void read_from_bin(){
	FILE *f = fopen("file", "rb");
	int e;
	struct Product a;
	do{
		e = fscanf(f, "%lf %lf %d %c %s", &a.old_price, &a.new_price, &a.id, &a.product_type, &a.product_name);
		printf  ("old_price: %5.2lf new_price: %5.2lf id: %2d type: %c name: %s\n", a.old_price, a.new_price, a.id, a.product_type, a.product_name);
	}while(e > 0);

}


int main(){
	srand(clock());
	struct Product a[41];
	for(int i = 0;i<40;i++){
		a[i] = generate();
	}
	pr(a, 40);
	printf("\n");
	qsort(a, 40, sizeof(struct Product), &cmp);
	pr(a, 40);
	save_to_bin(a, 40);
	printf("\n");
	read_from_bin();
	return 0;
}
