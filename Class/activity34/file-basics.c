#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
     FILE * fp;
     char ch;

     if (argc != 2) {
         fprintf(stderr, "usage: %s file_to_open\n", argv[0]);
         exit(2);
     }

	 //     fp = fopen("hello.txt", "r");   /* open file 'hello.txt' for read */
	 fp = fopen(argv[1], "r");   /* open file 'hello.txt' for read */
     if (!fp)  {
          fprintf(stderr, "error in opening file\n");
          exit(2);
     }
     fscanf(fp, "%c", &ch);
     while (!feof(fp))   { /* if not end of the file, continue */
          /* reading one char at a time */
          printf("%c", ch);
          fscanf(fp, "%c", &ch);
     }
     fclose(fp);
     return 0;
}
