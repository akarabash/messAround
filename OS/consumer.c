#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>

int main(){

  /* read in the key for the shared memory segment */
  char arrays[64];
  char *name = arrays; 	// file key & name for saving process status
  printf("Enter Key \n");
  scanf("%s", name);
	
  char array[64];    
  char *date = array;   // date for saving  process status
	
  char arr[64];
  char *c = arr;        // decision to terminate process
	
  
  int shm_fd;           // file descriptor, from shm_open()
  char *shm_base;       // base address, from mmap()
  char *ptr;            // movable pointer since shm_base is fixed

  const int shm_size = 4096; //shared memory segment size

  /* open the shared memory segment */
  shm_fd = shm_open(name, O_RDWR, 0666);
  if(shm_fd == -1){
    printf("cons: Shared memory failed: %s\n", strerror(errno));
    exit(1);
  }

  /* map the shared memory segment to address space of the process */
  shm_base = mmap(0, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  if(shm_fd == -1){
    printf("cons: Shared memory failed: %s\n", strerror(errno));
    exit(1);
  }

  /* check to see if anything written to shared memory */
  if(strcmp(shm_base,"First Time") == 0){

    /* save process status */
    printf("Enter Name \n");
    scanf("%s", name);
    printf("Enter Date \n");
    scanf("%s", date);
    ptr = shm_base;
    ptr += sprintf(ptr, "%s", name);
    ptr += sprintf(ptr, "%s",  " ");
    ptr += sprintf(ptr, "%s", date);
    ptr += sprintf(ptr, "%s",  " ");
  }
	
  else{
   
    /* save process status */
    printf("%s", shm_base);
    printf("\n");
    printf("Enter Name \n");
    scanf("%s", name);
    printf("Enter Date \n");
    scanf("%s", date);
    ptr = shm_base;
    ptr += sprintf(ptr, "%s", name);
    ptr += sprintf(ptr, "%s",  " ");
    ptr += sprintf(ptr, "%s", date);
    ptr += sprintf(ptr, "%s",  " ");
  }

  /* ask user if they want to terminate */
  printf("Do you want to terminate process? Y/N \n");
  scanf("%s", c);
  
  if(c == 'Y'){
    exit(0);
  }
  

  /* close the shared memory segment */
  close(shm_fd);

  return 0;
	
}
