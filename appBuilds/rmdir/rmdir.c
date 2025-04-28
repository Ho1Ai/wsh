#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <stdbool.h>

int main(int argc, char** argv) {
	if(argv[2]!=0){
		if(argv[0][strlen(argv[0])-1]=='/'){
	char* dir_name = strcat(argv[0],argv[2]);
	DIR* removing_dir = opendir(dir_name);
	
	struct dirent* entry; //testing if there are smth in dir
	bool empty_dir = true;
	
	while((entry = readdir(removing_dir))!=NULL) {
		if(strcmp(entry->d_name, ".")!=0 && strcmp(entry->d_name, "..")!=0) {
			//printf("something in the dir");
			empty_dir = false;
			break;
		}
	}

	if(empty_dir == false) {
		printf("An error occured: rmdir can delete only empty directories. Try to remove files and directories in it and then try to remove this directory again\nWrite 'rmdir --help' to see more information\n");
	} else {
		int rmdir_test = rmdir(dir_name);
		rmdir_test == 0 ? printf("Directory has been removed succesfully\n") : printf("An error occured while removing directory\n");
	} 
		closedir(removing_dir);
		} else {
		//printf("there is no slash in the end of pwd which has been delivered here by using rmdir\n");

		char* real_pwd = strcat(argv[0],"/");
		//printf("real_pwd: %s\n", real_pwd);
		char* dir_name = strcat(real_pwd, argv[2]);
		DIR* removing_dir = opendir(dir_name);
		
		struct dirent* entry;
		bool empty_dir=true;
		
		while((entry = readdir(removing_dir))!=NULL) {
			if(strcmp(entry->d_name, ".")!= 0 && strcmp(entry->d_name, "..")!= 0 ) {
				empty_dir = false;
				break;
			}
		}

		if (empty_dir == false) {
			printf("An error occured: rmdir can delete only empty directories. Try to remove files and directories in it and then try to remove this directory again\nWrite 'rmdir --help' to see more information\n");
		} else {
			int rmdir_test = rmdir(dir_name);
			rmdir_test == 0 ? printf("Directory has been removed succesfully\n"): printf("An error occured while removing directory\n");
		};
	}


	//closedir(removing_dir);
	} else {
		printf("An error occured: missing operand.\nWrite 'rmdir --help' to see more information\n");	
	}

	
	return 0;
}
