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
	
	char arrays[64];
  	char *name = arrays; 	// file name
  	printf("Enter Key \n");
  	scanf("%s", name);
	
	int shm_fd;
  	char *shm_base;
  	char *ptr;

  	const int shm_size = 4096;

  	const char *message0 = "Amin ";
  	const char *message1 = "February";
  	const char *message_end = "\n";

  	shm_fd = shm_open(name, O_RDWR, 0666);
  	if(shm_fd == -1){
  		printf("Shared memory failed\n")
  		exit(1);
  	}

  	shm_base = mmap(0, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  	if(shm_fd == -1){
  		exit(1);
  	}

  	/* check to see if anything written to shared memory */
  	if(shm_base == '\0'){
  		/*read from the mapped shared memory segment */
  		printf("%s", shm_base);

  		/* write to shared memory segment */
		ptr = shm_base;
  		ptr += sprintf(ptr, "%s", message0);
  		ptr += sprintf(ptr, "%s", message1);
  		ptr += sprintf(ptr, "%s", message_end);

  	}

  	

  	/*read from the mapped shared memory segment */
  	//printf("%s", shm_base);




  	/* write to shared memory segment */
	ptr = shm_base;
  	ptr += sprintf(ptr, "%s", message0);
  	ptr += sprintf(ptr, "%s", message1);
  	ptr += sprintf(ptr, "%s", message_end);



  	return 0;


}
