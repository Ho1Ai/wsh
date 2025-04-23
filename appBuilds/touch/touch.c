#include <stdio.h>

int main(const char* final_object_path){
	char* final_object_path	= "./final.js";
	FILE* file = fopen(final_object_path, "w");
	fclose(file);
}
