#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int phonebook_length = 0;
typedef struct PHONE_RECORD{
	char name[50];
	char birthdate[12];
	char phone[15];
}PHONE_RECORD;

//PHONE_RECORD phonebook[10];

//new _dynamic function

PHONE_RECORD *phonebook = NULL;

int array_size = 0;

void phonebook_array(int size){
	array_size = size;
	phonebook = malloc(size*sizeof(PHONE_RECORD));
	if(phonebook == NULL){
		puts("Not enough space to store phonebook of this size! Program terminated");
		exit(1);
	}
}










int addRecord(char name[], char birth[], char phone[]){
	if(phonebook_length >= array_size ) return 1;
	PHONE_RECORD p;
	strcpy(p.name, name);
        strcpy(p.birthdate, birth);
    	strcpy(p.phone, phone);
	
	phonebook[phonebook_length] = p;
	phonebook_length++;
	return 0;
}

int findRecord(char name[]){
	for(int i = 0; i < phonebook_length; i++){
		if(strcmp(name, phonebook[i].name) == 0){
		puts("---- NAME ---- ---- BIRTH DATE ---- ---- PHONE ----");
		printf("%-14s %-20s %-10s\n",
                        phonebook[i].name,
                        phonebook[i].birthdate,
                        phonebook[i].phone);
		return i;
		}
	}
	puts("Phone record not found");
        return -1;
}

int listRecords(void){
	if(phonebook_length == 0) return 1;
	puts("---- NAME ---- ---- BIRTH DATE ---- ---- PHONE ----");
	for(int i = 0; i < phonebook_length; i++){
		printf("%-14s %-20s %-10s\n", 
            		phonebook[i].name, 
            		phonebook[i].birthdate, 
            		phonebook[i].phone);
	}
	return 0;


}


int loadCSV(char *filename){
	FILE *file = fopen(filename, "rt");
	if(file == NULL) {
		return 1;
	}
	char name[100];
	char bd[100];
	char pn[100];
	int line = 0;
	while(1){
	for(int i = 0; i < 100; i++){

		char c = getc(file);
		
		if(c == EOF){
			if(line<2) return 1;

		       	return 0;
		}
		if(c == ','){
			name[i] = '\0';
			break;
		}
		if (c == EOF) return 0;
		name[i] = c;
	}
	for(int i = 0; i < 100; i++){
                char c = getc(file);
                if(c == ','){
			bd[i] = '\0';
                        break;
                }
                bd[i] = c;
        }
	for(int i = 0; i < 100; i++){
                char c = getc(file);
                if(c == '\n'){
			pn[i] = '\0';
                        break;
                }
                pn[i] = c;
        }
	

	if(line == 1)phonebook_length=0;
	if(line>0) addRecord(name,bd,pn);
	line++;
	}

	fclose(file);
	return 0;
}


int saveCSV(char *filename){
	FILE *file = fopen(filename, "wt");
	if(file == NULL) return 1;
	if(phonebook_length == 0) return 2;
	fprintf(file,"name,birthdate,phone\n");
	for(int i =0; i <phonebook_length;i++){
		fprintf(file, "%s,%s,%s\n", phonebook[i].name, phonebook[i].birthdate, phonebook[i].phone);
	}
	fclose(file);
	return 0;

}

/*
int main(){

	addRecord("yantian", "1999-08-23", "4389264897");
	listRecords();
	puts("file name:");
	char name[50];
	fgets(name, 50, stdin);
	for(int i = 0; i < 50; i++){
		if(name[i]=='\n') name[i] = '\0';
	}
	loadCSV(name);	
	listRecords();

	puts("copy to destination:");
	char out[50];
        fgets(out, 50, stdin);
        for(int i = 0; i < 50; i++){
                if(out[i]=='\n') out[i] = '\0';
        }

	saveCSV(out);
}
*/
