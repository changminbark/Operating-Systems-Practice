#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>      /* for read() and write() */
#include <sys/types.h>   /* for open() */
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char*argv[]) {
     int fp;
     char ch;
	 int bytes_read = 0;

	 if (argc != 2) {
		printf("Usage: %s file_to_open\n", argv[0]);
		exit(1);
	 }
	 //fp = open("hello.txt", O_RDONLY);   /* open file 'hello.txt' for read */
     fp = open(argv[1], O_RDONLY);  /* read itself */
     if (-1 == fp)  {
	   fprintf(stderr, "error in opening file\n");
	   exit(2);
     }
     bytes_read = read(fp, &ch, sizeof(ch));
     while (bytes_read > 0)   { /* if not end of the file, continue */
          /* reading one char at a time */
	   printf("%c", (char)ch);
	   bytes_read = read(fp, &ch, sizeof(ch));
     }
     close(fp);
     return 0;
}
