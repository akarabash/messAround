# the shared memory example from OSC 9e Sec. 3.5.1, Fig. 3.17, 3.18

# this must use GNU Make ("make" on Linux and Mac OS X, "gmake" on Solaris)

# compiler options -- C99 with warnings
OPT_GCC = -std=c99 -Wall -Wextra

# compiler options and libraries for Linux, Mac OS X or Solaris
ifeq ($(OSTYPE),linux)
  OPT = -D_XOPEN_SOURCE=700
  LIB = -lrt
endif
ifeq ($(OSTYPE),darwin)	# Mac OS X
  OPT = 
  LIB = 
endif
ifeq ($(OSTYPE),solaris)
  OPT = -D_XOPEN_SOURCE=600
  LIB = -lrt
endif

all: cons prod

cons: client_shm.c
	gcc $(OPT_GCC) -D_XOPEN_SOURCE=700 -o cons client_shm.c -lrt

prod: server_shm.c
	gcc $(OPT_GCC) -D_XOPEN_SOURCE=700 -o prod server_shm.c -lrt

run: cons prod
	./prod
	./cons

clean:
	rm -f cons prod
