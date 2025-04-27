#include <stdio.h>
#include <dirent.h>
#include <string.h>

void dispatch_list (const char *final_dispatch_dir_address) {
	DIR *dir = opendir(final_dispatch_dir_address);
	if(dir == NULL){
		printf("An error occured: couldn't read directory with this path: %s", final_dispatch_dir_address);
		return;
	}

	int row_num = 1;

	struct dirent *entry;
	while((entry = readdir(dir)) != NULL){
		if (strcmp(entry->d_name, ".")!=0&&strcmp(entry->d_name, "..")!=0) {
			if(row_num < 6) { // maximum 6 elements in one row
				entry->d_type == DT_DIR ? printf("\033[1;32m%s/\033[0m\t\t", entry->d_name) : printf("%s\t\t", entry->d_name);
				row_num++;
			} else {
				printf("%s\n", entry->d_name);
				row_num = 0;
			}
		}
	}
}

int main(int argc, char** argv){
	if (argv[2]==NULL) {
		dispatch_list(argv[0]);
	} else {
		dispatch_list(argv[2]); // if someone needs to check something in the different directory
	}

	printf("\n");

	return 0;	
}
