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
	
	char array[64];
  	char *date = array;
	
	char arr[64];
  	char *c = arr;
	
	
	int shm_fd;
  	char *shm_base;
  	char *ptr;

  	const int shm_size = 4096;


  	shm_fd = shm_open(name, O_RDWR, 0666);
  	if(shm_fd == -1){
  		printf("Shared memory failed\n");
  		exit(1);
  	}

  	shm_base = mmap(0, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  	if(shm_fd == -1){
  		exit(1);
  	}

  	/* check to see if anything written to shared memory */
  	if(strcmp(shm_base,"First Time") == 0){
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
		printf("%s", shm_base);
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

  	printf("Do you want to terminate? Y/N \n");
  	scanf("%s", c);
	if(c == 'Y'){
		exit(0);
	}
  	return 0;
	
}
