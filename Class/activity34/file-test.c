#include <stdio.h>
#include <stdlib.h>

int main() {
     FILE * fp;
     char ch;

     fp = fopen("hello.txt", "r");   /* open file 'file-test.c' for read */
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
