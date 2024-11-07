#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Altera_UP_SD_Card_Avalon_Interface.h"

#define MAX_SUBDIRECTORIES 20


/*******************************************************************************
 * This program demonstrates use of the SD Card reader
 *
 * It performs the following:
 *	1.	detects if a properly-formatted SD Card is present
 *	2.	recursively searches the directory tree for files
 *	3.	prints out the list of files to the terminal window
 ******************************************************************************/

// find_files will print out the list of files in the current path,
// then recursively call itself on any subdirectories it finds.
// It is limited to directories containing MAX_SUBDIRECTORIES or fewer
// subdirectories and a maximium path length of 104 characters (including /'s)
void find_files (char* path){
	char filepath [90];
	char filename [15];
	char fullpath [104];
	char* folders [MAX_SUBDIRECTORIES];
	int num_dirs = 0;
	short int file;
	short int attributes;
	bool foundAll;

	//copy the path name to local memory
	strcpy (filepath, path);

	foundAll = (alt_up_sd_card_find_first(filepath,filename) == 0 ? false : true);

	//output the current directory
	printf("/%s\n",filepath);

	//loop through the directory tree
	while (!foundAll){
		strcpy (fullpath,filepath);
		//remove the '.' character from the filepath (foo/bar/. -> foo/bar/)
		fullpath [strlen(filepath)-1] = '\0';
		strcat (fullpath,filename);

		file = alt_up_sd_card_fopen (fullpath, false);
		attributes = alt_up_sd_card_get_attributes (file);
		if (file != -1)
			alt_up_sd_card_fclose(file);

		//print the file name, unless it's a directory or mount point
		if ( (attributes != -1) && !(attributes & 0x0018)){
			printf("/%s\n",fullpath);
		}

		//if a directory is found, allocate space and save its name for later
		if ((attributes != -1) && (attributes & 0x0010)){
			folders [num_dirs] = malloc (15*sizeof(char));
			strcpy(folders[num_dirs],filename);
			num_dirs++;
		}

		foundAll = (alt_up_sd_card_find_next(filename) == 0 ? false : true);
	}

	//second loop to open any directories found and call find_files() on them
	int i;
	for (i=0; i<num_dirs; i++){

		strcpy (fullpath,filepath);
		fullpath [strlen(filepath)-1] = '\0';
		strcat (fullpath,folders[i]);
		strcat (fullpath, "/.");
		find_files (fullpath);
		free(folders[i]);
	}

	return;
}

int main (void){

	int choice;
	int i;

	char ch;
	alt_up_sd_card_dev * sd_card;
			sd_card = alt_up_sd_card_open_dev("/dev/SD_Card");

do{

printf("Enter 1 to see the files present in the SD Card \n");
printf("Enter 2 to write to a file \n");
printf("Enter 3 to read from a file \n");
scanf("%d", &choice);


		switch(choice){

case 1: {short int file_handle;
	 if (sd_card!=NULL){
		if (alt_up_sd_card_is_Present()){
			printf("An SD Card was found!\n");
		}
		else {
			printf("No SD Card Found. \n Exiting the program.");
		//	return -1;
		}

		if (alt_up_sd_card_is_FAT16()){
			printf("FAT-16 partition found!\n");
		}
		else{
			printf("No FAT-16 partition found - Exiting!\n");
	//		return -1;
		}

		printf("The SD Card contains the following files:\n");

		//Call find_files on the root directory
		find_files (".");

	}
	 break;}

case 2: {short int file_handle;
	file_handle =alt_up_sd_card_fopen("NEW_FILE.txt" ,false);

		 	if(file_handle != -1)
		 	{
		 		printf("File was opened!\n");
		 		alt_up_sd_card_write(file_handle,'C');
		 		alt_up_sd_card_fclose(file_handle);
		 	}
		 		else
		 		printf("Error opening the file\n");
		 	// the code below reads the data in a file until it ends
		 	// Reads byte by byte and is saves it as a CHARACTER! until a -1 is returned
		 	//

break;
}

case 3: {short int file_handle;
	file_handle =alt_up_sd_card_fopen("NEW_FILE.txt" ,false);
		 	do
		 	{

		 	i = alt_up_sd_card_read(file_handle); //
		 	if(i == -1)
		 	 			break;
		 	printf("%c",i);
		 	}while(i != -1);
		 	alt_up_sd_card_fclose(file_handle);
break;
}
		}
printf("\n Do you want to continue? (y/n) \n");
scanf(" %c",&ch);
}while(ch != 'n' && ch != 'N');

return 0;
}
