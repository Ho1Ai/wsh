#include <stdio.h>
#include <string.h>

#define MAX_LEN 1024

int main(int argc, char** argv){
	if(argv[2] !=NULL) {
		if(argv[0][strlen(argv[0])-1] == '/'){
			char* final_file = strcat(argv[0], argv[2]);
		//snprintf(final_file, MAX_LEN, "%s%s", argv[0], argv[2]);
			int on_remove_tester = remove(final_file);
			if(on_remove_tester==0) {
				printf("Object has been removed succesfully\n");
			} else {
				printf("Couldn't remove this object\n");
			}
		} else {
			char* final_file = strcat(argv[0], "/");
			int on_remove_tester = remove(strcat(final_file,argv[2]));
			on_remove_tester == 0 ? printf("Object has been removed succesfully\n") : printf("Couldn't remove this object\n");
		}	
	} else {
		printf("An error occured: no arguments provided\n");
	}
	

	return 0;
}
