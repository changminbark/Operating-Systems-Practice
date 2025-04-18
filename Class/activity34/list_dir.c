/*
 * CSCI 315
 * class demonstration
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

#define _GNU_SOURCE // needed for directory types or compile with -std=gnu99

void print_ftype(unsigned char);

int main(int argc, char* argv[]) {

  struct dirent *dp;
  DIR *dirp;

  if (argc != 2) {
     fprintf(stderr, "usage %s dir_name\n", argv[0]);
     exit(1);
  }
  char * dname = argv[1];

  dirp = opendir(dname);
  if (dirp != NULL) { // it is a directory

    printf("directory : %s\n",dname);
	
    for (dp = readdir(dirp); NULL != dp; dp = readdir(dirp)) {
      printf("name: [%s] ", dp->d_name);  
      print_ftype(dp->d_type);
    }
    closedir (dirp);
  } 

  return 0;
}

void print_ftype(unsigned char type) {

  switch (type)
    {
    case DT_UNKNOWN: printf("type: [unknown]\n");
      break;
    case DT_REG: printf("type: [regular]\n");
      break;
    case DT_DIR: printf("type: [directory]\n");
      break;
    case DT_FIFO: printf("type: [named pipe]\n");
      break;
    case DT_SOCK: printf("type: [local-domain socket]\n");
      break;
    case DT_CHR: printf("type: [character device]\n");
      break;
    case DT_BLK: printf("type: [block device]\n");
      break;
    case DT_LNK: printf("type: [symbolic link]\n");
      break;
    }
}
