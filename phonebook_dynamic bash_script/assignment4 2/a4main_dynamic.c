#include "a4phonebook_dynamic.c"
int menu(void){
	puts("Phonebook Menu: (1)Add, (2)Find, (3)List, (4)Quit > ");
	int temp;
        scanf("%d", &temp);
	//clear buffer
	while (getchar() != '\n');	
	return temp;
}

int main(){
	puts("size of phonebook array:");
	int size;
	scanf("%d",&size);
	phonebook_array(size);	



	while(1) {
		int exit = 0;
		int input = menu();
		switch (input){
			case 1:
				char name[50];
				char bd[50];
				char pn[50];
				puts("name: ");
				fgets(name, 50, stdin);
				for(int i = 0 ; i < 50; i++){
					if(name[i]=='\n') name[i] = '\0';
				}
					
				puts("birthday: ");
                                fgets(bd, 50, stdin);
                                for(int i = 0 ; i < 50; i++){
                                        if(bd[i]=='\n') bd[i] = '\0';
                                }

				puts("phone: ");
                                fgets(pn, 50, stdin);
                                for(int i = 0 ; i < 50; i++){
                                        if(pn[i]=='\n') pn[i] = '\0';
                                }
				int exit_status = addRecord(name,bd,pn);
				if(exit_status!=0) printf("exit with error code %d: phone book array was already full\n", exit_status);
				break;
			case 2:
				puts("name to find: ");
				char find_name[50];
                                fgets(find_name, 50, stdin);
                                for(int i = 0 ; i < 50; i++){
                                      if(find_name[i]=='\n') find_name[i] = '\0';
                                }
				findRecord(find_name);
				break;
			case 3:
				int code = listRecords();
				if(code != 0) puts("phonebook is empty"); 
				break;
			case 4:
				exit = 1;
				break;
			default:
				puts("Invalid menu selection");
		}
		if(exit){
			saveCSV("phonebook.csv");
        		puts("End of phonebook program");
        		return 0;
		}
	}
}

