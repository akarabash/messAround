#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>

int main()
{
	const int shm_size = 4096;

	char arrays[64];
  	char *name = arrays; 	// file name
  	printf("Enter Key \n");
  	scanf("%s", name);

  	const char *message0 = "Amin";
  	const char *message1 = "February ";
  	const char *message_end = "\n";

  	int shm_fd;
  	char *shm_base;
  	char *ptr;

  	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
  	if(shm_fd == -1){
  		printf("prod: Shared memory failed: %s\n", strerror(errno));
  		exit(1);
  	}

  	ftruncate(shm_fd, shm_size);

  	shm_base = mmap(0, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  	if(shm_base == MAP_FAILED){
  		printf("prod: Map failed: %s\n", strerror(errno));
  		exit(1);
  	}

  	ptr = shm_base;
  	ptr += sprintf(ptr, "%s", message0);
  	ptr += sprintf(ptr, "%s", message1);
  	ptr += sprintf(ptr, "%s", message_end);

  	/*
  	if (munmap(shm_base, SIZE) == -1) {
    	printf("prod: Unmap failed: %s\n", strerror(errno));
    	exit(1);
  	}

  	
  	if (close(shm_fd) == -1) {
    	printf("prod: Close failed: %s\n", strerror(errno));
    	exit(1);
  	}
  	*/

  	return 0;

}
