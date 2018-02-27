#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>

//void display(char *prog, char *bytes, int n);

int main()
{
  const char *name = "OS";	// file name
  const int SIZE = 4096;		// file size

  const char *message0 = "Amin ";
  const char *message1 = "February ";
  const char *message2 = "!";
  const char *msg_end  = "\n";


  int shm_fd;		// file descriptor, from shm_open()
  char *shm_base;	// base address, from mmap()
  char *ptr;

  /* open the shared memory segment as if it was a file */
  shm_fd = shm_open(name, O_RDWR, 0666);
  if (shm_fd == -1) {
    printf("cons: Shared memory failed: %s\n", strerror(errno));
    exit(1);
  }

  /* map the shared memory segment to the address space of the process */
  shm_base = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  if (shm_base == MAP_FAILED) {
    printf("cons: Map failed: %s\n", strerror(errno));
    // close and unlink?
    exit(1);
  }

  /* read from the mapped shared memory segment */
  //display("cons", shm_base, 64);	// first as bytes, then as a string
  
  /* check if shared memory object contains any status */
  printf("%s", shm_base);
 
  /* write into shared memory */
   ptr = shm_base;
   ptr += sprintf(ptr, "%s", message0);
   ptr += sprintf(ptr, "%s", message1);
   ptr += sprintf(ptr, "%s", message2);
   ptr += sprintf(ptr, "%s", msg_end);
  
  
  else{
    printf("%s", shm_base);
  }
  
  char array[64];
  char *c = array;
  printf("Do you want to terminate? Y or N \n");
  scanf("%s", c);
  if(name = 'Y'){
    exit(0);
  }
  

  /* remove the mapped shared memory segment from the address space of the process */
  if (munmap(shm_base, SIZE) == -1) {
    printf("cons: Unmap failed: %s\n", strerror(errno));
    exit(1);
  }

  /* close the shared memory segment as if it was a file */
  if (close(shm_fd) == -1) {
    printf("cons: Close failed: %s\n", strerror(errno));
    exit(1);
  }

  /* remove the shared memory segment from the file system 
  if (shm_unlink(name) == -1) {
    printf("cons: Error removing %s: %s\n", name, strerror(errno));
    exit(1);
  }
  */

  return 0;
}
