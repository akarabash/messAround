#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <errno.h>

int main()
{
	const int shm_size = 4096; //file size
	const char *name = "OS";  //file name

	/*original message to write into shared memory segment */
	const char *message0 = "First Time";
  	
	int shm_fd;
	char *shm_base;
	char *ptr;

	/* create shared memory segment like it is a file */
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	if(shm_fd == -1){
		printf("prod: Shared memory failed: %s\n", strerror(errno));
    	exit(1);
	}

	/* configure size of the shared memory segment */
	ftruncate(shm_fd, shm_size);

	/* map shared memory segment to address space of process */
	shm_base = mmap(0, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (shm_base == MAP_FAILED) {
	  printf("prod: Map failed: %s\n", strerror(errno));
	  exit(1);
	}
	/* write to shared memory segment */
	ptr = shm_base;
  	ptr += sprintf(ptr, "%s", message0);

	/* close the shared memory segment */
	close(shm_fd);
	
  	return 0;
  }

