#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void print_bin_byte(unsigned char a){
	for(int i = 7;i >= 0;i--){
		printf("%d", !(!(a&(1<<i))));
	}
}

void print_bin(char* filename){
	int fd = open(filename,O_RDONLY);
	if(fd < 0){perror("Eroor opening file");return;}
	unsigned char c;
	int e;
	do{
		e = read(fd, &c, 1);
		if(e == 0){return;}
		if (e != 1){perror("Error reading file"); return;}
		print_bin_byte(c);
		printf("\t");
	}while(1);
	
}

void print_hex(char * filename){
	int fd = open(filename,O_RDONLY);
	if(fd < 0){perror("Eroor opening file");return;}
	unsigned char c;
	int e;
	do{
		e = read(fd, &c, 1);
		if(e == 0){return;}
		if (e != 1){perror("Error reading file"); return;}
		printf("%x",c);
		printf("\t");
	}while(1);
}

int main(int argc, char * argv[]){
	//print_bin_byte(1);
	if(argc != 3){printf("invalid arguments\n");}
	else{
		if(!(argv[2][1] != 'H' || argv[2][1] != 'B')){printf("invalid arguments\n");}
		if(argv[2][1] == 'H'){print_hex(argv[1]);}
		if(argv[2][1] == 'B'){print_bin(argv[1]);}
	}
	printf("\n");
	return 0;
}
