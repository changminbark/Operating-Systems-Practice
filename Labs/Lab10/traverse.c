/*
* CSCI 315 Operating Systems Design
* Original developed by CSCI 315 staff
* Modified by: L. Felipe Perrone
* Date: 2011-4-21
* Copyright (c) 2011 Bucknell University
*
* Permission is hereby granted, free of charge, to any individual or
* institution obtaining a copy of this software and associated
* documentation files (the "Software"), to use, copy, modify, and
* distribute without restriction, provided that this copyright and
* permission notice is maintained, intact, in all copies and supporting
* documentation.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL BUCKNELL UNIVERSITY BE LIABLE FOR ANY CLAIM, DAMAGES
* OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
* OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "read_dir.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <grp.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <pwd.h>
#include <time.h>
#include <unistd.h>

// Struct of stats
struct traverse_stats {
  off_t smallest;
  off_t largest;
  double average;
  off_t total_size;
  int total_files;  // for calculating average
  int num_dirs;
  int num_reg_files;
  char most_recent_file[255];
  time_t most_recent_time;
  char least_recent_file[255];
  time_t least_recent_time;
};

// function prototypes
void process(char *root, struct traverse_stats *stats);
int get_file_stats(char *path, struct traverse_stats *stats);
void print_stats(struct traverse_stats *stats);

// main function
int main(int argc,char *argv[]) {

  if (2 != argc) {
    printf(" usage: %s dirpath\n", argv[0]);
    exit(-1);
  }
  else {
    // pass in the starting directory
    struct traverse_stats stats = {0};
    process(argv[1], &stats); 
    print_stats(&stats);      
  }
  
  return 0;
}

// traverse a directory tree applying a function when a file is found
void process(char *root, struct traverse_stats *stats)
{
  que_t nameq;
  char dname[MAXLENGTH+1];
  char cname[MAXLENGTH+1]; // Technically could reuse dname, but for clarity use cname
  char prefix[MAXLENGTH+1];

  struct dirent *dp;
  DIR *dirp;

    initq(&nameq);
    enqueue(root,&nameq);

    while (true != queue_empty(nameq)) {
      peek_front(dname,nameq); 
      dequeue(&nameq);
      
      dirp = opendir(dname);
      if (dirp != NULL) { // it is a directory
        printf("directory : %s\n",dname);
        strncpy(prefix, dname, MAXLENGTH);
        strncat(prefix,"/", MAXLENGTH);
        
        // Loop through every directory entry and add to queue
        for (dp = readdir(dirp); NULL != dp; dp = readdir(dirp)) {
          if ((strcmp(dp->d_name,"..") != 0) && 
              (strcmp(dp->d_name,".") != 0)) {
            
            // prevent from infinite loop
            strncpy(cname, prefix, MAXLENGTH);
            
            // concatenate the prefix
            strncat(cname, dp->d_name, MAXLENGTH);  

            // Check if it's a symbolic link
            struct stat entry_stat;
            if (lstat(cname, &entry_stat) == 0) {
              if (S_ISLNK(entry_stat.st_mode)) {
                printf(" symbolic link skipped: %s\n", cname);
                continue;  // skip enqueueing symlink
              }
            } else {
              perror("lstat failed");
              continue;
            }
            
            enqueue(cname,&nameq);
          }
        }
        closedir (dirp);
      } else { 
        // test if it is a regular file and not a device or link -- TO-DO
        // if this is a regular file, then process it -- TO-DO
        printf(" processing file: %s\n", dname);
      } 
      
      // Get file/directory stats and update stats struct if needed
      if (get_file_stats(dname, stats) != 0) {
        printf(" error getting file stats for: %s\n", dname);
      }
      stats->total_files++;
    } // while
    
    printf(" a total of %d files were counted\n", stats->total_files);
}

// initialize queue data structure
void initq(que_t *q) {
  q->head = q->tail = NULL;
}

// test whether queue data structure is empty
bool queue_empty(que_t q) {
  if (NULL == q.head) {
    return true;
  } else {
    return false;
  }
}

// add an element to queue
void enqueue(char *name, que_t *q) {
  item_t *temp;
  
  temp = (item_t *)malloc(sizeof(item_t));
  strncpy(temp->name,name,MAXLENGTH);
  temp->next = NULL;
  
  if (true == queue_empty(*q)) {
    q->head = temp;
    q->tail = temp;
  } else {
    q->tail->next = temp;
    q->tail = q->tail->next;
  }
}

// remove an element from the front of the queue
void dequeue(que_t *q) {
  item_t *temp;
  
  if (true == queue_empty(*q)) {
    printf(" error in dequeue \n");
    exit(-1);
  } else {
    temp = q->head;
    q->head = q->head->next;
    free(temp);
  }
}

// find element at front of queue without removing
void peek_front(char *name, que_t q) {
  if (true == queue_empty(q)) {
    printf(" error in dequeue \n");
    exit(-1);
  } else {
    strncpy(name, q.head->name, MAXLENGTH);
  }
} 

int get_file_stats(char *path, struct traverse_stats *stats) {

  // container for complete set of file permission bits (binary)
  unsigned int mode;

  // container for the three bits of user permissions
  unsigned int umode;

  // container for the three bits of group permissions
  unsigned int gmode;

  // container for the three bits of owner permission
  unsigned int omode;

  // human readable file permissions (ASCII text)
  char perm_bits_str[] = "---------";

  // file descriptor 
  unsigned int fd;

  // structure to contain the result of the fstat call (info on this file)
  struct stat file_info;
  
  // try to open file
  fd = open(path, O_RDONLY);
  if (-1 == fd) {
    perror("Failed to open read only file - ");
    exit(-1);
  }
   
  // use fstat to get information on specific file
  if (fstat(fd, &file_info) == 0) {
    printf("\n== FILE INFO ============================\n");
    printf(" file fstat() call successful\n");
    
    // mode comes from the lower 9 bits in file_info.st_mode
    mode = file_info.st_mode & 0x1FF;
    
    printf(" file protection bits = 0%o\n", mode);
    
    // umode comes from the high 3 bits in mode
    umode = (mode & 0700) >> 6; 
    
    // gmode comes from the middle 3 bits in mode
    gmode = (mode & 0070) >> 3; 
    
    // omode comes from the low 3 bits in mode
    omode = (mode & 0007); 
      
    // once you have set umode, gmode, and omode, the code below
    // will construct the right string for you and display it

    // construct string with file protection information
    if (umode & 0x4) perm_bits_str[0] = 'r';
    if (umode & 0x2) perm_bits_str[1] = 'w';
    if (umode & 0x1) perm_bits_str[2] = 'x';
    
    if (gmode & 0x4) perm_bits_str[3] = 'r';
    if (gmode & 0x2) perm_bits_str[4] = 'w';
    if (gmode & 0x1) perm_bits_str[5] = 'x';
    
    if (omode & 0x4) perm_bits_str[6] = 'r';
    if (omode & 0x2) perm_bits_str[7] = 'w';
    if (omode & 0x1) perm_bits_str[8] = 'x';
    
    printf(" file protection string = %s\n", perm_bits_str);
    
    printf(" file protection mode (u:g:o) = %o:%o:%o\n",
	   umode, gmode, omode);
    
    // get owner user name
    struct passwd *pw = getpwuid(file_info.st_uid);
    if (pw != NULL)
      printf(" owner user name = %s\n", pw->pw_name);
    else
      printf(" owner user name = (could not resolve UID %d)\n", file_info.st_uid);
      
    // get owner group name
    struct group *gr = getgrgid(file_info.st_gid);
    if (gr != NULL)
      printf(" owner group name = %s\n", gr->gr_name);
    else
      printf(" owner group name = (could not resolve GID %d)\n", file_info.st_gid);
    
		// TO-DO: print "mode = x", where x may be:
		// "regular file"
		// "directory"
		// "character device"
		// "block device"
		// "symbolic link"
		// "socket"
		// "fifo"
		// "unknown"

    // determine file type using mode macros
    if (S_ISREG(file_info.st_mode)) {
      printf(" mode = regular file\n");
      stats->num_reg_files++;
      stats->total_size += file_info.st_size;
      stats->total_files++;

      // Initialize on first file
      if (stats->smallest == 0 || file_info.st_size < stats->smallest) {
        stats->smallest = file_info.st_size;
      }
      if (file_info.st_size > stats->largest) {
        stats->largest = file_info.st_size;
      }

      // Compute running average (optional but safe to do after all files instead)
      stats->average = (double)stats->total_size / stats->total_files;
    } else if (S_ISDIR(file_info.st_mode)) {
      printf(" mode = directory\n");
      stats->num_dirs++;
    } else if (S_ISCHR(file_info.st_mode)) {
      printf(" mode = character device\n");
    } else if (S_ISBLK(file_info.st_mode)) {
      printf(" mode = block device\n");
    } else if (S_ISLNK(file_info.st_mode)) {
      printf(" mode = symbolic link\n");
    } else if (S_ISSOCK(file_info.st_mode)) {
      printf(" mode = socket\n");
    } else if (S_ISFIFO(file_info.st_mode)) {
      printf(" mode = fifo\n");
    } else {
      printf(" mode = unknown\n");
    }
        
    // Initialize stats most_recent_time if does not exist
    // Check if file is newest most/least recent time
    if (stats->most_recent_time == 0 || file_info.st_mtime > stats->most_recent_time) {
      stats->most_recent_time = file_info.st_mtime;
      strncpy(stats->most_recent_file, path, sizeof(stats->most_recent_file));
      stats->most_recent_file[sizeof(stats->most_recent_file) - 1] = '\0';
    }
    if (stats->least_recent_time == 0 || file_info.st_mtime < stats->least_recent_time) {
      stats->least_recent_time = file_info.st_mtime;
      strncpy(stats->least_recent_file, path, sizeof(stats->least_recent_file));
      stats->least_recent_file[sizeof(stats->least_recent_file) - 1] = '\0';
    }
    
    fflush(stdout);
    close(fd);
    return 0;
  }
  else
    printf(" fstat call failed\n");

  return -1;
}

void print_stats(struct traverse_stats *stats) {
  char mod_time_str[35];
  char least_time_str[35];
  struct tm timebuf;

  printf("\n== TRAVERSAL STATISTICS ======================\n");

  printf(" Smallest file size: %ld bytes\n", stats->smallest);
  printf(" Largest file size: %ld bytes\n", stats->largest);
  printf(" Average file size: %.2f bytes\n", stats->average);

  printf(" Total number of regular files: %d\n", stats->num_reg_files);
  printf(" Total number of directories: %d\n", stats->num_dirs);

  // Most recent file
  localtime_r(&stats->most_recent_time, &timebuf);
  asctime_r(&timebuf, mod_time_str);
  mod_time_str[strcspn(mod_time_str, "\n")] = '\0'; // remove trailing newline
  printf(" Most recently modified file: %s\n", stats->most_recent_file);
  printf(" Modification time: %s\n", mod_time_str);

  // Least recent file
  localtime_r(&stats->least_recent_time, &timebuf);
  asctime_r(&timebuf, least_time_str);
  least_time_str[strcspn(least_time_str, "\n")] = '\0'; // remove trailing newline
  printf(" Least recently modified file: %s\n", stats->least_recent_file);
  printf(" Modification time: %s\n", least_time_str);
}