#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>      /* for read() and write() */
#include <sys/types.h>   /* for open() */
#include <sys/stat.h>
#include <fcntl.h>

int main() {
     int fp;
     char ch;
	 int bytes_read = 0;

     fp = open("hello.txt", O_RDONLY);   /* open file 'hello.txt' for read */
     //fp = open("file-syscalls.c", O_RDONLY);  /* read itself */
     if (-1 == fp)  {
	   fprintf(stderr, "error in opening file\n");
	   exit(2);
     }
	 lseek(fp, 6, SEEK_SET);   // "Hello world!" so we should read 'w' now
     bytes_read = read(fp, &ch, sizeof(ch));
	 printf("char read = ['%c']\n", ch);
     close(fp);
     return 0;
}
