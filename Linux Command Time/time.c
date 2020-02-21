#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <math.h>

int main(int argc, char *argv[])
{
	double time_elapsed = 0.0; //Initially set to 0 then update based on process
	struct timeval *t1; //Store start time in here
	char *filename = "./time.c"; //for argv
	const int SIZE = 4096;
	int fd; //shared memory file descriptor
	//char *ptr;
	const char *name = "time"; //Shared memory object, could name anything
	//Set conditions for fork
	pid_t pid;
	pid = fork();
	//Check for error condition
	if (pid < 0) { printf("error \n"); }
	//Child
	else if (pid == 0) {
	//Shared memory object
	 fd = shm_open(name,O_CREAT | O_RDWR,0666);
	 //Configure size of shared memory
	 ftruncate(fd, SIZE);
	 //Update time onto the shared memory
	 t1 = (struct timeval*) mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	 gettimeofday(t1, NULL);
	 execvp(filename, argv);
}
	//Parent
	else {
	//Parent waits until child process terminates
	wait(NULL);
	struct timeval t2; //Stores end time
	//Opens shared memory object
	fd = shm_open(name, O_RDONLY, 0666);
	//Time being stored onto the shared memory
	t1 = (struct timeval*) mmap(NULL, SIZE, PROT_READ, MAP_PRIVATE, fd, 0);
	gettimeofday(&t2, NULL); //Gets endtime
	//Calculate the time elapsed in microseconds
	time_elapsed += ((t2.tv_usec - t1->tv_usec));
	printf("time.c \n");
	printf("time \n");
	printf("Elapsed time: %.2f", time_elapsed);
	printf(" microseconds ");
	printf("or %.6f ", time_elapsed / 1000000 ); //Gets conversion in seconds
	printf(" seconds \n ");
	shm_unlink(name);
}
	return 0;
}
