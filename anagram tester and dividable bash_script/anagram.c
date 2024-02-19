#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
	if (argc != 3) {
		printf("need three arguments\n");
		return 1;
	}

	if (strlen(argv[1]) != strlen(argv[2])){
		printf("Not an anagram\n");
		return 1;
	}

	for (int i =0; i< strlen(argv[1]);i++){
		int count=0;
		for(int k =0;k< strlen(argv[1]);k++){
			if(argv[1][i]==argv[1][k]){
				count++;
			}
			if(argv[1][i]==argv[2][k]){
                                count--;
                        }
		}
		if(count != 0) {
                        printf("Not an anagram\n");
                        return 1;
                }
	}
	printf("Anagram\n");
	return 0;
}
